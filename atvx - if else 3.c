#include <stdio.h>
#include <stdlib.h>
#include <locale.h> /*para a função setlocate*/
#include <string.h> /*para a função strcmp*/

/*Implemente uma algoritmo que represente a situação a seguir: Se a idade for maior ou
 igual 18 anos e idade menor ou igual 95 anos e o resultado do exame de legislação for
 APROVADO, então apresentar a mensagem de saída 'Sua carteira de motorista estará pronta
 em uma semana’. Caso contrário apresentar a mensagem de saída 'Você não possui idade
 permitida ou não passou no teste de legislação’*/

int idade;
char exame[10];


int main(){
	setlocale(LC_ALL, "Portuguese");
	
	printf("Digite sua idade: ");
    scanf("%d", &idade);
    printf("Digite o resultado do exame (APROVADO/REPROVADO): ");
    scanf("%s", &exame);
	if(idade >= 18 && idade <= 95 && strcmp(exame, "APROVADO") == 0){
        printf("Sua carteira de motorista estará pronta em uma semana\n");
    }else{
        printf("Você não possui idade permitida e/ou não passou no teste de legislação\n");
    }
    system("pause");
}