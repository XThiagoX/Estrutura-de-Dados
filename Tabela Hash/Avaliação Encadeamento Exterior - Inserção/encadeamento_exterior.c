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
    // cursor para posição do endereço base
    fseek(TableHash_file, baseAddress * tamanho_compartimento(), SEEK_SET);
    // leitura de endereço base. 1º da lista de clientes
    int addressClient = -1;
    int address_clientReleased = -1;
    int prox_clientReleased = -1;
    fread(&addressClient, sizeof(int), 1, TableHash_file);
    if (addressClient == -1)
    {
        
        TCliente *newCliente = cliente(cod_cli, nome_cli, -1, 1);
        fseek(Data_file, 0, SEEK_END);
        
        int address_newclient = ftell(Data_file) / tamanho_cliente();

        // Escrever o novo cliente no final do arquivo de dados
        salva_cliente(newCliente, Data_file);

        // Atualizar o endereço do primeiro cliente na lista encadeada do compartimento
        fseek(TableHash_file, baseAddress * tamanho_compartimento(), SEEK_SET);
        fwrite(&address_newclient, sizeof(int), 1, TableHash_file);

        // Fechar arquivos
        fclose(TableHash_file);
        fclose(Data_file);

        // Liberar memória do novo cliente
        free(newCliente);

        // Retornar o endereço lógico do novo cliente
        return address_newclient;
    }
    
    // busca pela chave na lista de clienes         
    while (addressClient != -1) {  
        // cursor para o endereço do cliente na lista de clientes
        fseek(Data_file, addressClient * tamanho_cliente(), SEEK_SET);
        client = le_cliente(Data_file);
        //imprime_cliente(client);
        // verificação da chave            
        if (client->cod == cod_cli && client->ocupado == 1)
        {
            printf("\n CHAVE EXISTENTE\n");
            fclose(TableHash_file);
            fclose(Data_file);                
            free(client);
            return -1;
        }  
        // obtendo o ultimo cliente liberado
        if (client->ocupado != 1)
        {
            prox_clientReleased = client->prox;
            address_clientReleased = addressClient;
        }               
        addressClient = client->prox;            
        free(client);            
    }
    fseek(TableHash_file, baseAddress * tamanho_compartimento(), SEEK_SET);
    addressClient = -1;
    fread(&addressClient, sizeof(int), 1, TableHash_file);    
    // Busca de posição para inserção
    while (addressClient != -1)
    {
        fseek(Data_file, addressClient * tamanho_cliente(), SEEK_SET);
        client = le_cliente(Data_file);
        // verifiacando se há registro liberado
        if (address_clientReleased != -1)
        {   // atualização
            strcpy(client->nome, nome_cli);
            client->cod = cod_cli;       
            client->prox = prox_clientReleased;
            client->ocupado = 1;
            // Movendo o cursor para o endereço do cliente liberdo e sobrescrevê-lo
            fseek(Data_file, address_clientReleased * tamanho_cliente(), SEEK_SET);
            salva_cliente(client, Data_file);

            fclose(TableHash_file);
            fclose(Data_file);
            free(client);

            return address_clientReleased;
        }
        // chave não existe - adicionar cliente.
        if (client->prox == -1)
        {
            // endereço de cliente atual (ultimo da lista)
            int address_LastClient = addressClient;
            // adicionar
            TCliente *newClient = cliente(cod_cli, nome_cli, -1, 1);
            fseek(Data_file, 0, SEEK_END);                
            int address_newClient = ftell(Data_file) / tamanho_cliente();                
            salva_cliente(newClient, Data_file);
            // atulizando ponteiro do cliente atual para o novo
            client->prox = address_newClient;
            fseek(Data_file, address_LastClient * tamanho_cliente() + sizeof(int), SEEK_SET);
            fwrite(&address_newClient, sizeof(int), 1, Data_file);

            fclose(TableHash_file);
            fclose(Data_file);
            free(client);

            return address_newClient;
        }            
        addressClient = client->prox;
    }
    fclose(TableHash_file);
    fclose(Data_file);
    free(client);
        
    return -1;
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
    ///home/thiago/UFF/Estrutura de Dados/Tabela Hash/Avaliação Encadeamento Exterior - Inserção/clientes.dat
    ///home/thiago/UFF/Estrutura de Dados/Tabela Hash/Avaliação Encadeamento Exterior - Inserção/tabHash.dat
    pont = insere(cod, nome, "/home/thiago/UFF/Estrutura de Dados/Tabela Hash/Avaliação Encadeamento Exterior - Inserção/tabHash.dat", "/home/thiago/UFF/Estrutura de Dados/Tabela Hash/Avaliação Encadeamento Exterior - Inserção/clientes.dat", M);
    imprime_arquivos("/home/thiago/UFF/Estrutura de Dados/Tabela Hash/Avaliação Encadeamento Exterior - Inserção/tabHash.dat", "/home/thiago/UFF/Estrutura de Dados/Tabela Hash/Avaliação Encadeamento Exterior - Inserção/clientes.dat");
    //pont = insere(cod, nome, "tabHash.dat", "clientes.dat", M);
    //imprime_arquivos("tabHash.dat", "clientes.dat");
    //Imprime resultado da função
    printf("\nRESULTADO: %d", pont);
}