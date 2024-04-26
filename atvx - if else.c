#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

float salario;

/* Implemente uma algoritmo que represente a situação a seguir: Se salario maior
que 1800 reais e menor que 8000 mil reais, deverá ser apresentada a mensagem de
saída 'Salário válido para financiamento’. Caso contrário deverá ser apresentada
a mensagem de saída 'Salário fora da faixa permitida para financiamento‘*/

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	printf("Informe seu salário:\n");
	scanf("%f",&salario);
	if(salario <= 1800){
		printf("Salário fora da faixa permitida para financiamento");		
	}else{
		if(salario < 8000){
			printf("Salário válido para financiamento");
		}else{
			printf("Salário fora da faixa permitida para financiamento");
		}
	}
}