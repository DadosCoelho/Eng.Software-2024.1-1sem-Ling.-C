#include <stdio.h>
#include <math.h>
#include <locale.h>

/* Implemente uma algoritmo que calcule a raiz quadrada de um numero descartando
a possibilidade do número ser igual a zero. Caso contrário isso aconteça
apresentar a mensagemde saída‘Informe um valor maior que zero’.*/

double num;
double raiz;

int main() {
    setlocale(LC_ALL, "Portuguese");
    printf("Informe um número: ");
    scanf("%lf", &num);

    if(num <= 0) {
        printf("Informe um valor maior que zero.\n");
    } else {
        raiz = sqrt(num);
        printf("A raiz quadrada de %.2lf é %.2lf\n", num, raiz);
    }
    system("pause");
    return 0;

}