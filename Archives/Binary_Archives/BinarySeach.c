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

TypeEmployee BinarySeach( FILE *archive, int fetched_key){
    // obtendo o tamnho do arquivo
    fseek(archive, 0, SEEK_END);
    long archive_size =  ftell(archive);
    // definindo os limites iniciais e final do arquivo
    long start = 0;
    long end = archive_size / sizeof(TypeEmployee) - 1;

    while (start <= end)
    {
        long middle = (start+end)/2;

        fseek(archive, middle * sizeof(TypeEmployee), SEEK_SET);

        // lendo o resistro do meio
        TypeEmployee employee;
        fread(&employee, sizeof(TypeEmployee), 1, archive);

        if (fetched_key == employee.code)
        {
            return employee;
        } else if (fetched_key < employee.code)
        {
            end = middle - 1;
        } else {
            start = middle + 1;
        }                                                
    }
    // caso o registro não encontrado
    TypeEmployee nullEmployee;
    nullEmployee.code = - 1;    
    return nullEmployee;
}

int main()
{
    TypeEmployee employee;
    FILE *archive;
    int fetched_key = 300;

    archive = fopen("/home/thiago/UFF/Estrutura de Dados/Archives/Files/Employees.txt", "rb");

    if (archive == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    

    employee = BinarySeach( archive, fetched_key);
    printf("\n Código empregado: %d ", employee.code);

    
    return 0;
}
