#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Biblioteca para usar caracteres especiai
#include <math.h>

int DL, DC, i, j, i, j;


int main()
{
	setlocale(LC_ALL, "Portuguese");
	printf("\nInforme a dimensão da Linha das matrizes  : ");
	scanf("%d", &DL);
	printf("\nInforme a dimensão da Coluna das matrizes : ");
	scanf("%d", &DC);

	int matrizP [DL] [DC];
	printf("\nInforme os valores da primeira matriz %dx%d:\n", DL, DC);
	for (i = 0; i < DL; i++)
	{
		for (j = 0; j < DC; j++)
		{
			scanf("%d", &matrizP[i][j]);
		}
	}
	printf("\nPrimeira matriz:\n");
	for (i = 0;	i < DL; i++)
	{
		for (j = 0; j < DC; j++)

			printf("|%4d", matrizP[i][j]);
		printf("|\n");

	}

	int matrizS [DL] [DC];
	printf("\nInforme os valores da segunda matriz %dx%d:\n", DL, DC);
	for (i = 0; i < DL; i++)
	{
		for (j = 0; j < DC; j++)
		{
			scanf("%d", &matrizS[i][j]);
		}
	}
	printf("\nSegunda matriz:\n");
	for (i = 0;	i < DL; i++)
	{
		for (j = 0; j < DC; j++)

			printf("|%4d", matrizS[i][j]);
		printf("|\n");

	}

	printf("\nPrimeira matriz vezes 2:\n");
	
	
	for (i = 0; i < DL; i++)
	{
		for (j = 0; j < DC; j++)
			printf("|%4d", matrizP[i][j]*2);
		printf("|\n");
	}
	
	printf("\nSegunda matriz vezes 3:\n");
	
	
	for (i = 0; i < DL; i++)
	{
		for (j = 0; j < DC; j++)
			printf("|%4d", matrizS[i][j]*3);
		printf("|\n");
	}





	return 0;
}
