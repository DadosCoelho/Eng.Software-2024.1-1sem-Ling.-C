#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//Declaração de entrada das variaveis
int operador;

char nomeCliente[40];
char cpf[11];
char dataNasc[10];
int quantDependente;
float valorIndividual, valorTotal;

char nomeCliente_odonto[40];
char cpf_odonto[11];
char dataNasc_odonto[10];
int quantDependente_odonto;
float valorIndividual_odonto, valorTotal_odonto;

float valorTotalGeral;
int tipoPlano;
int main(){
	setlocale(LC_ALL, "Portuguese_Brasil");
	do{
	printf("Informe seu tipo de plano 1-Saude ou 0-Odonto\n ");
	scanf("%d", &tipoPlano);
		if(tipoPlano==1){
		do{
		printf("Informe o nome \n");
		scanf("%s", &nomeCliente);
		printf("Informe o cpf\n");
		scanf("%s", &cpf);
		printf("Informe a data de nascimento\n");
		scanf("%s", &dataNasc);
		printf("Informe a quantidade de dependentes\n");
		scanf("%d", &quantDependente);
		valorIndividual=120;
		valorTotal=valorIndividual*quantDependente;
		printf("Cliente..............: %s\n", nomeCliente);
		printf("CPF..................: %s\n", cpf);
		printf("Data de Nascimento...: %s\n", dataNasc);
		printf("Qtd de Dependente....: %d\n", quantDependente);
		printf("Valor da Fatura......: %.2f ", valorTotal);
		printf("\nDeseja recalcular o plano novamente? 1-sim ou 0-sair\n");
		scanf("%d", &operador);
		}while(operador!=0);
	}else{
		do{
		printf("Informe o nome \n");
		scanf("%s", &nomeCliente_odonto);
		printf("Informe o cpf\n");
		scanf("%s", &cpf_odonto);
		printf("Informe a data de nascimento\n");
		scanf("%s", &dataNasc_odonto);
		printf("Informe a quantidade de dependentes\n");
		scanf("%d", &quantDependente_odonto);
		valorIndividual_odonto=80;
		valorTotal_odonto=valorIndividual_odonto*quantDependente_odonto;
		printf("Cliente..............: %s\n", nomeCliente_odonto);
		printf("CPF..................: %s\n", cpf_odonto);
		printf("Data de Nascimento...: %s\n", dataNasc_odonto);
		printf("Qtd de Dependente....: %d\n", quantDependente_odonto);
		printf("Valor da Fatura......: %.2f ", valorTotal_odonto);
		printf("\nDeseja recalcular o plano novamente? 1-sim ou 0-sair\n");
		scanf("%d", &operador);
		}while(operador!=0);
	}
	valorTotalGeral=valorTotal+valorTotal_odonto;
	printf("O valor total da fatura é %.2f\n", valorTotalGeral);
	printf("\nDeseja calcular outro plano? 1-sim ou 0-sair\n");
	scanf("%d", &operador);
	}while(operador!=0);
	
	
	
	
	
	
}
