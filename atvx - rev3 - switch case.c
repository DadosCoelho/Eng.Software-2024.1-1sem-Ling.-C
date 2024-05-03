#include <stdio.h>
#include <locale.h>

/*Elabore um algoritmo que seja capaz de representar um card�pio de uma
lanchonete, conforme o exemplo a seguir. No algoritmo dever� ser informado o
c�digo do item pedido, a quantidade e calcule o valor a ser pago por aquele
lanche. Considere que a cada execu��o somente ser� calculado um item.

Especifica��o         	C�digo			Pre�o
Cachorro quente			100  			4,2
Bauru simples 			101				3,3
Bauru com ovo 			102 			5,5
Hamb�rger 				103				6,2
Cheeseburguer 			104				5,3
Refrigerante 			105				4,5
*/

int codigo, quantidade;
float valor, total;


int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("Digite o c�digo do item pedido: ");
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
            printf("C�digo inv�lido!\n");
            return 0;
    }

    total = valor * quantidade;

    printf("O valor a ser pago �: R$ %.2f\n", total);
	system("pause");
    return 0;
}
