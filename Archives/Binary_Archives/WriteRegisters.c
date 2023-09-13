#include <stdio.h>
#include <stdlib.h>

typedef struct Employee {
    int code;
    char name[50];
    char cpf[15];
    char birthday[11];
    double wage;
} TypeEmployee;

void assignEmployeeValues(TypeEmployee *employee){
    printf("Digite o código do funcionário: ");
    scanf("%d", &employee->code);

    printf("Digite o nome do funcionário: ");
    scanf("%s", &employee->name);

    printf("Digite o CPF do funcionário: ");
    scanf("%s", &employee->cpf);

    printf("Digite a data de nascimento do funcionário (DD/MM/AAAA): ");
    scanf("%s", &employee->birthday);

    printf("Digite o salário do funcionário: ");
    scanf("%lf", &employee->wage);  
}

void save( TypeEmployee *employee, FILE *writingFile){
    fwrite(&employee->code, sizeof(int), 1, writingFile);    
    fwrite(employee->name, sizeof(char), sizeof(employee->name), writingFile);
    fwrite(employee->cpf, sizeof(char), sizeof(employee->cpf), writingFile);
    fwrite(employee->birthday, sizeof(char), sizeof(employee->birthday), writingFile);
    fwrite(&employee->wage, sizeof(double), 1, writingFile); 
}

int main()
{
    TypeEmployee employee;
    FILE *writingFile;

    writingFile = fopen("/home/thiago/UFF/Estrutura de Dados/Archives/Files/Employees.txt", "ab+");

    if (writingFile!= NULL)
    {
        assignEmployeeValues(&employee);           
        save(&employee, writingFile);           
    }
    else
    {
        printf("\nerror\n");
    }    
    
    return 0;
}
