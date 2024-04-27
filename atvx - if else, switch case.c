#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int num1, num2, num3, maior;

int main(){
    setlocale(LC_ALL, "Portuguese");
    
    printf("Digite o primeiro número: ");
    scanf("%d", &num1);

    printf("Digite o segundo número: ");
    scanf("%d", &num2);

    printf("Digite o terceiro número: ");
    scanf("%d", &num3);
    
    if (num1 == num2 && num2 == num3) {
        maior = -1; // Todos os números são iguais
    } else if (num1 >= num2 && num1 >= num3) {
        maior = 1;
    } else if (num2 >= num1 && num2 >= num3) {
        maior = 2;
    } else {
        maior = 3;
    }

    switch (maior) {
        case 1:
            printf("O maior número é: %d\n", num1);
            break;
        case 2:
            printf("O maior número é: %d\n", num2);
            break;
        case 3:
            printf("O maior número é: %d\n", num3);
            break;
        default:
            printf("Todos os valores digitados são iguais\n");
            break;
    }

}
