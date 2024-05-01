#include <stdio.h>
#include <stdlib.h>
#include <locale.h> /*para a fun��o setlocate*/
#include <string.h> /*para a fun��o strcmp*/

/*Implemente uma algoritmo que represente a situa��o a seguir: Se a idade for maior ou
 igual 18 anos e idade menor ou igual 95 anos e o resultado do exame de legisla��o for
 APROVADO, ent�o apresentar a mensagem de sa�da 'Sua carteira de motorista estar� pronta
 em uma semana�. Caso contr�rio apresentar a mensagem de sa�da 'Voc� n�o possui idade
 permitida ou n�o passou no teste de legisla��o�*/

int idade;
char exame[10];


int main(){
	setlocale(LC_ALL, "Portuguese");
	
	printf("Digite sua idade: ");
    scanf("%d", &idade);
    printf("Digite o resultado do exame (APROVADO/REPROVADO): ");
    scanf("%s", &exame);
	if(idade >= 18 && idade <= 95 && strcmp(exame, "APROVADO") == 0){
        printf("Sua carteira de motorista estar� pronta em uma semana\n");
    }else{
        printf("Voc� n�o possui idade permitida e/ou n�o passou no teste de legisla��o\n");
    }
    system("pause");
}