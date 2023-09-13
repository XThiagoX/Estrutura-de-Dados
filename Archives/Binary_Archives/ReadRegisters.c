#include <stdio.h>
#include <stdlib.h>

typedef struct Employee {
    int code;
    char name[50];
    char cpf[15];
    char birthday[11];
    double wage;
} TypeEmployee;

int size_register() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //salario
}

int archive_size(FILE *archive){
    fseek(archive, 0, SEEK_END);
    int size = trunc( ftell(archive) / size_register());
    return size;
}

TypeEmployee *read(FILE *file){
    TypeEmployee *employee = (TypeEmployee *) malloc(sizeof(TypeEmployee));
    if (0 >= fread(&employee->code, sizeof(int), 1, file)) 
    {
        free(employee);
        return NULL;
    }    
    fread(employee->name, sizeof(char), sizeof(employee->name), file);
    fread(employee->cpf, sizeof(char), sizeof(employee->cpf), file);
    fread(employee->birthday, sizeof(char), sizeof(employee->birthday), file);
    fread(&employee->wage, sizeof(double), 1, file);
    return employee;                    
}

int main()
{
    TypeEmployee employee;
    FILE *readingFile;

    readingFile = fopen("/home/thiago/UFF/Estrutura de Dados/Archives/Files/Employees.txt", "rb");

    if (readingFile!= NULL)
    {                
        printf("\nExibindo os dados gravados no arquivo binário:\n");

        TypeEmployee *reading_employee = (TypeEmployee *) malloc(sizeof(TypeEmployee));
        reading_employee = read(readingFile); 
        if (reading_employee != NULL)
        {
            printf("Código: %d\n", reading_employee->code);
            printf("Nome: %s\n", reading_employee->name);
            printf("CPF: %s\n", reading_employee->cpf);
            printf("Data de nascimento: %s\n", reading_employee->birthday);
            printf("Salário: %.2lf\n", reading_employee->wage);

            printf("\n o arquivo tem %d registros armazenados\n", archive_size(readingFile));
        }
        else{
            printf("\n o arquivo não contem dados.");
        }                
    }
    else
    {
        printf("\nerror\n");
    }    
    
    return 0;
}
