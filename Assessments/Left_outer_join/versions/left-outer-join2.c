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
    FILE *arq_departamento, *arq_funcionario, *arq_join;
    TDepartamento *departamento;
    TFuncionario *funcionario;

    // Abre os arquivos de departamentos e funcionários para leitura
    arq_departamento = fopen(nome_arquivo_departamento, "r");
    arq_funcionario = fopen(nome_arquivo_funcionarios, "r");

    // Cria o arquivo de junção para escrita
    arq_join = fopen(nome_arquivo_join, "w");

    if (arq_departamento == NULL || arq_funcionario == NULL || arq_join == NULL) {
        printf("Erro ao abrir os arquivos\n");
        return;
    }

    departamento = le_departamento(arq_departamento);
    funcionario = le_funcionario(arq_funcionario);

    while (departamento != NULL) {
        if (funcionario != NULL && departamento->cod_departamento == funcionario->cod_departamento) {
            // Escreve os dados de departamento e funcionário no arquivo de junção
            fprintf(arq_join, "%d;%d;%s;%d;%s;\n", departamento->cod_departamento, departamento->sala, departamento->nome, funcionario->cod_funcionario, funcionario->nome);

            // Lê o próximo registro de funcionário
            free(funcionario);
            funcionario = le_funcionario(arq_funcionario);
        } else {
            // Escreve os dados de departamento sem funcionários no arquivo de junção
            fprintf(arq_join, "%d;%d;%s;0;\n", departamento->cod_departamento, departamento->sala, departamento->nome);
        }

        // Lê o próximo registro de departamento
        free(departamento);
        departamento = le_departamento(arq_departamento);
    }

    // Fecha os arquivos
    fclose(arq_departamento);
    fclose(arq_funcionario);
    fclose(arq_join);
}

int main() {
    leftOuterJoin("/home/thiago/UFF/Estrutura de Dados/Assessments/Left_outer_join/departamentos.txt", "/home/thiago/UFF/Estrutura de Dados/Assessments/Left_outer_join/Funcionarios.txt", "/home/thiago/UFF/Estrutura de Dados/Assessments/Left_outer_join/join.txt");
    imprime_arquivo("/home/thiago/UFF/Estrutura de Dados/Assessments/Left_outer_join/join.txt");
}