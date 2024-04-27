#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*Implemente uma algoritmo que represente a situação a seguir: Se a idade for
menor que 18 anos ou idade for maior que 95 anos, apresentar a mensagem de saída
'Você não pode tirar carteira de motorista’. Caso contrário apresentar a 
mensagem de saída 'Você pode possuir carteira de motorista’.*/

int idade;


int main(){
	setlocale(LC_ALL, "Portuguese");
	
	printf("Informe sua idade:\n");
	scanf("%d",&idade);
	if(idade >= 18 && idade <= 95){
		printf("Você pode possuir carteira de motorista");		
	}else{
		printf("Você não pode tirar carteira de motorista");
		}
}