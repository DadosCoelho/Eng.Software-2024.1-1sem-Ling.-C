#include <stdio.h>
#include <string.h>
#include <locale.h>

/*Implemente um Algoritmo em C que receba via teclado a sigla dos estados(UF) do
Nordeste e seja impresso Ex. Se informado PE �Voc� � Pernambucano�Se PI �Voc� �
Piauiense� etc.*/

char uf[3];
int i;

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("Digite a sigla do seu estado (UF): ");
    scanf("%s", uf);

    //Convertendo para mai�sculas para evitar problemas de case
    for(i = 0; uf[i]; i++){
        uf[i] = toupper(uf[i]);
    }

    if (strcmp(uf, "AC") == 0) {
        printf("Voc� � Acreano\n");
    } else if (strcmp(uf, "AL") == 0) {
        printf("Voc� � Alagoano\n");
    } else if (strcmp(uf, "AP") == 0) {
        printf("Voc� � Amapaense\n");
    } else if (strcmp(uf, "AM") == 0) {
        printf("Voc� � Amazonense\n");
    } else if (strcmp(uf, "BA") == 0) {
        printf("Voc� � Baiano\n");
    } else if (strcmp(uf, "CE") == 0) {
        printf("Voc� � Cearense\n");
    } else if (strcmp(uf, "DF") == 0) {
        printf("Voc� � Brasiliense\n");
    } else if (strcmp(uf, "ES") == 0) {
        printf("Voc� � Capixaba\n");
    } else if (strcmp(uf, "GO") == 0) {
        printf("Voc� � Goiano\n");
    } else if (strcmp(uf, "MA") == 0) {
        printf("Voc� � Maranhense\n");
    } else if (strcmp(uf, "MT") == 0) {
        printf("Voc� � Mato-grossense\n");
    } else if (strcmp(uf, "MS") == 0) {
        printf("Voc� � Sul-mato-grossense\n");
    } else if (strcmp(uf, "MG") == 0) {
        printf("Voc� � Mineiro\n");
    } else if (strcmp(uf, "PA") == 0) {
        printf("Voc� � Paraense\n");
    } else if (strcmp(uf, "PB") == 0) {
        printf("Voc� � Paraibano\n");
    } else if (strcmp(uf, "PR") == 0) {
        printf("Voc� � Paranaense\n");
    } else if (strcmp(uf, "PE") == 0) {
        printf("Voc� � Pernambucano\n");
    } else if (strcmp(uf, "PI") == 0) {
        printf("Voc� � Piauiense\n");
    } else if (strcmp(uf, "RJ") == 0) {
        printf("Voc� � Fluminense\n");
    } else if (strcmp(uf, "RN") == 0) {
        printf("Voc� � Potiguar\n");
    } else if (strcmp(uf, "RS") == 0) {
        printf("Voc� � Ga�cho\n");
    } else if (strcmp(uf, "RO") == 0) {
        printf("Voc� � Rondoniense\n");
    } else if (strcmp(uf, "RR") == 0) {
        printf("Voc� � Roraimense\n");
    } else if (strcmp(uf, "SC") == 0) {
        printf("Voc� � Catarinense\n");
    } else if (strcmp(uf, "SP") == 0) {
        printf("Voc� � Paulista\n");
    } else if (strcmp(uf, "SE") == 0) {
        printf("Voc� � Sergipano\n");
    } else if (strcmp(uf, "TO") == 0) {
        printf("Voc� � Tocantinense\n");
    } else {
        printf("Estado n�o reconhecido\n");
    }
	system("pause");
    return 0;
}
