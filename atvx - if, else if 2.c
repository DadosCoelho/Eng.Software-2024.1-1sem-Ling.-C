#include <stdio.h>
#include <locale.h>

/*Escreva um algoritmo que determine o grau de obesidade de uma pessoa, sendo
fornecido o peso e a altura da pessoa. O grau de obesidade � determinado pelo
�ndice de massa corp�rea(IMC) (massa=peso/altura2) atrav�s da tabela abaixo:
 Indice Massa corp�rea			Grau de obesidade
 <26							Normal
 >=26 e <30						Obeso
 >=30							Obeso m�rbido*/

float peso, altura, imc;

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("Digite seu peso em kg: ");
    scanf("%f", &peso);

    printf("Digite sua altura em metros: ");
    scanf("%f", &altura);

    imc = peso / (altura * altura);

    if (imc < 26) {
        printf("Grau de obesidade: Normal\n");
    } else if (imc >= 26 && imc < 30) {
        printf("Grau de obesidade: Obeso\n");
    } else {
        printf("Grau de obesidade: Obeso m�rbido\n");
    }
	system("pause");
    return 0;
}
