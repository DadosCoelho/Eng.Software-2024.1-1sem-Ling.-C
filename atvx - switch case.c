#include <stdio.h>
#include <locale.h>

/*Implemente um algoritmo em C para classificar os nadadores escritos em uma 
competição de acordo com a idade informada indicar a categoria do atleta:
 • infantil A = 5 a 7 anos
 • infantil B = 8 a 10 anos
 • juvenil A = 11 a 13 anos
 • juvenil B = 14 a 17 anos
 • adulto = maiores de 18 anos*/

int idade;

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("Digite a idade do nadador: ");
    scanf("%d", &idade);

    switch(idade) {
        case 5:
        case 6:
        case 7:
            printf("Categoria: Infantil A\n");
            break;
        case 8:
        case 9:
        case 10:
            printf("Categoria: Infantil B\n");
            break;
        case 11:
        case 12:
        case 13:
            printf("Categoria: Juvenil A\n");
            break;
        case 14:
        case 15:
        case 16:
        case 17:
            printf("Categoria: Juvenil B\n");
            break;
        default:
            if (idade >= 18) {
                printf("Categoria: Adulto\n");
            } else {
                printf("Idade inválida\n");
            }
    }
	system("pause");
    return 0;
}
