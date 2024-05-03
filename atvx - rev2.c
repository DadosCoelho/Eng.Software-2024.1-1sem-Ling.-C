#include <stdio.h>
#include <locale.h>

 /*Implemente um Algoritmo que Dado um número inteiro no formato CDU(Centena,
 Dezena e Unidade), exibir o número no formato UDC(Unidade, Dezena e Centena).
 Exemplo:123, será 321. O número deverá ser atribuído a uma variável antes de 
 ser exibido.*/
 
    int numero, unidade, dezena, centena, invertido;
    
int main() {
	setlocale(LC_ALL, "Portuguese");

    printf("Digite um número no formato CDU (Centena, Dezena e Unidade): ");
    scanf("%d", &numero);

    // Extrair a unidade, dezena e centena
    unidade = numero % 10;
    dezena = (numero / 10) % 10;
    centena = numero / 100;

    // Inverter o número para o formato UDC
    invertido = unidade * 100 + dezena * 10 + centena;

    printf("O número no formato UDC é: %d\n", invertido);
	system("pause");
    return 0;
}
