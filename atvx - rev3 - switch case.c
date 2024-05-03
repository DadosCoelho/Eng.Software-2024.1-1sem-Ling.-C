#include <stdio.h>
#include <locale.h>

/*Elabore um algoritmo que seja capaz de representar um cardápio de uma
lanchonete, conforme o exemplo a seguir. No algoritmo deverá ser informado o
código do item pedido, a quantidade e calcule o valor a ser pago por aquele
lanche. Considere que a cada execução somente será calculado um item.

Especificação         	Código			Preço
Cachorro quente			100  			4,2
Bauru simples 			101				3,3
Bauru com ovo 			102 			5,5
Hambúrger 				103				6,2
Cheeseburguer 			104				5,3
Refrigerante 			105				4,5
*/

int codigo, quantidade;
float valor, total;


int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("Digite o código do item pedido: ");
    scanf("%d", &codigo);

    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);

    switch(codigo) {
        case 100:
            valor = 4.2;
            break;
        case 101:
            valor = 3.3;
            break;
        case 102:
            valor = 5.5;
            break;
        case 103:
            valor = 6.2;
            break;
        case 104:
            valor = 5.3;
            break;
        case 105:
            valor = 4.5;
            break;
        default:
            printf("Código inválido!\n");
            return 0;
    }

    total = valor * quantidade;

    printf("O valor a ser pago é: R$ %.2f\n", total);
	system("pause");
    return 0;
}
