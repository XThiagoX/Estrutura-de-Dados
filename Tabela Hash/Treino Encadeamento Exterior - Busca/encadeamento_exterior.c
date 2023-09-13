#include <limits.h>
#include <stdio.h>

#include "cliente.c"
#include "compartimento_hash.c"

#define M 7

void imprime_arquivos(char *nome_arquivo_hash, char *nome_arquivo_dados) {
    //Imprime arquivo de hash
    printf("TABELA HASH:\n");
    imprime_arquivo_hash(nome_arquivo_hash);

    //Imprime arquivo de dados
    printf("\nDADOS:\n");
    imprime_arquivo_dados(nome_arquivo_dados);
}

/* Executa busca em Arquivos por Encadeamento Exterior (Hash)
 * Assumir que ponteiro para proximo noh eh igual a -1 quando nao houver proximo noh
 * Ponteiros são lógicos (é preciso multiplicar pelo tamanho do registro para calcular o valor do deslocamento
 * Use a função tamanho_compartimento() e tamanho_cliente() dependendo do arquivo que está sendo manipulado
 *
 * Parametros:
 * cod_cli: chave do cliente que esta sendo buscado
 * nome_arquivo_hash: nome do arquivo que contem a tabela hash
 * nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
 * m: tamanho da tabela hash (a função de hash é h(x) = x mod m
 *
 * Retorna o endereco (lógico) onde o cliente foi encontrado, ou -1 se nao for encontrado
 */
int hash (int cod_cli, int m){
    return cod_cli % m;
}

int busca(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m) {
    TCliente *client = NULL;
    FILE *TableHash_file = fopen(nome_arquivo_hash, "rb");
    FILE *Data_file = fopen(nome_arquivo_dados, "rb");

    int baseAddress = hash(cod_cli, m);
    //printf("\n %d mod 7 = %d \n", cod_cli, baseAddress);
    if (TableHash_file == NULL ) {
        //printf("Erro ao abrir arquivos de Hash");
        return -1;
    }
    if (Data_file == NULL){
        //printf("Erro ao abrir arquivos de Dados");
        return -1;
    }
    else
    {   // cursor para posição do endereço base
        fseek(TableHash_file, baseAddress * tamanho_compartimento(), SEEK_SET);
        // leitura de endereço base. 1º da lista de clientes
        int addressClient = -1;
        fread(&addressClient, sizeof(int), 1, TableHash_file);
        // busca pela chave na lista de clienes         
        while (addressClient != -1) {  
            // cursor para o endereço do cliente na lista de clientes
            fseek(Data_file, addressClient * tamanho_cliente(), SEEK_SET);
            client = le_cliente(Data_file);
            imprime_cliente(client);
            // verificação da chave            
            if (client->cod == cod_cli && client->ocupado == 1)
            {
                fclose(TableHash_file);
                fclose(Data_file);
                printf("\n ocupado = %d", client->ocupado);
                free(client);
                return addressClient;
            }                    
            addressClient = client->prox;            
            free(client);            
        }
        fclose(TableHash_file);
        fclose(Data_file);
        return addressClient;
    }        
}


int main() {
    /* Essa função gera a saída que é usada no teste do run.codes. Ela NÃO DEVE SER MODIFICADA */
    int cod;
    int pont;

    //Imprime arquivos de entrada
    //imprime_arquivos("tabHash.dat", "clientes.dat");

    //le chave a ser buscada
    scanf("%d", &cod);
    printf("REGISTROS ACESSADOS:\n");
    pont = busca(cod, "/home/thiago/UFF/Estrutura de Dados/Tabela Hash/Treino Encadeamento Exterior - Busca/tabHash.dat", "/home/thiago/UFF/Estrutura de Dados/Tabela Hash/Treino Encadeamento Exterior - Busca/clientes.dat", M);

    //Imprime resultado da função
    printf("RESULTADO: %d", pont);
}