#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int OpMenuPrinc, OpSubMenuCad, matricula, i;
char nome[40];

void MenuPrincipal(){
	setlocale(LC_ALL, "Portuguese");
	printf("                      +=======================================+\n");
	printf("                      |          TEMPLATE DO PROJETO          |\n");
	printf("                      +---------------------------------------+\n");
	printf("                      |    1-OP��O I      |     2-OP��O II    |\n");
	printf("                      +---------------------------------------+\n");
	printf("                      |   3-OP��O III     |     4-OP��O IV    |\n");
	printf("                      +=======================================+\n");
	printf("                      ");
}

void CadastroI (){
	for(i=0;i<5;i++){
		printf("Ordem %d:\n", i);
		printf("Informe sua matricula\n");
		scanf("%d", &matricula);
		printf("Informe seu nome\n");
		scanf("%s", &nome);
	}
}

void SubMenuCadastro(){
	do{
		printf("                      +=======================================+\n");
		printf("                      |            CADASTRO EM GERAL          |\n");
		printf("                      +---------------------------------------+\n");
		printf("                      |   1-CADASTRO I    |   2-CADASTRO II   |\n");
		printf("                      +---------------------------------------+\n");
		printf("                      |  3-CADASTRO III   |   4-CADASTRO IV   |\n");
		printf("                      +=======================================+\n");
	    printf("             Digite a opera��o desejada ou 5 para voltar ao Menu Principal\n");
		scanf("%d", &OpSubMenuCad);
		switch(OpSubMenuCad)
		{
		case 1:
			system("cls");
			CadastroI();
		    break;
		case 2:
			system("cls");
			system("calc.exe");
			//Cadastro
		    break;
		case 3:
			system("cls");
			//Cadastro
		    break;
		case 4:
			system("cls");
			//Cadastro
		    break;
		default:
			printf("Opera��o Invalida\n");
			break;
		}
	}while(OpSubMenuCad != 5);
		MenuPrincipal();		
	
}


int main(){
	setlocale(LC_ALL, "Portuguese");
	MenuPrincipal();
	printf("Informe a op��o desejada ou 0 para sair\n");
	scanf("%d", &OpMenuPrinc);
	switch(OpMenuPrinc)
	{
	case 1:
		system("cls");
		SubMenuCadastro();
		break;
	case 2:
		system("cls");
		printf("O Cadastro II est� sendo desemvolvido");
		break;
	case 3:
		system("cls");
		printf("O Cadastro III est� sendo desemvolvido");
		break;
	case 4:
		system("cls");
		printf("O Cadastro IV est� sendo desemvolvido");
		break;
	default:
		break;
	}
	return 0;
	
}