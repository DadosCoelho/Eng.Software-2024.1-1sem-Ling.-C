#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int operador;
char NomeAluno [40];
float Nota1,Nota2,Nota3, Media;


/*Implemente o algoritimo que receba o nome do aluno e calcule a m�dia de 
tr�s notas e imprima o nome do aluno e a m�dia*/

int main(){
	setlocale(LC_ALL, "Portuguese_Brasil");
	do{
		printf("\nInforme o nome do al�no:\n");
		scanf("%s", &NomeAluno);
		printf("\nInforme a primeira nota:\n");
		scanf("%f", &Nota1);
		printf("\nInforme a segunda nota:\n");
		scanf("%f", &Nota2);
		printf("\nInforme a terceira nota:\n");
		scanf("%f", &Nota3);
		Media=(Nota1+Nota2+Nota3)/3;
		printf("\nNome do aluno: %s", NomeAluno);
		printf("\nO resultado da m�dia do aluno: %.2f \n", Media);	
		printf("\nDeseja calcular outra m�dia? 1-sim ou 0-sair\n");
		scanf("%d", &operador);
	}while(operador!=0);
	system("pause");
	
}

