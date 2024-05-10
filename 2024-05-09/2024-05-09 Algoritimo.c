#include<stdio.h>
#include<stdlib.h>
	FILE *arquivo; //vai ser associada ao arquivo
char nome [40], DataNasc[10], str[120], NomeArquivo[50];
int main () {
	printf ("Informe o nome do arquivo: Ex. Aluno.txt \n");
	scanf("%s", NomeArquivo);
	sprintf(str, "C:/Users/daldo/OneDrive/Área de Trabalho/Eng.Software 2024.1 1sem Ling. C/2024-05-09//%s", NomeArquivo);
	
	
	
	arquivo = fopen(str ,"w+");
	if (arquivo == 0)
		printf ("Erro na leitura do arquivo\n") ;
	else
		printf ("Arquivo criado com sucesso\n");
		printf("Informe seu nome: \n");
		scanf("%s", nome) ;
		printf ("Informe sua data de nascimento Ex.16/06/2000: \n");
		scanf ("%s", DataNasc) ;
		fprintf(arquivo, "+====================================+\n");
		fprintf (arquivo, "Nome: %s\n", nome); //gravando no arquivo
		fprintf (arquivo, "Data de Nascimento: %s\n", DataNasc) ;
		fprintf(arquivo, "+====================================+\n");
		fclose (arquivo); //fecha arquivo
		
		system ("pause") ;
		
		
		return 0;
}