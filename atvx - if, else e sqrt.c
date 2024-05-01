#include <stdio.h>
#include <math.h>
#include <locale.h>

/* Implemente uma algoritmo que calcule a raiz quadrada de um numero descartando
a possibilidade do n�mero ser igual a zero. Caso contr�rio isso aconte�a
apresentar a mensagemde sa�da�Informe um valor maior que zero�.*/

double num;
double raiz;

int main() {
    setlocale(LC_ALL, "Portuguese");
    printf("Informe um n�mero: ");
    scanf("%lf", &num);

    if(num <= 0) {
        printf("Informe um valor maior que zero.\n");
    } else {
        raiz = sqrt(num);
        printf("A raiz quadrada de %.2lf � %.2lf\n", num, raiz);
    }
    system("pause");
    return 0;

}