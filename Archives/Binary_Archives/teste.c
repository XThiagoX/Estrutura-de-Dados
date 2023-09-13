#include <stdio.h>

typedef struct Employee {
    int code;
    char name[50];
    char cpf[15];
    char birthday[11];
    double wage;
} TypeEmployee;

void assignEmployeeData(TypeEmployee *employee) {
    printf("Digite o código do funcionário: ");
    scanf("%d", &employee->code);

    printf("Digite o nome do funcionário: ");
    scanf("%s", employee->name);

    printf("Digite o CPF do funcionário: ");
    scanf("%s", employee->cpf);

    printf("Digite a data de nascimento do funcionário (DD/MM/AAAA): ");
    scanf("%s", employee->birthday);

    printf("Digite o salário do funcionário: ");
    scanf("%lf", &employee->wage);
}

int main() {
    TypeEmployee employee;
    assignEmployeeData(&employee);

    // Exemplo de impressão dos valores atribuídos
    printf("Código: %d\n", employee.code);
    printf("Nome: %s\n", employee.name);
    printf("CPF: %s\n", employee.cpf);
    printf("Data de nascimento: %s\n", employee.birthday);
    printf("Salário: %.2lf\n", employee.wage);

    return 0;
}
