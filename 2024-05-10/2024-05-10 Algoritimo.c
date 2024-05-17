#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
FILE *arquivo; // vai ser associado ao arquivo
char nome[40], DataNasc[10], str[80], nomearquivo[50], linha[250];

void LerArquivo()
{
	sprintf(str, "C:/Users/reinaldo.coelho/OneDrive/Área de Trabalho/Eng.Software 2024.1 1sem Ling. C/2024-05-10//%s", nomearquivo);
	arquivo = fopen (str, "r");
	while (fgets(linha, sizeof(linha), arquivo) != NULL)
	{
		printf( "%s", linha);
	}
	// fecha o arquivo
	fclose(arquivo);
}


int main()
{
	setlocale(LC_ALL, "");
	printf("informe o nome do arquivo: Ex. Aluno.txt \n");
	scanf("%s", nomearquivo);
	sprintf(str, "C:/Users/reinaldo.coelho/OneDrive/Área de Trabalho/Eng.Software 2024.1 1sem Ling. C/2024-05-10//%s", nomearquivo);
	arquivo = fopen(str, "w+");
	if(arquivo == 0)
		printf ("Erro na leitura do arquivo \n");
	else
		printf("Arquivo criado com sucesso\n");

	int i;
	for(i = 1; i <= 5; i++)
	{
		printf("Infome seu nome\n");
		scanf("%s", nome);
		printf("Informe sua data de nascimento Ex.16/06/2000\n");
		scanf("%s", DataNasc);
		printf("Aluno N :%d\n", i);
		fprintf(arquivo, "+=======================================+\n"); //gravando no arquivo
		fprintf(arquivo, "| RELAÇÃO DE ALUNO POR DATA DE NASC     |\n");
		fprintf(arquivo, "+=======================================+\n"); //gravando no arquivo
		fprintf(arquivo, "Matricula:%d\n", i);
		fprintf(arquivo, "|Nome     :%s\n", nome); //gravando no arquivo
		fprintf(arquivo, "|Data Nasc:%s\n", DataNasc);
		fprintf(arquivo, "+========================================+\n");
	}
	fclose(arquivo); //fecha arquivo
	LerArquivo ();
	system ("pause");
	return 0;
}
