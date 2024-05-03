#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int operacao,valor1,valor2,res;


void MenuCalculadora(){
	setlocale(LC_ALL, "Portuguese");
	printf("   +=======================================+\n");
	printf("   |            CALCULADORA SIMPLES        |\n");
	printf("   +---------------------------------------+\n");
	printf("   |      1-SOMA       |   2-SUBTRAIR      |\n");
	printf("   +---------------------------------------+\n");
	printf("   |   3-MULTIPLICAR   |    4-DIVIDIR      |\n");
	printf("   +=======================================+\n");
	printf("  Digite a operação desejada ou 5 para Sair\n");	
	scanf("%d", &operacao);	
	
}

void Entrada(){
	valor1 = 0;
	valor2 = 0;
	setlocale(LC_ALL, "Portuguese");
	printf("Digite o primeiro valor:\n");
	scanf("%d",&valor1);
	printf("Digite o segundo valor:\n");
	scanf("%d", &valor2);
	
}

void Somar(){ //Função que realiza a soma
	res = valor1+valor2;
	
}

void Subtrair(){
	res = valor1-valor2;
	
}

void Multiplicar(){
	res = valor1*valor2;
	
}

void Dividir(){
	res = valor1/valor2;
	
}

void Saida(){
	setlocale(LC_ALL, "Portuguese");
	printf("O Resultado da operação é: %d\n", res);
}



int main(){
	setlocale(LC_ALL, "Portuguese");
	do{
	MenuCalculadora();
			switch(operacao)
		{
		case 1:
			system("cls");
			Entrada();
			Somar();
			Saida();
			break;
		case 2:
			system("cls");
			Entrada();
			Subtrair();
			Saida();
			break;
		case 3:
			system("cls");
			Entrada();
			Multiplicar();
			Saida();
			break;
		case 4:
			system("cls");
			Entrada();
			Dividir();
			Saida();
			break;
		case 5:
			printf("Saindo...");
			break;
		default:
			printf("Opção invalida!\n");
			break;
		}
	}while(operacao != 5);
	system("pause");
    return 0;

}