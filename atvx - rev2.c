#include <stdio.h>
#include <locale.h>

 /*Implemente um Algoritmo que Dado um n�mero inteiro no formato CDU(Centena,
 Dezena e Unidade), exibir o n�mero no formato UDC(Unidade, Dezena e Centena).
 Exemplo:123, ser� 321. O n�mero dever� ser atribu�do a uma vari�vel antes de 
 ser exibido.*/
 
    int numero, unidade, dezena, centena, invertido;
    
int main() {
	setlocale(LC_ALL, "Portuguese");

    printf("Digite um n�mero no formato CDU (Centena, Dezena e Unidade): ");
    scanf("%d", &numero);

    // Extrair a unidade, dezena e centena
    unidade = numero % 10;
    dezena = (numero / 10) % 10;
    centena = numero / 100;

    // Inverter o n�mero para o formato UDC
    invertido = unidade * 100 + dezena * 10 + centena;

    printf("O n�mero no formato UDC �: %d\n", invertido);
	system("pause");
    return 0;
}
