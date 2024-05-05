#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <ctype.h> // Biblioteca para usar a fun��o isdigit


int operacao;
float valor1,valor2,res;


void MenuCalculadora(){
	setlocale(LC_ALL, "Portuguese");
	printf("                      +=======================================+\n");
	printf("                      |          CALCULADORA SIMPLES          |\n");
	printf("                      +---------------------------------------+\n");
	printf("                      |      1-SOMA       |   2-SUBTRAIR      |\n");
	printf("                      +---------------------------------------+\n");
	printf("                      |   3-MULTIPLICAR   |    4-DIVIDIR      |\n");
	printf("                      +=======================================+\n");
	printf("                      Digite a opera��o desejada ou 5 para Sair\n");
	printf("                      ");

			char entrada[100]; // Tamanho arbitr�rio para a string
    		scanf("%s", entrada);
				// Verifica se a string cont�m apenas d�gitos
			int i = 0;
    		while (entrada[i] != '\0') {
  			    if (!isdigit(entrada[i])) {
  			    	system("cls");
    		    	printf("                      Op��o invalida!\n");
		        }
		        i++;
			}
			// Converte a string para inteiro
    		operacao = atoi(entrada);
}

void Entrada(){
	
	
	setlocale(LC_ALL, "Portuguese");
	
    	valor1 = 0;
        printf("                      Digite o primeiro valor:    ");
        scanf("%f", &valor1);
        if(valor1 > 9999999 || valor1 < -9999999){
			do{
			printf("                      Valor excedeu a capacidade de calculo!\n");
			printf("                      Digite o primeiro valor:    ");
		    scanf("%f", &valor1);		
			} while (valor1 > 9999999 || valor1 < -9999999);
		}

    	valor2 = 0;
        printf("                      Digite o segundo valor:     ");
        scanf("%f", &valor2);
        if(valor2 > 9999999 || valor2 < -9999999){
			do{
			printf("                      Valor excedeu a capacidade de calculo!\n");
			printf("                      Digite o segundo valor:    ");
	        scanf("%f", &valor2);		
			} while (valor2 > 9999999 || valor2 < -9999999);
		}
}

void Somar(){ //Fun��o que realiza a soma
	res = valor1+valor2;
	
}

void Subtrair(){ //Fun��o que realiza a subtra��o
	res = valor1-valor2;
	
}

void Multiplicar(){ //Fun��o que realiza a multiplica��o
	res = valor1*valor2;
	
}

void Dividir(){ //Fun��o que realiza a divis�o
	if(valor2 == 0) {
		system("cls");
		printf("                      Impossivel a divis�o por 0. \n");
	} else{
		res = valor1/valor2;
	}
	
}

void Saida(){
	setlocale(LC_ALL, "Portuguese");
	if(operacao == 4 && valor2 == 0) {
		system("cls");
		printf("                      Impossivel a divis�o por 0. \n");
	} else if(res > 19999998 || res < -19999998){
		printf("                      Valor excedeu a capacidade de calculo!\n");
	} else {
		printf("                      O Resultado da opera��o �:  %.2f\n", res);
	}
}



int main(){
	setlocale(LC_ALL, "Portuguese");
	do{
	system("cls");
	MenuCalculadora();
			switch(operacao)
		{
        case 0:
			system("pause");
			break;
		case 1:
			system("cls");
			printf("                      Para Somar\n");
			Entrada();
			Somar();
			Saida();
			system("pause");
			break;
		case 2:
			system("cls");
			printf("                      Para Subtrair\n");
			Entrada();
			Subtrair();
			Saida();
			system("pause");
			break;
		case 3:
			system("cls");
			printf("                      Para Multiplicar\n");
			Entrada();
			Multiplicar();
			Saida();
			system("pause");
			break;
		case 4:
			system("cls");
			printf("                      Para Dividir\n");
			Entrada();
			Dividir();
			Saida();
			system("pause");
			break;
		case 5:
			printf("Saindo...");
			break;
		default:
			system("cls");
			printf("                      Op��o invalida!\n");
			system("pause");
			break;
		}
		printf("\n\n");
	}while(operacao != 5);
	system("pause");
    return 0;

}