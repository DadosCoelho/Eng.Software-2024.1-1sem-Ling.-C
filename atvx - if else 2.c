#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*Implemente uma algoritmo que represente a situa��o a seguir: Se a idade for
menor que 18 anos ou idade for maior que 95 anos, apresentar a mensagem de sa�da
'Voc� n�o pode tirar carteira de motorista�. Caso contr�rio apresentar a 
mensagem de sa�da 'Voc� pode possuir carteira de motorista�.*/

int idade;


int main(){
	setlocale(LC_ALL, "Portuguese");
	
	printf("Informe sua idade:\n");
	scanf("%d",&idade);
	if(idade >= 18 && idade <= 95){
		printf("Voc� pode possuir carteira de motorista");		
	}else{
		printf("Voc� n�o pode tirar carteira de motorista");
		}
}