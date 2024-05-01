#include <stdio.h>
#include <string.h>
#include <locale.h>

/*Implemente um Algoritmo em C que receba via teclado a sigla dos estados(UF) do
Nordeste e seja impresso Ex. Se informado PE “Você é Pernambucano”Se PI “Você é
Piauiense” etc.*/

char uf[3];
int i;

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("Digite a sigla do seu estado (UF): ");
    scanf("%s", uf);

    //Convertendo para maiúsculas para evitar problemas de case
    for(i = 0; uf[i]; i++){
        uf[i] = toupper(uf[i]);
    }

    if (strcmp(uf, "AC") == 0) {
        printf("Você é Acreano\n");
    } else if (strcmp(uf, "AL") == 0) {
        printf("Você é Alagoano\n");
    } else if (strcmp(uf, "AP") == 0) {
        printf("Você é Amapaense\n");
    } else if (strcmp(uf, "AM") == 0) {
        printf("Você é Amazonense\n");
    } else if (strcmp(uf, "BA") == 0) {
        printf("Você é Baiano\n");
    } else if (strcmp(uf, "CE") == 0) {
        printf("Você é Cearense\n");
    } else if (strcmp(uf, "DF") == 0) {
        printf("Você é Brasiliense\n");
    } else if (strcmp(uf, "ES") == 0) {
        printf("Você é Capixaba\n");
    } else if (strcmp(uf, "GO") == 0) {
        printf("Você é Goiano\n");
    } else if (strcmp(uf, "MA") == 0) {
        printf("Você é Maranhense\n");
    } else if (strcmp(uf, "MT") == 0) {
        printf("Você é Mato-grossense\n");
    } else if (strcmp(uf, "MS") == 0) {
        printf("Você é Sul-mato-grossense\n");
    } else if (strcmp(uf, "MG") == 0) {
        printf("Você é Mineiro\n");
    } else if (strcmp(uf, "PA") == 0) {
        printf("Você é Paraense\n");
    } else if (strcmp(uf, "PB") == 0) {
        printf("Você é Paraibano\n");
    } else if (strcmp(uf, "PR") == 0) {
        printf("Você é Paranaense\n");
    } else if (strcmp(uf, "PE") == 0) {
        printf("Você é Pernambucano\n");
    } else if (strcmp(uf, "PI") == 0) {
        printf("Você é Piauiense\n");
    } else if (strcmp(uf, "RJ") == 0) {
        printf("Você é Fluminense\n");
    } else if (strcmp(uf, "RN") == 0) {
        printf("Você é Potiguar\n");
    } else if (strcmp(uf, "RS") == 0) {
        printf("Você é Gaúcho\n");
    } else if (strcmp(uf, "RO") == 0) {
        printf("Você é Rondoniense\n");
    } else if (strcmp(uf, "RR") == 0) {
        printf("Você é Roraimense\n");
    } else if (strcmp(uf, "SC") == 0) {
        printf("Você é Catarinense\n");
    } else if (strcmp(uf, "SP") == 0) {
        printf("Você é Paulista\n");
    } else if (strcmp(uf, "SE") == 0) {
        printf("Você é Sergipano\n");
    } else if (strcmp(uf, "TO") == 0) {
        printf("Você é Tocantinense\n");
    } else {
        printf("Estado não reconhecido\n");
    }
	system("pause");
    return 0;
}
