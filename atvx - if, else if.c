#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/* Implemente uma algoritmo que capaz de imprimir o m�s do ano, sendo que quando
o usu�rio digitar entre o intervalo de 1 a 12 ser� impresso o m�s correspondente
ao n�mero (Ex. Se o usu�rio digitar o n�mero 3 dever� ser impresso o m�s de
MAR�O). O algoritmo dever� prever os valores digitados fora desse intervalo
estabelecido.*/

int mes;
char *meses[] = {"JANEIRO", "FEVEREIRO", "MAR�O", "ABRIL", "MAIO", "JUNHO",
 	 	 	 	 "JULHO", "AGOSTO", "SETEMBRO", "OUTUBRO", "NOVEMBRO",
			   	 "DEZEMBRO"};
int main(){
    setlocale(LC_ALL, "Portuguese");
    

    
    printf("Digite o digito do m�s: (DE 1 A 12) ");
    scanf("%d", &mes);
    
    if(mes >= 1 && mes <= 12){
        printf("%s\n", meses[mes-1]);
    } else {
        printf("FORAM DIGITADOS NUMEROS FORAS DO INTERVALO\n");
    }
    system("pause");
    return 0;
}