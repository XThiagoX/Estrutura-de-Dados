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

/* Executa insercao em Arquivos por Encadeamento Exterior (Hash)
 * cod_cli: chave do cliente que esta sendo inserido
 * nome_cli: nome do cliente a ser inserido
 * nome_arquivo_hash: nome do arquivo que contem a tabela hash
 * nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
 * Retorna o endereco (lógico) onde o cliente foi inserido, ou -1 se nao conseguiu inserir
 */
int hash (int cod_cli, int m){
    return cod_cli % m;
}

int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m) {
    TCliente *client = NULL;
    FILE *TableHash_file = fopen(nome_arquivo_hash, "rb+");
    FILE *Data_file = fopen(nome_arquivo_dados, "rb+");

    int baseAddress = hash(cod_cli, m);
    //printf("\n %d mod 7 = %d \n", cod_cli, baseAddress);
    if (TableHash_file == NULL ) {
        
        return -1;
    }
    if (Data_file == NULL){
        
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
            //imprime_cliente(client);
            // verificação da chave            
            if (client->cod == cod_cli)
            {
                printf("\n CHAVE EXISTENTE");
                fclose(TableHash_file);
                fclose(Data_file);                
                free(client);
                return -1;
            }                    
            addressClient = client->prox;            
            free(client);            
        }
        addressClient -1;
        fread(&addressClient, sizeof(int), 1, TableHash_file);
        while (addressClient != -1)
        {
            fseek(Data_file, addressClient * tamanho_cliente(), SEEK_SET);
            client = le_cliente(Data_file);
            // verifiacando se o registro é liberado
            if (client->ocupado != 1)
            {
                
            }
            
        }
        




        fclose(TableHash_file);
        fclose(Data_file);
        return addressClient;
    }        

    return INT_MAX;
}

int main() {
    /* Essa função gera a saída que é usada no teste do run.codes. Ela NÃO DEVE SER MODIFICADA */
    int cod;
    char nome[TAM_NOME] = "";
    int pont;

    //le dados a serem inseridos
    scanf("%d", &cod);
    scanf("%s", nome);

    //Imprime arquivos de entrada
    //imprime_arquivos("tabHash.dat", "clientes.dat");

    pont = insere(cod, nome, "tabHash.dat", "clientes.dat", M);
    imprime_arquivos("/home/thiago/UFF/Estrutura de Dados/Tabela Hash/tabHash.dat", "/home/thiago/UFF/Estrutura de Dados/Tabela Hash/clientes.dat");
    //Imprime resultado da função
    printf("\nRESULTADO: %d", pont);
}