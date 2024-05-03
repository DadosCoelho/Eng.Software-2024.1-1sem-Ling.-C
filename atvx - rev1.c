#include <stdio.h>
#include <locale.h>

/*Sabendo que 100 quilowatts de energia custam um sétimo do salário mínimo,
fazer um algoritmo que dados a valor do salário mínimo e a quantidade de
quilowatts gastos por uma residência, exibir: valor em de cada quilowatt, valor
da conta de energia e novo valor da conta de energia após um desconto de 10%.*/
float salario_minimo, quilowatts, valor_quilowatt, valor_conta, valor_desconto;

int main() {
	setlocale(LC_ALL, "Portuguese");
    
    printf("Digite o valor do salário mínimo: ");
    scanf("%f", &salario_minimo);

    printf("Digite a quantidade de quilowatts gastos: ");
    scanf("%f", &quilowatts);

    valor_quilowatt = salario_minimo / 700; // 100 quilowatts custam 1/7 do salário mínimo
    valor_conta = valor_quilowatt * quilowatts;
    valor_desconto = valor_conta * 0.9; // desconto de 10%

    printf("Valor de cada quilowatt: R$ %.2f\n", valor_quilowatt);
    printf("Valor da conta de energia: R$ %.2f\n", valor_conta);
    printf("Novo valor da conta de energia após um desconto de 10%%: R$ %.2f\n", valor_desconto);
	system("pause");
    return 0;
}
