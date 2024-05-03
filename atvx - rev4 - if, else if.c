#include <stdio.h>
#include <locale.h>

/*Construa uma algoritmo que tenha como dados de entrada o sexo e a altura de
uma pessoa (M-masculino e F-feminino), e calcule seu peso ideal, utilizando as
seguintes f�rmulas:
Para homens: (72.7*h)� 58, onde h � altura
Para mulheres: (62.1*h)- 44.7
*/
char sexo;
float altura, peso_ideal;


int main() {
	setlocale(LC_ALL, "Portuguese");

    printf("Digite o sexo da pessoa (M para masculino, F para feminino): ");
    scanf(" %c", &sexo);

    printf("Digite a altura da pessoa em metros: ");
    scanf("%f", &altura);

    if(sexo == 'M' || sexo == 'm') {
        peso_ideal = (72.7 * altura) - 58;
    } else if(sexo == 'F' || sexo == 'f') {
        peso_ideal = (62.1 * altura) - 44.7;
    } else {
        printf("Sexo inv�lido!\n");
        return 0;
    }

    printf("O peso ideal �: %.2f kg\n", peso_ideal);
	system("pause");
    return 0;
}
