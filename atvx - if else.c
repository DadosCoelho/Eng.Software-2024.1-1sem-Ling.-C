#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

float salario;

/* Implemente uma algoritmo que represente a situa��o a seguir: Se salario maior
que 1800 reais e menor que 8000 mil reais, dever� ser apresentada a mensagem de
sa�da 'Sal�rio v�lido para financiamento�. Caso contr�rio dever� ser apresentada
a mensagem de sa�da 'Sal�rio fora da faixa permitida para financiamento�*/

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	printf("Informe seu sal�rio:\n");
	scanf("%f",&salario);
	if(salario <= 1800){
		printf("Sal�rio fora da faixa permitida para financiamento");		
	}else{
		if(salario < 8000){
			printf("Sal�rio v�lido para financiamento");
		}else{
			printf("Sal�rio fora da faixa permitida para financiamento");
		}
	}
}