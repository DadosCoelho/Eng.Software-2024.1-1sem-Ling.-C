#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/* Implemente uma algoritmo que capaz de imprimir o mês do ano, sendo que quando
o usuário digitar entre o intervalo de 1 a 12 será impresso o mês correspondente
ao número (Ex. Se o usuário digitar o número 3 deverá ser impresso o mês de
MARÇO). O algoritmo deverá prever os valores digitados fora desse intervalo
estabelecido.*/

int mes;
char *meses[] = {"JANEIRO", "FEVEREIRO", "MARÇO", "ABRIL", "MAIO", "JUNHO",
 	 	 	 	 "JULHO", "AGOSTO", "SETEMBRO", "OUTUBRO", "NOVEMBRO",
			   	 "DEZEMBRO"};
int main(){
    setlocale(LC_ALL, "Portuguese");
    

    
    printf("Digite o digito do mês: (DE 1 A 12) ");
    scanf("%d", &mes);
    
    if(mes >= 1 && mes <= 12){
        printf("%s\n", meses[mes-1]);
    } else {
        printf("FORAM DIGITADOS NUMEROS FORAS DO INTERVALO\n");
    }
    system("pause");
    return 0;
}