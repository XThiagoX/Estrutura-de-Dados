#include <stdio.h>
#include <stdlib.h>

void read_character(){
    FILE *archive;

    archive = fopen("/home/thiago/UFF/Estrutura de Dados/Archives/read_archives/numeros.txt", "r");
    // /home/thiago/UFF/Estrutura de Dados/Archives/read_archives/numeros.txt
    // Archives/read_archives/numeros.txt
    if (archive != NULL)
    {        
        char character;        

        while (( character = fgetc(archive)) != EOF) // lê o tipo char e testa se chegou ao fim do arquivo
        {
            printf("%c",character);
        }        
        fclose(archive);
    }
    else
    {
        printf("\nnada ok!\n");
    }    
}

void read_string(){
    FILE *archive;

    archive = fopen("/home/thiago/UFF/Estrutura de Dados/Archives/read_archives/numeros.txt", "r");

    if (archive != NULL)
    {
        int number;
        fscanf(archive, "%d", &number);
        while (!feof(archive)) // ou: while(fscanf(arq, “%s”, s) != EOF) {
        {
            printf("%d ", number);
            fscanf(archive, "%d", &number);
        }
        printf("\n");
        fclose(archive);
    }else{
        printf("\nnada ok!\n");
    }
    
}

void write_strings(){
    FILE *archive;
    archive = fopen("/home/thiago/UFF/Estrutura de Dados/Archives/white_archives/numeros.txt", "w");
    /* no modo 'w' é feita a abertura do arquivo,
        se ja existir, conteúdo no arquivo ele é apagado. 
        se não existir, é criado.*/

    if (archive != NULL)
    {
        for (int i = 10; i < 100; i = i + 3)
        {
            fprintf(archive, "%d\n", i); 
        }
        printf("Gravação feita\n");  
        fclose(archive);
    }
    else
    {
        printf("\n erro");   
    }
    
    
}

int main(int argc, char const *argv[])
{
    printf("\nFazendo leitura caracter por caracter: \n");
    read_character();
    printf("\nFazendo leitura linha por linha: \n");
    read_string();
    write_strings();
    return 0;
}
