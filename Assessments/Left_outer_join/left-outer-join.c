#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM_NOME 100

typedef struct Departamento {
    int cod_dept;
    int sala;
    char nome[TAM_NOME];
} TDepartamento;

typedef struct Funcionario {
    int cod_func;
    int cod_dept;
    char nome[TAM_NOME];
} TFuncionario;

TFuncionario *le_funcionario(FILE *in)
{
    TFuncionario *func = (TFuncionario *) malloc(sizeof(TFuncionario));
    char linha[150];
    if (fgets (linha, 150, in) == NULL ) {
        free(func);
        return NULL;
    }

    char delimitador[] = ";";
    char *ptr;
    int cod;

    //quebra a linha
    ptr = strtok(linha, delimitador);
    cod = atoi(ptr);
    func->cod_func = cod;
    ptr = strtok(NULL, delimitador);
    cod = atoi(ptr);
    func->cod_dept = cod;
    ptr = strtok(NULL, delimitador);
    strcpy(func->nome, ptr);

    return func;
}

TDepartamento *le_departamento(FILE *in)
{
    TDepartamento *dept = (TDepartamento *) malloc(sizeof(TDepartamento));
    char linha[150];
    if (fgets (linha, 150, in) == NULL ) {
        free(dept);
        return NULL;
    }

    char delimitador[] = ";";
    char *ptr;
    int cod, sala;

    //quebra a linha
    ptr = strtok(linha, delimitador);
    cod = atoi(ptr);
    dept->cod_dept = cod;
    ptr = strtok(NULL, delimitador);
    sala = atoi(ptr);
    dept->sala = sala;
    ptr = strtok(NULL, delimitador);
    strcpy(dept->nome, ptr);

    return dept;
}

void imprime_arquivo(char *name) {
    FILE *arq; //declara ponteiro para arquivo
    // abre arquivo para leitura
    arq = fopen(name, "r");
    if (arq != NULL) {// checa se não deu erro na abertura do arquivo
        char linha[150];
        fgets (linha, 150, arq);
        while (!feof(arq)) {//testa se chegou ao final do arquivo
            printf("%s", linha);
            fgets (linha, 150, arq);
        }
        fclose(arq); //fecha arquivo
    } else printf("Erro ao abrir arquivo\n");
}

void leftOuterJoin(char *nome_arq_dept, char *nome_arq_funcionarios, char *nome_arq_join) {
    FILE *arquivo_departamento, *arquivo_funcionario, *arquivo_join;
    TDepartamento *departamento;
    TFuncionario *funcionario;

    arquivo_departamento = fopen(nome_arq_dept, "r");
    arquivo_funcionario = fopen(nome_arq_funcionarios, "r+");
    arquivo_join = fopen(nome_arq_join, "w+");

    if (arquivo_departamento == NULL) {
        printf("Erro ao abrir arquivo de departamentos\n");
        return;
    }
    if (arquivo_funcionario == NULL) {
        printf("Erro ao abrir arquivo de funcionários\n");
        return;
    }
    if (arquivo_join == NULL) {
        printf("Erro ao abrir arquivo JOIN\n");
        fclose(arquivo_departamento);
        fclose(arquivo_funcionario);
        return;
    }

    departamento = le_departamento(arquivo_departamento);
    funcionario = le_funcionario(arquivo_funcionario);

    while (departamento != NULL) {        
        int departamento_vazio = 1;
        while (funcionario != NULL)
        {            
            if (departamento->cod_dept == funcionario->cod_dept) {
                fprintf(arquivo_join, "%d;%d;%s;%d;%s;\n", departamento->cod_dept, departamento->sala, departamento->nome, funcionario->cod_func, funcionario->nome);
                departamento_vazio = 0;
            } 
            free(funcionario);
            funcionario = le_funcionario(arquivo_funcionario);
        }
        if (funcionario == NULL && departamento_vazio == 1)
        {
            fprintf(arquivo_join, "%d;%d;%s;%s;%s;\n", departamento->cod_dept, departamento->sala, departamento->nome,"0","");
        }
        free(departamento);
        departamento = le_departamento(arquivo_departamento);

        fseek(arquivo_funcionario, 0, SEEK_SET);
        funcionario = le_funcionario(arquivo_funcionario);
    }
    fclose(arquivo_departamento);
    fclose(arquivo_funcionario);
    fclose(arquivo_join);
}

int main() {
    leftOuterJoin("departamentos.txt", "funcionarios.txt", "join.txt");
    imprime_arquivo("join.txt");
}
