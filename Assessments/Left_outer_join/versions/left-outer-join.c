#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM_NOME 100

typedef struct Departamento {
    int cod_departamento;
    int sala;
    char nome[TAM_NOME];
} TDepartamento;

typedef struct Funcionario {
    int cod_funcionario;
    int cod_departamento;
    char nome[TAM_NOME];
} TFuncionario;

TFuncionario *le_funcionario(FILE *in)
{
    TFuncionario *funcionario = (TFuncionario *) malloc(sizeof(TFuncionario));
    char linha[150];
    if (fgets (linha, 150, in) == NULL ) {
        free(funcionario);
        return NULL;
    }

    char delimitador[] = ";";
    char *ptr;
    int cod;

    //quebra a linha
    ptr = strtok(linha, delimitador);
    cod = atoi(ptr);
    funcionario->cod_funcionario = cod;
    ptr = strtok(NULL, delimitador);
    cod = atoi(ptr);
    funcionario->cod_departamento = cod;
    ptr = strtok(NULL, delimitador);
    strcpy(funcionario->nome, ptr);

    return funcionario;
}

TDepartamento *le_departamento(FILE *in)
{
    TDepartamento *departamento = (TDepartamento *) malloc(sizeof(TDepartamento));
    char linha[150];
    if (fgets (linha, 150, in) == NULL ) {
        free(departamento);
        return NULL;
    }

    char delimitador[] = ";";
    char *ptr;
    int cod, sala;

    //quebra a linha
    ptr = strtok(linha, delimitador);
    cod = atoi(ptr);
    departamento->cod_departamento = cod;
    ptr = strtok(NULL, delimitador);
    sala = atoi(ptr);
    departamento->sala = sala;
    ptr = strtok(NULL, delimitador);
    strcpy(departamento->nome, ptr);

    return departamento;
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

void leftOuterJoin(char *nome_arquivo_departamento, char *nome_arquivo_funcionarios, char *nome_arquivo_join) {
    FILE *arquivo_departamento, *arquivo_funcionario, *arquivo_join;
    TDepartamento *departamento;
    TFuncionario *funcionario;

    printf("\n%s\n", nome_arquivo_departamento);
    printf("%s\n", nome_arquivo_funcionarios);
    printf("%s\n", nome_arquivo_join); 

    arquivo_departamento = fopen(nome_arquivo_departamento, "r");
    arquivo_funcionario = fopen(nome_arquivo_funcionarios, "r");
    arquivo_join = fopen(nome_arquivo_join, "w");
    
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
    
    while (funcionario != NULL && departamento != NULL) {        
        if (departamento->cod_departamento < funcionario->cod_departamento) {            
            fprintf(arquivo_join, "%d;%d;%s;;\n", departamento->cod_departamento, departamento->sala, departamento->nome);
            free(departamento);
            departamento = le_departamento(arquivo_departamento);
        } else if (departamento->cod_departamento > funcionario->cod_departamento) {
            
            fprintf(arquivo_join, ";;;;%d;%s\n", funcionario->cod_funcionario, funcionario->nome);
            free(funcionario);
            funcionario = le_funcionario(arquivo_funcionario);
        } else {
            fprintf(arquivo_join, "%d;%d;%s;%d;%s\n", departamento->cod_departamento, departamento->sala, departamento->nome, funcionario->cod_funcionario, funcionario->nome);
            free(departamento);
            free(funcionario);
            departamento = le_departamento(arquivo_departamento);
            funcionario = le_funcionario(arquivo_funcionario);
        }
    }
    while (departamento != NULL) {
        fprintf(arquivo_join, "%d;%d;%s;;\n", departamento->cod_departamento, departamento->sala, departamento->nome);
        free(departamento);
        departamento = le_departamento(arquivo_departamento);
    }
    while (funcionario != NULL) {
        fprintf(arquivo_join, ";;;;%d;%s\n", funcionario->cod_funcionario, funcionario->nome);
        free(funcionario);
        funcionario = le_funcionario(arquivo_funcionario);
    }
    fclose(arquivo_departamento);
    fclose(arquivo_funcionario);
    fclose(arquivo_join);
}

int main() {
    leftOuterJoin("/home/thiago/UFF/Estrutura de Dados/Assessments/Left_outer_join/departamentos.txt", "/home/thiago/UFF/Estrutura de Dados/Assessments/Left_outer_join/funcionarios.txt", "/home/thiago/UFF/Estrutura de Dados/Assessments/Left_outer_join/join.txt");
    imprime_arquivo("/home/thiago/UFF/Estrutura de Dados/Assessments/Left_outer_join/join.txt");
}