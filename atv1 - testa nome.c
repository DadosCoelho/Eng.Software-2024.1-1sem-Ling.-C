#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

char Nome [40];
char SobreNome [40];

/*Fun��o principal do algoritimo*/
int main(){
	setlocale(LC_ALL, "Portuguese_Brasil");
/*Entrada de dados*/
	printf("Informe seu primeiro nome\n");
	scanf("%s", &Nome);
	printf("Informe seu sobrenome\n");
	scanf("%s", &SobreNome);	
/*Impress�o dos dados*/
	printf("Nome completo: %s" , Nome);
	printf(" %s" , SobreNome);
}