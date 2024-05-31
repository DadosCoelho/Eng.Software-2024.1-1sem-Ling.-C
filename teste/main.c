#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <locale.h> // Biblioteca para usar caracteres especiais
#include <windows.h> // Para a função Sleep
#include <conio.h> // Para a função Getch
#include "login.h"

int TempMostrarTodos; // Variavel global



// 01.01 - Estrutura para representar um Afiliado
int QtdCamposAfiliado = 2;
typedef struct
{
	int IdAfiliado;
	char NomeAfiliado[50];
} Afiliado;

// 01.01 - Função para criar um Afiliado
Afiliado CriarAfiliado(int IdAfiliado, char* NomeAfiliado)
{
	Afiliado VarAfiliado;
	VarAfiliado.IdAfiliado = IdAfiliado;
	strcpy(VarAfiliado.NomeAfiliado, NomeAfiliado);
	return VarAfiliado;
}

// 01.01 - Função para imprimir um Afiliado
void ImprimirAfiliado(Afiliado VarAfiliado)
{
	printf("|  %04d  |  %-50s  |\n", VarAfiliado.IdAfiliado, VarAfiliado.NomeAfiliado);
	printf("+--------+------------------------------------------------------+\n");
}

// 01.01 - Função para escrever um Afiliado em um arquivo de base de dados
void EscreverAfiliado(FILE* fp, Afiliado VarAfiliado)
{
	fprintf(fp, "%d;%s\n", VarAfiliado.IdAfiliado, VarAfiliado.NomeAfiliado);
}

// 01.01 - Função para escrever um Afiliado em um arquivo temporário
void EscreverTempAfiliado(FILE* fp, Afiliado VarAfiliado)
{
	fprintf(fp, "|  %04d  |  %-50s  |\n+--------+------------------------------------------------------+\n", VarAfiliado.IdAfiliado, VarAfiliado.NomeAfiliado);
}

// 01.01 - Função para ler um Afiliado de um arquivo de base de dados
int LerAfiliado(FILE* fp, Afiliado* VarAfiliado)
{
	return fscanf(fp, "%d;%49[^\n]\n", &VarAfiliado->IdAfiliado, VarAfiliado->NomeAfiliado);
}

// 01.01 - Função para obter o maior ID de Afiliado
int ObterMaiorIdAfiliado()
{
	FILE *fp = fopen("DadosAfiliados.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}

	int MaiorIdAfiliado = 0;
	Afiliado VarAfiliado;
	while (LerAfiliado(fp, &VarAfiliado) == QtdCamposAfiliado)
	{
		if (VarAfiliado.IdAfiliado > MaiorIdAfiliado)
		{
			MaiorIdAfiliado = VarAfiliado.IdAfiliado;
		}
	}

	fclose(fp);

	return MaiorIdAfiliado;
}


// 01.01.01 - Cadastrar novo Afiliado
void CadastrarNovoAfiliado()
{
	char NomeAfiliadoCadastrar[50];
	printf("Digite o nome do Afiliado: ");
	fgets(NomeAfiliadoCadastrar, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
	NomeAfiliadoCadastrar[strcspn(NomeAfiliadoCadastrar, "\n")] = 0; // Remove a nova linha do final

	int IdAfiliadoCadastrar = ObterMaiorIdAfiliado() + 1;

	Afiliado VarAfiliado = CriarAfiliado(IdAfiliadoCadastrar, NomeAfiliadoCadastrar);

	FILE *fp = fopen("DadosAfiliados.txt", "a");
	EscreverAfiliado(fp, VarAfiliado);
	fclose(fp);

	printf("Afiliado cadastrado com sucesso!\n");
}

// 01.01.02 - Mostrar todos os Afiliados
void MostrarTodosAfiliados()
{
	FILE *fp = fopen("DadosAfiliados.txt", "r");
	if (fp == NULL)
	{
		system("cls");
		printf("Afiliados ainda n%co cadastrados!\n", 198);
		TempMostrarTodos = 1;
		Sleep(2500);
		system("cls");
	}
	else
	{
		system("cls");
		printf("+--------+------------------------------------------------------+\n");
		printf("|   ID   |                  NOME DO AFILIADO                    |\n");
		printf("+--------+------------------------------------------------------+\n");
		Afiliado VarAfiliado;
		while (LerAfiliado(fp, &VarAfiliado) == QtdCamposAfiliado)
		{
			ImprimirAfiliado(VarAfiliado);
		}
	}
	fclose(fp);
}

// 01.01.02.01 - Imprimir todos os cadastros de Afiliados em um arquivo temporário
void ImprimirTempAfiliado()
{
	char NomeArquivoTempAfiliado0[80], NomeArquivoTempAfiliado[80];
	printf("Informe o nome do arquivo: \n");
	scanf("%s", NomeArquivoTempAfiliado0);
	sprintf(NomeArquivoTempAfiliado, "%s.txt", NomeArquivoTempAfiliado0);

	FILE *fpOld = fopen("DadosAfiliados.txt", "r");
	FILE *fpNew = fopen(NomeArquivoTempAfiliado, "w");

	Afiliado VarAfiliado;
	fprintf(fpNew, "+--------+------------------------------------------------------+\n");
	fprintf(fpNew, "|   ID   |                  NOME DO AFILIADO                    |\n");
	fprintf(fpNew, "+--------+------------------------------------------------------+\n");

	while (LerAfiliado(fpOld, &VarAfiliado) == QtdCamposAfiliado)
	{
		EscreverTempAfiliado(fpNew, VarAfiliado);
	}

	fclose(fpOld);
	fclose(fpNew);

	printf("Arquivo impresso com sucesso!\n");
}

// 01.01.03 - Editar um cadastro de Afiliado
void EditarCadastroAfiliado()
{
	int IdAfiliadoEditar;
	printf("Digite o ID do Afiliado a ser editado: ");
	scanf("%d", &IdAfiliadoEditar);
	getchar(); // Consume o caractere de nova linha

	FILE *fpOld = fopen("DadosAfiliados.txt", "r");
	FILE *fpNew = fopen("DadosAfiliados_tmp.txt", "w");

	Afiliado VarAfiliado;
	while (LerAfiliado(fpOld, &VarAfiliado) == QtdCamposAfiliado)
	{
		if (VarAfiliado.IdAfiliado == IdAfiliadoEditar)
		{
			printf("Digite o novo nome do Afiliado: ");
			fgets(VarAfiliado.NomeAfiliado, 50, stdin);
			VarAfiliado.NomeAfiliado[strcspn(VarAfiliado.NomeAfiliado, "\n")] = 0;
		}
		EscreverAfiliado(fpNew, VarAfiliado);
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosAfiliados.txt");
	rename("DadosAfiliados_tmp.txt", "DadosAfiliados.txt");

	printf("Cadastro editado com sucesso!\n");
}

// 01.01.04 - Excluir um cadastro de Afiliado
void ExcluirCadastroAfiliado()
{
	int IdAfiliadoExcluir;
	printf("Digite o ID do Afiliado a ser exclu%cdo: ", 161);
	scanf("%d", &IdAfiliadoExcluir);
	getchar();

	FILE *fpOld = fopen("DadosAfiliados.txt", "r");
	FILE *fpNew = fopen("DadosAfiliados_tmp.txt", "w");

	Afiliado VarAfiliado;
	while (LerAfiliado(fpOld, &VarAfiliado) == QtdCamposAfiliado)
	{
		if (VarAfiliado.IdAfiliado != IdAfiliadoExcluir)
		{
			EscreverAfiliado(fpNew, VarAfiliado);
		}
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosAfiliados.txt");
	rename("DadosAfiliados_tmp.txt", "DadosAfiliados.txt");

	printf("Cadastro exclu%cdo com sucesso!\n", 161);
}


// 01.01 - Função para chamar Menu Cadastro Afiliado
void MenuCadastroAfiliado()
{
	int OpMenuCadastroAfiliado;
	do
	{
		system("cls");
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                  MENU DE CADASTRO DO AFILIADO                 \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-CADASTRAR NOVO AFILIADO     \xBA 2-MOSTRAR TODOS OS AFILIADOS  \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-EDITAR UM AFILIADO          \xBA 4-EXCLUIR UM AFILIADO         \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                0-VOLTAR PARA MENU DE CADASTRO                 \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenuCadastroAfiliado);
		getchar();

		switch (OpMenuCadastroAfiliado)
		{
		case 1:
		{
			system("cls");
			CadastrarNovoAfiliado();
			Sleep(2500);
			system("cls");
			break;
		}
		case 2:
		{
			MostrarTodosAfiliados();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				system("pause");
				system("cls");
				printf("Gostaria de imprimir esse arquivo? '1' para SIM ou '2' para N%cO : ", 199);
				int temp;
				scanf("%d", &temp);
				if(temp == 1)
				{
					system("cls");
					ImprimirTempAfiliado();
					Sleep(2500);
					system("cls");
				}
				else
					system("cls");
			}
			break;
		}
		case 3:
		{
			MostrarTodosAfiliados();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				EditarCadastroAfiliado();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 4:
		{
			MostrarTodosAfiliados();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ExcluirCadastroAfiliado();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 0:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenuCadastroAfiliado != 0);
}





// 01.02 - Estrutura para representar um Livro
typedef struct
{
	int IdLivro;
	char NomeLivro[50];
} Livro;

// 01.02 - Função para criar um Livro
Livro CriarLivro(int IdLivro, char* NomeLivro)
{
	Livro VarLivro;
	VarLivro.IdLivro = IdLivro;
	strcpy(VarLivro.NomeLivro, NomeLivro);
	return VarLivro;
}

// 01.02 - Função para imprimir um Livro
void ImprimirLivro(Livro VarLivro)
{
	printf("|  %04d  |  %-50s  |\n", VarLivro.IdLivro, VarLivro.NomeLivro);
	printf("+--------+------------------------------------------------------+\n");
}

// 01.02 - Função para escrever um Livro em um arquivo de base de dados
void EscreverLivro(FILE* fp, Livro VarLivro)
{
	fprintf(fp, "%d;%s\n", VarLivro.IdLivro, VarLivro.NomeLivro);
}

// 01.01 - Função para escrever um Livro em um arquivo temporário
void EscreverTempLivro(FILE* fp, Livro VarLivro)
{
	fprintf(fp, "|  %04d  |  %-50s  |\n+--------+------------------------------------------------------+\n", VarLivro.IdLivro, VarLivro.NomeLivro);
}

// 01.02 - Função para ler um Livro de um arquivo de base de dados
int LerLivro(FILE* fp, Livro* VarLivro)
{
	return fscanf(fp, "%d;%49[^\n]\n", &VarLivro->IdLivro, VarLivro->NomeLivro);
}

// 01.02 - Função para obter o maior ID de Livro
int ObterMaiorIdLivro()
{
	FILE *fp = fopen("DadosLivros.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}

	int MaiorIdLivro = 0;
	Livro VarLivro;
	while (LerLivro(fp, &VarLivro) == 2)
	{
		if (VarLivro.IdLivro > MaiorIdLivro)
		{
			MaiorIdLivro = VarLivro.IdLivro;
		}
	}

	fclose(fp);

	return MaiorIdLivro;
}


// 01.02.01 - Cadastrar novo Livro
void CadastrarNovoLivro()
{
	char NomeLivroCadastrar[50];
	printf("Digite o nome do Livro: ");
	fgets(NomeLivroCadastrar, 50, stdin);
	NomeLivroCadastrar[strcspn(NomeLivroCadastrar, "\n")] = 0;

	int IdLivroCadastrar = ObterMaiorIdLivro() + 1;

	Livro VarLivro = CriarLivro(IdLivroCadastrar, NomeLivroCadastrar);

	FILE *fp = fopen("DadosLivros.txt", "a");
	EscreverLivro(fp, VarLivro);
	fclose(fp);

	printf("Livro cadastrado com sucesso!\n");
}

// 01.02.02 - Mostrar todos os Livros
void MostrarTodosLivros()
{
	FILE *fp = fopen("DadosLivros.txt", "r");
	if (fp == NULL)
	{
		system("cls");
		printf("Livros ainda n%co cadastrados!\n", 198);
		TempMostrarTodos = 1;
		Sleep(2500);
		system("cls");
	}
	else
	{
		system("cls");
		printf("+--------+------------------------------------------------------+\n");
		printf("|   ID   |                   NOME DO LIVRO                      |\n");
		printf("+--------+------------------------------------------------------+\n");
		Livro VarLivro;
		while (LerLivro(fp, &VarLivro) == 2)
		{
			ImprimirLivro(VarLivro);
		}
	}
	fclose(fp);
}

// 01.02.02.01 - Imprimir todos os cadastros de Livros em um arquivo temporário
void ImprimirTempLivro()
{
	char NomeArquivoTempLivro0[80], NomeArquivoTempLivro[80];
	printf("informe o nome do arquivo: \n");
	scanf("%s", NomeArquivoTempLivro0);
	sprintf(NomeArquivoTempLivro, "%s.txt", NomeArquivoTempLivro0);

	FILE *fpOld = fopen("DadosLivros.txt", "r");
	FILE *fpNew = fopen(NomeArquivoTempLivro, "w");

	Livro VarLivro;
	fprintf(fpNew, "+--------+------------------------------------------------------+\n");
	fprintf(fpNew, "|   ID   |                   NOME DO LIVRO                      |\n");
	fprintf(fpNew, "+--------+------------------------------------------------------+\n");

	while (LerLivro(fpOld, &VarLivro) == 2)
	{
		EscreverTempLivro(fpNew, VarLivro);
	}

	fclose(fpOld);
	fclose(fpNew);

	printf("Arquivo impresso com sucesso!\n");
}

// 01.02.03 - Editar um cadastro de Livro
void EditarCadastroLivro()
{
	int IdLivroEditar;
	printf("Digite o ID do Livro a ser editado: ");
	scanf("%d", &IdLivroEditar);
	getchar();

	FILE *fpOld = fopen("DadosLivros.txt", "r");
	FILE *fpNew = fopen("DadosLivros_tmp.txt", "w");

	Livro VarLivro;
	while (LerLivro(fpOld, &VarLivro) == 2)
	{
		if (VarLivro.IdLivro == IdLivroEditar)
		{
			printf("Digite o novo nome do Livro: ");
			fgets(VarLivro.NomeLivro, 50, stdin);
			VarLivro.NomeLivro[strcspn(VarLivro.NomeLivro, "\n")] = 0;
		}
		EscreverLivro(fpNew, VarLivro);
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosLivros.txt");
	rename("DadosLivros_tmp.txt", "DadosLivros.txt");

	printf("Cadastro editado com sucesso!\n");
}

// 01.02.04 - Excluir um cadastro de Livro
void ExcluirCadastroLivro()
{
	int IdLivroExcluir;
	printf("Digite o ID do Livro a ser exclu%cdo: ", 161);
	scanf("%d", &IdLivroExcluir);
	getchar();

	FILE *fpOld = fopen("DadosLivros.txt", "r");
	FILE *fpNew = fopen("DadosLivros_tmp.txt", "w");

	Livro VarLivro;
	while (LerLivro(fpOld, &VarLivro) == 2)
	{
		if (VarLivro.IdLivro != IdLivroExcluir)
		{
			EscreverLivro(fpNew, VarLivro);
		}
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosLivros.txt");
	rename("DadosLivros_tmp.txt", "DadosLivros.txt");

	printf("Cadastro exclu%cdo com sucesso!\n", 161);
}

// 01.02 - Função para chamar Menu Cadastro Livro
void MenuCadastroLivro()
{
	int OpMenuCadastroLivro;
	do
	{
		system("cls");
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                  MENU DE CADASTRO DO LIVRO                    \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-CADASTRAR NOVO LIVRO        \xBA 2-MOSTRAR TODOS OS LIVROS     \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-EDITAR UM LIVRO             \xBA 4-EXCLUIR UM LIVRO            \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                0-VOLTAR PARA MENU DE CADASTRO                 \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenuCadastroLivro);
		getchar();

		switch (OpMenuCadastroLivro)
		{
		case 1:
		{
			system("cls");
			CadastrarNovoLivro();
			Sleep(2500);
			system("cls");
			break;
		}
		case 2:
		{
			MostrarTodosLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				system("pause");
				system("cls");
				printf("Gostaria de imprimir esse arquivo? '1' para SIM ou '2' para N%cO : ", 199);
				int temp;
				scanf("%d", &temp);
				if(temp == 1)
				{
					system("cls");
					ImprimirTempLivro();
					Sleep(2500);
					system("cls");
				}
				else
					system("cls");
			}
			break;
		}
		case 3:
		{
			MostrarTodosLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				EditarCadastroLivro();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 4:
		{
			MostrarTodosLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ExcluirCadastroLivro();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 0:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenuCadastroLivro != 0);
}





// 01.03 - Estrutura para representar um StatusLivro
typedef struct
{
	int IdStatusLivro;
	char NomeStatusLivro[50];
} StatusLivro;

// 01.03 - Função para criar um StatusLivro
StatusLivro CriarStatusLivro(int IdStatusLivro, char* NomeStatusLivro)
{
	StatusLivro VarStatusLivro;
	VarStatusLivro.IdStatusLivro = IdStatusLivro;
	strcpy(VarStatusLivro.NomeStatusLivro, NomeStatusLivro);
	return VarStatusLivro;
}

// 01.03 - Função para imprimir um StatusLivro
void ImprimirStatusLivro(StatusLivro VarStatusLivro)
{
	printf("|  %04d  |  %-50s  |\n", VarStatusLivro.IdStatusLivro, VarStatusLivro.NomeStatusLivro);
	printf("+--------+------------------------------------------------------+\n");
}

// 01.03 - Função para escrever um StatusLivro em um arquivo de base de dados
void EscreverStatusLivro(FILE* fp, StatusLivro VarStatusLivro)
{
	fprintf(fp, "%d;%s\n", VarStatusLivro.IdStatusLivro, VarStatusLivro.NomeStatusLivro);
}

// 01.01 - Função para escrever um StatusLivro em um arquivo temporário
void EscreverTempStatusLivro(FILE* fp, StatusLivro VarStatusLivro)
{
	fprintf(fp, "|  %04d  |  %-50s  |\n+--------+------------------------------------------------------+\n", VarStatusLivro.IdStatusLivro, VarStatusLivro.NomeStatusLivro);
}

// 01.03 - Função para ler um StatusLivro de um arquivo de base de dados
int LerStatusLivro(FILE* fp, StatusLivro* VarStatusLivro)
{
	return fscanf(fp, "%d;%49[^\n]\n", &VarStatusLivro->IdStatusLivro, VarStatusLivro->NomeStatusLivro);
}

// 01.03 - Função para obter o maior ID de StatusLivro
int ObterMaiorIdStatusLivro()
{
	FILE *fp = fopen("DadosStatusLivros.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}

	int MaiorIdStatusLivro = 0;
	StatusLivro VarStatusLivro;
	while (LerStatusLivro(fp, &VarStatusLivro) == 2)
	{
		if (VarStatusLivro.IdStatusLivro > MaiorIdStatusLivro)
		{
			MaiorIdStatusLivro = VarStatusLivro.IdStatusLivro;
		}
	}

	fclose(fp);

	return MaiorIdStatusLivro;
}


// 01.03.01 - Cadastrar novo StatusLivro
void CadastrarNovoStatusLivro()
{
	char NomeStatusLivroCadastrar[50];
	printf("Digite o nome do Status do Livro: ");
	fgets(NomeStatusLivroCadastrar, 50, stdin);
	NomeStatusLivroCadastrar[strcspn(NomeStatusLivroCadastrar, "\n")] = 0;

	int IdStatusLivroCadastrar = ObterMaiorIdStatusLivro() + 1;

	StatusLivro VarStatusLivro = CriarStatusLivro(IdStatusLivroCadastrar, NomeStatusLivroCadastrar);

	FILE *fp = fopen("DadosStatusLivros.txt", "a");
	EscreverStatusLivro(fp, VarStatusLivro);
	fclose(fp);

	printf("Status do Livro cadastrado com sucesso!\n");
}

// 01.03.02 - Mostrar todos os StatusLivros
void MostrarTodosStatusLivros()
{
	FILE *fp = fopen("DadosStatusLivros.txt", "r");
	if (fp == NULL)
	{
		system("cls");
		printf("Status dos Livros ainda n%co cadastrados!\n", 198);
		TempMostrarTodos = 1;
		Sleep(2500);
		system("cls");
	}
	else
	{
		system("cls");
		printf("+--------+------------------------------------------------------+\n");
		printf("|   ID   |              NOME DO STATUS DO LIVRO                 |\n");
		printf("+--------+------------------------------------------------------+\n");
		StatusLivro VarStatusLivro;
		while (LerStatusLivro(fp, &VarStatusLivro) == 2)
		{
			ImprimirStatusLivro(VarStatusLivro);
		}
	}
	fclose(fp);
}

// 01.03.02.01 - Imprimir todos os cadastros de StatusLivros em um arquivo temporário
void ImprimirTempStatusLivro()
{
	char NomeArquivoTempStatusLivro0[80], NomeArquivoTempStatusLivro[80];
	printf("informe o nome do arquivo: \n");
	scanf("%s", NomeArquivoTempStatusLivro0);
	sprintf(NomeArquivoTempStatusLivro, "%s.txt", NomeArquivoTempStatusLivro0);

	FILE *fpOld = fopen("DadosStatusLivros.txt", "r");
	FILE *fpNew = fopen(NomeArquivoTempStatusLivro, "w");

	StatusLivro VarStatusLivro;
	fprintf(fpNew, "+--------+------------------------------------------------------+\n");
	fprintf(fpNew, "|   ID   |               NOME DO STATUS DO LIVRO                |\n");
	fprintf(fpNew, "+--------+------------------------------------------------------+\n");

	while (LerStatusLivro(fpOld, &VarStatusLivro) == 2)
	{
		EscreverTempStatusLivro(fpNew, VarStatusLivro);
	}

	fclose(fpOld);
	fclose(fpNew);

	printf("Arquivo impresso com sucesso!\n");
}

// 01.03.03 - Editar um cadastro de StatusLivro
void EditarCadastroStatusLivro()
{
	int IdStatusLivroEditar;
	printf("Digite o ID do StatusLivro a ser editado: ");
	scanf("%d", &IdStatusLivroEditar);
	getchar();

	FILE *fpOld = fopen("DadosStatusLivros.txt", "r");
	FILE *fpNew = fopen("DadosStatusLivros_tmp.txt", "w");

	StatusLivro VarStatusLivro;
	while (LerStatusLivro(fpOld, &VarStatusLivro) == 2)
	{
		if (VarStatusLivro.IdStatusLivro == IdStatusLivroEditar)
		{
			printf("Digite o novo nome do Status do Livro: ");
			fgets(VarStatusLivro.NomeStatusLivro, 50, stdin);
			VarStatusLivro.NomeStatusLivro[strcspn(VarStatusLivro.NomeStatusLivro, "\n")] = 0;
		}
		EscreverStatusLivro(fpNew, VarStatusLivro);
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosStatusLivros.txt");
	rename("DadosStatusLivros_tmp.txt", "DadosStatusLivros.txt");

	printf("Cadastro editado com sucesso!\n");
}

// 01.03.04 - Excluir um cadastro de StatusLivro
void ExcluirCadastroStatusLivro()
{
	int IdStatusLivroExcluir;
	printf("Digite o ID do Status do Livro a ser exclu%cdo: ", 161);
	scanf("%d", &IdStatusLivroExcluir);
	getchar();

	FILE *fpOld = fopen("DadosStatusLivros.txt", "r");
	FILE *fpNew = fopen("DadosStatusLivros_tmp.txt", "w");

	StatusLivro VarStatusLivro;
	while (LerStatusLivro(fpOld, &VarStatusLivro) == 2)
	{
		if (VarStatusLivro.IdStatusLivro != IdStatusLivroExcluir)
		{
			EscreverStatusLivro(fpNew, VarStatusLivro);
		}
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosStatusLivros.txt");
	rename("DadosStatusLivros_tmp.txt", "DadosStatusLivros.txt");

	printf("Cadastro exclu%cdo com sucesso!\n", 161);
}

// 01.03 - Função para chamar Menu Cadastro StatusLivro
void MenuCadastroStatusLivro()
{
	system("cls");
	int OpMenuCadastroStatusLivro;
	do
	{
		system("cls");
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                MENU DE CADASTRO DO STATUS DO LIVRO            \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-CADASTRAR NOVO STATUS       \xBA 2-MOSTRAR TODOS OS STATUS     \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-EDITAR UM STATUS            \xBA 4-EXCLUIR UM STATUS           \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                0-VOLTAR PARA MENU DE CADASTRO                 \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenuCadastroStatusLivro);
		getchar();

		switch (OpMenuCadastroStatusLivro)
		{
		case 1:
		{
			system("cls");
			CadastrarNovoStatusLivro();
			Sleep(2500);
			system("cls");
			break;
		}
		case 2:
		{
			MostrarTodosStatusLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				system("pause");
				system("cls");
				printf("Gostaria de imprimir esse arquivo? '1' para SIM ou '2' para N%cO : ", 199);
				int temp;
				scanf("%d", &temp);
				if(temp == 1)
				{
					system("cls");
					ImprimirTempStatusLivro();
					Sleep(2500);
					system("cls");
				}
				else
					system("cls");
			}
			break;
		}
		case 3:
		{
			MostrarTodosStatusLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				EditarCadastroStatusLivro();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 4:
		{
			MostrarTodosStatusLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ExcluirCadastroStatusLivro();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 0:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenuCadastroStatusLivro != 0);
}







// 01.04 - Estrutura para representar um CategoriaLivro
typedef struct
{
	int IdCategoriaLivro;
	char NomeCategoriaLivro[50];
} CategoriaLivro;

// 01.04 - Função para criar um CategoriaLivro
CategoriaLivro CriarCategoriaLivro(int IdCategoriaLivro, char* NomeCategoriaLivro)
{
	CategoriaLivro VarCategoriaLivro;
	VarCategoriaLivro.IdCategoriaLivro = IdCategoriaLivro;
	strcpy(VarCategoriaLivro.NomeCategoriaLivro, NomeCategoriaLivro);
	return VarCategoriaLivro;
}

// 01.04 - Função para imprimir um CategoriaLivro
void ImprimirCategoriaLivro(CategoriaLivro VarCategoriaLivro)
{
	printf("|  %04d  |  %-50s  |\n", VarCategoriaLivro.IdCategoriaLivro, VarCategoriaLivro.NomeCategoriaLivro);
	printf("+--------+------------------------------------------------------+\n");
}

// 01.04 - Função para escrever um CategoriaLivro em um arquivo de base de dados
void EscreverCategoriaLivro(FILE* fp, CategoriaLivro VarCategoriaLivro)
{
	fprintf(fp, "%d;%s\n", VarCategoriaLivro.IdCategoriaLivro, VarCategoriaLivro.NomeCategoriaLivro);
}

// 01.01 - Função para escrever um CategoriaLivro em um arquivo temporário
void EscreverTempCategoriaLivro(FILE* fp, CategoriaLivro VarCategoriaLivro)
{
	fprintf(fp, "|  %04d  |  %-50s  |\n+--------+------------------------------------------------------+\n", VarCategoriaLivro.IdCategoriaLivro, VarCategoriaLivro.NomeCategoriaLivro);
}

// 01.04 - Função para ler um CategoriaLivro de um arquivo de base de dados
int LerCategoriaLivro(FILE* fp, CategoriaLivro* VarCategoriaLivro)
{
	return fscanf(fp, "%d;%49[^\n]\n", &VarCategoriaLivro->IdCategoriaLivro, VarCategoriaLivro->NomeCategoriaLivro);
}

// 01.04 - Função para obter o maior ID de CategoriaLivro
int ObterMaiorIdCategoriaLivro()
{
	FILE *fp = fopen("DadosCategoriaLivros.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}

	int MaiorIdCategoriaLivro = 0;
	CategoriaLivro VarCategoriaLivro;
	while (LerCategoriaLivro(fp, &VarCategoriaLivro) == 2)
	{
		if (VarCategoriaLivro.IdCategoriaLivro > MaiorIdCategoriaLivro)
		{
			MaiorIdCategoriaLivro = VarCategoriaLivro.IdCategoriaLivro;
		}
	}

	fclose(fp);

	return MaiorIdCategoriaLivro;
}


// 01.04.01 - Cadastrar novo CategoriaLivro
void CadastrarNovoCategoriaLivro()
{
	char NomeCategoriaLivroCadastrar[50];
	printf("Digite o nome do Categoria do Livro: ");
	fgets(NomeCategoriaLivroCadastrar, 50, stdin);
	NomeCategoriaLivroCadastrar[strcspn(NomeCategoriaLivroCadastrar, "\n")] = 0;

	int IdCategoriaLivroCadastrar = ObterMaiorIdCategoriaLivro() + 1;

	CategoriaLivro VarCategoriaLivro = CriarCategoriaLivro(IdCategoriaLivroCadastrar, NomeCategoriaLivroCadastrar);

	FILE *fp = fopen("DadosCategoriaLivros.txt", "a");
	EscreverCategoriaLivro(fp, VarCategoriaLivro);
	fclose(fp);

	printf("Categoria do Livro cadastrado com sucesso!\n");
}

// 01.04.02 - Mostrar todos os CategoriaLivros
void MostrarTodosCategoriaLivros()
{
	FILE *fp = fopen("DadosCategoriaLivros.txt", "r");
	if (fp == NULL)
	{
		system("cls");
		printf("Categorias dos Livros ainda n%co cadastrados!\n", 198);
		TempMostrarTodos = 1;
		Sleep(2500);
		system("cls");
	}
	else
	{
		system("cls");
		printf("+--------+------------------------------------------------------+\n");
		printf("|   ID   |             NOME DA CATEGORIA DO LIVRO               |\n");
		printf("+--------+------------------------------------------------------+\n");
		CategoriaLivro VarCategoriaLivro;
		while (LerCategoriaLivro(fp, &VarCategoriaLivro) == 2)
		{
			ImprimirCategoriaLivro(VarCategoriaLivro);
		}
	}
	fclose(fp);
}

// 01.04.02.01 - Imprimir todos os cadastros de CategoriaLivros em um arquivo temporário
void ImprimirTempCategoriaLivro()
{
	char NomeArquivoTempCategoriaLivro0[80], NomeArquivoTempCategoriaLivro[80];
	printf("informe o nome do arquivo: \n");
	scanf("%s", NomeArquivoTempCategoriaLivro0);
	sprintf(NomeArquivoTempCategoriaLivro, "%s.txt", NomeArquivoTempCategoriaLivro0);

	FILE *fpOld = fopen("DadosCategoriaLivros.txt", "r");
	FILE *fpNew = fopen(NomeArquivoTempCategoriaLivro, "w");

	CategoriaLivro VarCategoriaLivro;
	fprintf(fpNew, "+--------+------------------------------------------------------+\n");
	fprintf(fpNew, "|   ID   |             NOME DA CATEGORIA DO LIVRO               |\n");
	fprintf(fpNew, "+--------+------------------------------------------------------+\n");

	while (LerCategoriaLivro(fpOld, &VarCategoriaLivro) == 2)
	{
		EscreverTempCategoriaLivro(fpNew, VarCategoriaLivro);
	}

	fclose(fpOld);
	fclose(fpNew);

	printf("Arquivo impresso com sucesso!\n");
}

// 01.04.03 - Editar um cadastro de CategoriaLivro
void EditarCadastroCategoriaLivro()
{
	int IdCategoriaLivroEditar;
	printf("Digite o ID do Categoria do Livro a ser editado: ");
	scanf("%d", &IdCategoriaLivroEditar);
	getchar();

	FILE *fpOld = fopen("DadosCategoriaLivros.txt", "r");
	FILE *fpNew = fopen("DadosCategoriaLivros_tmp.txt", "w");

	CategoriaLivro VarCategoriaLivro;
	while (LerCategoriaLivro(fpOld, &VarCategoriaLivro) == 2)
	{
		if (VarCategoriaLivro.IdCategoriaLivro == IdCategoriaLivroEditar)
		{
			printf("Digite o novo nome do CategoriaLivro: ");
			fgets(VarCategoriaLivro.NomeCategoriaLivro, 50, stdin);
			VarCategoriaLivro.NomeCategoriaLivro[strcspn(VarCategoriaLivro.NomeCategoriaLivro, "\n")] = 0;
		}
		EscreverCategoriaLivro(fpNew, VarCategoriaLivro);
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosCategoriaLivros.txt");
	rename("DadosCategoriaLivros_tmp.txt", "DadosCategoriaLivros.txt");

	printf("Cadastro editado com sucesso!\n");
}

// 01.04.04 - Excluir um cadastro de CategoriaLivro
void ExcluirCadastroCategoriaLivro()
{
	int IdCategoriaLivroExcluir;
	printf("Digite o ID do Categoria do Livro a ser exclu%cdo: ", 161);
	scanf("%d", &IdCategoriaLivroExcluir);
	getchar();

	FILE *fpOld = fopen("DadosCategoriaLivros.txt", "r");
	FILE *fpNew = fopen("DadosCategoriaLivros_tmp.txt", "w");

	CategoriaLivro VarCategoriaLivro;
	while (LerCategoriaLivro(fpOld, &VarCategoriaLivro) == 2)
	{
		if (VarCategoriaLivro.IdCategoriaLivro != IdCategoriaLivroExcluir)
		{
			EscreverCategoriaLivro(fpNew, VarCategoriaLivro);
		}
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosCategoriaLivros.txt");
	rename("DadosCategoriaLivros_tmp.txt", "DadosCategoriaLivros.txt");

	printf("Cadastro exclu%cdo com sucesso!\n", 161);
}

// 01.04 - Função para chamar Menu Cadastro CategoriaLivro
void MenuCadastroCategoriaLivro()
{
	int OpMenuCadastroCategoriaLivro;
	do
	{
		system("cls");
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA             MENU DE CADASTRO DA CATEGORIA DO LIVRO            \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-CADASTRAR NOVA CATEGORIA    \xBA 2-MOSTRAR TODAS AS CATEGORIAS \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-EDITAR UMA CATEGORIA        \xBA 4-EXCLUIR UMA CATEGORIA       \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                0-VOLTAR PARA MENU DE CADASTRO                 \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenuCadastroCategoriaLivro);
		getchar();

		switch (OpMenuCadastroCategoriaLivro)
		{
		case 1:
		{
			system("cls");
			CadastrarNovoCategoriaLivro();
			Sleep(2500);
			system("cls");
			break;
		}
		case 2:
		{
			MostrarTodosCategoriaLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				system("pause");
				system("cls");
				printf("Gostaria de imprimir esse arquivo? '1' para SIM ou '2' para N%cO : ", 199);
				int temp;
				scanf("%d", &temp);
				if(temp == 1)
				{
					system("cls");
					ImprimirTempCategoriaLivro();
					Sleep(2500);
					system("cls");
				}
				else
					system("cls");
			}
			break;
		}
		case 3:
		{
			MostrarTodosCategoriaLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				EditarCadastroCategoriaLivro();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 4:
		{
			MostrarTodosCategoriaLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ExcluirCadastroCategoriaLivro();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 0:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenuCadastroCategoriaLivro != 0);
}





// 02 - Estrutura para representar um Inventario
typedef struct
{
	int IdInventario;
	int IdInventarioLivro;
	char NomeLivroInventario[50];
	int IdInventarioCategoria;
	int IdInventarioStatus;

} Inventario;

// 02 - Função para criar um Inventario
Inventario CriarInventario(int IdInventario, int IdInventarioLivro, char * NomeLivroInventario, int IdInventarioCategoria, int IdInventarioStatus)
{
	Inventario VarInventario;
	VarInventario.IdInventario = IdInventario;
	VarInventario.IdInventarioLivro = IdInventarioLivro;
	strcpy(VarInventario.NomeLivroInventario, NomeLivroInventario);
	VarInventario.IdInventarioCategoria = IdInventarioCategoria;
	VarInventario.IdInventarioStatus = IdInventarioStatus;
	return VarInventario;
}

// 02 - Função para imprimir um Inventario
void ImprimirInventario(Inventario VarInventario)
{
	printf("|  %04d  |  %04d  |  %-50s  |  %04d  |  %04d  |\n", VarInventario.IdInventario, VarInventario.IdInventarioLivro, VarInventario.NomeLivroInventario, VarInventario.IdInventarioCategoria, VarInventario.IdInventarioStatus);
	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
}

// 02 - Função para escrever um Inventario em um arquivo de base de dados
void EscreverInventario(FILE * fp, Inventario VarInventario)
{
	fprintf(fp, "%d;%d;%s;%d;%d\n", VarInventario.IdInventario, VarInventario.IdInventarioLivro, VarInventario.NomeLivroInventario, VarInventario.IdInventarioCategoria, VarInventario.IdInventarioStatus);
}

// 02 - Função para escrever um Inventario em um arquivo temporário
void EscreverTempInventario(FILE * fp, Inventario VarInventario)
{
	fprintf(fp, "|  %04d  |  %04d  |  %-50s  |  %04d  |  %04d  |\n+--------+--------+------------------------------------------------------+--------+--------+\n", VarInventario.IdInventario, VarInventario.IdInventarioLivro, VarInventario.NomeLivroInventario, VarInventario.IdInventarioCategoria, VarInventario.IdInventarioStatus);
}

// 02 - Função para ler um Inventario de um arquivo de base de dados
int LerInventario(FILE * fp, Inventario * VarInventario)
{
	return fscanf(fp, "%d;%d;%49[^;];%d;%d\n", &VarInventario->IdInventario, &VarInventario->IdInventarioLivro, VarInventario->NomeLivroInventario, &VarInventario->IdInventarioCategoria, &VarInventario->IdInventarioStatus);
}

// 02 - Função para obter o maior ID de Inventario
int ObterMaiorIdInventario()
{
	FILE *fp = fopen("DadosInventarios.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}

	int MaiorIdInventario = 0;
	Inventario VarInventario;
	while (LerInventario(fp, &VarInventario) == 5)
	{
		if (VarInventario.IdInventario > MaiorIdInventario)
		{
			MaiorIdInventario = VarInventario.IdInventario;
		}
	}

	fclose(fp);

	return MaiorIdInventario;
}


// 02.01 - Cadastrar novo Inventario
void CadastrarNovoInventario()
{
	char NomeLivroInventarioCadastrar[50];
	int IdInventarioLivroCadastrar, IdInventarioCategoriaCadastrar, IdInventarioStatusCadastrar;

	int IdInventarioCadastrar = ObterMaiorIdInventario() + 1;


	printf("+--------+------------------------------------------------------+\n");
	printf("|   ID   |                   NOME DO LIVRO                      |\n");
	printf("+--------+------------------------------------------------------+\n");
	MostrarTodosLivros();
	printf("Digite o Id do Livro: ");
	scanf("%d", &IdInventarioLivroCadastrar);
	system("cls");

	FILE *fp = fopen("DadosLivros.txt", "r");
	Livro VarLivro;
	while (LerLivro(fp, &VarLivro) == 2)
	{
		if (VarLivro.IdLivro == IdInventarioLivroCadastrar)
		{
			strcpy(NomeLivroInventarioCadastrar, VarLivro.NomeLivro);
		}
	}
	fclose(fp);

	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
	printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
	printf("|  %04d  |  %04d  |  %-50s  |        |        |\n", IdInventarioCadastrar, IdInventarioLivroCadastrar, NomeLivroInventarioCadastrar);
	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
	printf("\n");

	printf("+--------+------------------------------------------------------+\n");
	printf("|   ID   |             NOME DA CATEGORIA DO LIVRO               |\n");
	printf("+--------+------------------------------------------------------+\n");
	MostrarTodosCategoriaLivros();
	printf("Digite o Id da categoria: ");
	scanf("%d", &IdInventarioCategoriaCadastrar);
	system("cls");
	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
	printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
	printf("|  %04d  |  %04d  |  %-50s  |  %04d  |        |\n", IdInventarioCadastrar, IdInventarioLivroCadastrar, NomeLivroInventarioCadastrar, IdInventarioCategoriaCadastrar);
	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
	printf("\n");

	printf("+--------+------------------------------------------------------+\n");
	printf("|   ID   |              NOME DO STATUS DO LIVRO                 |\n");
	printf("+--------+------------------------------------------------------+\n");
	MostrarTodosStatusLivros();
	printf("Digite o Id do Status: ");
	scanf("%d", &IdInventarioStatusCadastrar);
	system("cls");
	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
	printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
	printf("|  %04d  |  %04d  |  %-50s  |  %04d  |  %04d  |\n", IdInventarioCadastrar, IdInventarioLivroCadastrar, NomeLivroInventarioCadastrar, IdInventarioCategoriaCadastrar, IdInventarioStatusCadastrar);
	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
	printf("\n");


	Inventario VarInventario = CriarInventario(IdInventarioCadastrar, IdInventarioLivroCadastrar, NomeLivroInventarioCadastrar, IdInventarioCategoriaCadastrar, IdInventarioStatusCadastrar);

	FILE *fp2 = fopen("DadosInventarios.txt", "a");
	EscreverInventario(fp2, VarInventario);
	fclose(fp2);

	printf("Invent%crio cadastrado com sucesso!\n", 160);
}

// 02.02 - Mostrar todos os Inventarios
void MostrarTodosInventarios()
{
	FILE *fp = fopen("DadosInventarios.txt", "r");
	if (fp == NULL)
	{
		system("cls");
		printf("Invent%crio ainda n%co cadastrado!\n", 160, 198);
		TempMostrarTodos = 1;
		Sleep(2500);
		system("cls");
	}
	else
	{
		system("cls");
		printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
		printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
		printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
		Inventario VarInventario;
		while (LerInventario(fp, &VarInventario) == 5)
		{
			ImprimirInventario(VarInventario);
		}
	}
	fclose(fp);
}

// 02.02.01 - Imprimir todos os cadastros de Inventarios em um arquivo temporário
void ImprimirTempInventario()
{
	char NomeArquivoTempInventario0[80], NomeArquivoTempInventario[80];
	printf("informe o nome do arquivo: \n");
	scanf("%s", NomeArquivoTempInventario0);
	sprintf(NomeArquivoTempInventario, "%s.txt", NomeArquivoTempInventario0);

	FILE *fpOld = fopen("DadosInventarios.txt", "r");
	FILE *fpNew = fopen(NomeArquivoTempInventario, "w");

	Inventario VarInventario;
	fprintf(fpNew, "+--------+--------+------------------------------------------------------+--------+--------+\n");
	fprintf(fpNew, "|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
	fprintf(fpNew, "+--------+--------+------------------------------------------------------+--------+--------+\n");

	while (LerInventario(fpOld, &VarInventario) == 5)
	{
		EscreverTempInventario(fpNew, VarInventario);
	}

	fclose(fpOld);
	fclose(fpNew);

	printf("Arquivo impresso com sucesso!\n");
}

// 02.03 - Editar um cadastro de Inventario
void EditarCadastroInventario()
{
	int IdInventarioEditar;
	printf("Digite o ID do Invent%crio a ser editado: ", 160);
	scanf("%d", &IdInventarioEditar);
	getchar();
	system("cls");

	FILE *fpOld = fopen("DadosInventarios.txt", "r");
	FILE *fpNew = fopen("DadosInventarios_tmp.txt", "w");
	Inventario VarInventario;
	while (LerInventario(fpOld, &VarInventario) == 5)
	{
		if (VarInventario.IdInventario == IdInventarioEditar)
		{
			char NomeLivroInventarioEditar[50];
			int IdInventarioLivroEditar, IdInventarioCategoriaEditar, IdInventarioStatusEditar;

			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("|  %04d  |        |                                                      |        |        |\n", IdInventarioEditar);
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("\n");
			printf("+--------+------------------------------------------------------+\n");
			printf("|   ID   |                   NOME DO LIVRO                      |\n");
			printf("+--------+------------------------------------------------------+\n");
			MostrarTodosLivros();

			printf("Digite o Id do Livro: ");
			scanf("%d", &IdInventarioLivroEditar);
			system("cls");

			FILE *fp = fopen("DadosLivros.txt", "r");
			Livro VarLivro;
			while (LerLivro(fp, &VarLivro) == 2)
			{
				if (VarLivro.IdLivro == IdInventarioLivroEditar)
				{
					strcpy(NomeLivroInventarioEditar, VarLivro.NomeLivro);
				}
			}
			fclose(fp);

			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("|  %04d  |  %04d  |  %-50s  |        |        |\n", IdInventarioEditar, IdInventarioLivroEditar, NomeLivroInventarioEditar);
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("\n");

			printf("+--------+------------------------------------------------------+\n");
			printf("|   ID   |             NOME DA CATEGORIA DO LIVRO               |\n");
			printf("+--------+------------------------------------------------------+\n");
			MostrarTodosCategoriaLivros();
			printf("Digite o Id da categoria: ");
			scanf("%d", &IdInventarioCategoriaEditar);
			system("cls");
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("|  %04d  |  %04d  |  %-50s  |  %04d  |        |\n", IdInventarioEditar, IdInventarioLivroEditar, NomeLivroInventarioEditar, IdInventarioCategoriaEditar);
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("\n");

			printf("+--------+------------------------------------------------------+\n");
			printf("|   ID   |              NOME DO STATUS DO LIVRO                 |\n");
			printf("+--------+------------------------------------------------------+\n");
			MostrarTodosStatusLivros();
			printf("Digite o Id do Status: ");
			scanf("%d", &IdInventarioStatusEditar);
			system("cls");
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("|  %04d  |  %04d  |  %-50s  |  %04d  |  %04d  |\n", IdInventarioEditar, IdInventarioLivroEditar, NomeLivroInventarioEditar, IdInventarioCategoriaEditar, IdInventarioStatusEditar);
			printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
			printf("\n");

			VarInventario.IdInventarioLivro = IdInventarioLivroEditar;
			strcpy(VarInventario.NomeLivroInventario, NomeLivroInventarioEditar);
			VarInventario.IdInventarioCategoria = IdInventarioCategoriaEditar;
			VarInventario.IdInventarioStatus = IdInventarioStatusEditar;

		}
		EscreverInventario(fpNew, VarInventario);
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosInventarios.txt");
	rename("DadosInventarios_tmp.txt", "DadosInventarios.txt");

	printf("Cadastro editado com sucesso!\n");

}

// 02.04 - Excluir um cadastro de Inventario
void ExcluirCadastroInventario()
{
	int IdInventarioExcluir;
	printf("Digite o ID do Invent%crio a ser exclu%cdo: ", 160, 161);
	scanf("%d", &IdInventarioExcluir);
	getchar();

	FILE *fpOld = fopen("DadosInventarios.txt", "r");
	FILE *fpNew = fopen("DadosInventarios_tmp.txt", "w");

	Inventario VarInventario;
	while (LerInventario(fpOld, &VarInventario) == 5)
	{
		if (VarInventario.IdInventario != IdInventarioExcluir)
		{
			EscreverInventario(fpNew, VarInventario);
		}
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosInventarios.txt");
	rename("DadosInventarios_tmp.txt", "DadosInventarios.txt");

	printf("Cadastro exclu%cdo com sucesso!\n", 161);
}

// 02 - Função para chamar Menu Cadastro Inventario
void MenuCadastroInventario()
{
	int OpMenuCadastroInventario;
	do
	{
		system("cls");
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                      MENU DE INVENT%cRIO                       \xBA%*s\xB3\n", 27, "", 181, 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-NOVO INVENT%cRIO             \xBA 2-MOSTRAR TODAS OS INVENT%cRIOS\xBA%*s\xB3\n", 27, "", 181, 181, 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-EDITAR UM INVENT%cRIO        \xBA 4-EXCLUIR UM INVENT%cRIO       \xBA%*s\xB3\n", 27, "", 181, 181, 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                  0-VOLTAR PARA MENU PRINCIPAL                 \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenuCadastroInventario);
		getchar();

		switch (OpMenuCadastroInventario)
		{
		case 1:
		{
			system("cls");
			CadastrarNovoInventario();
			Sleep(2500);
			system("cls");
			break;
		}
		case 2:
		{
			MostrarTodosInventarios();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				system("pause");
				system("cls");
				printf("Gostaria de imprimir esse arquivo? '1' para SIM ou '2' para N%cO : ", 199);
				int temp;
				scanf("%d", &temp);
				if(temp == 1)
				{
					system("cls");
					ImprimirTempInventario();
					Sleep(2500);
					system("cls");
				}
				else
					system("cls");
			}
			break;
		}
		case 3:
		{
			MostrarTodosInventarios();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				EditarCadastroInventario();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 4:
		{
			MostrarTodosInventarios();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ExcluirCadastroInventario();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 0:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenuCadastroInventario != 0);
}









// 03 - Estrutura para representar um EmprestimoDevolucao
typedef struct
{
	int IdEmprestimoDevolucao;
	char NomeEmprestimoDevolucao[11];
	char DataEmprestimoDevolucao[11];
	int IdEmprestimoDevolucaoAfiliado;
	int IdEmprestimoDevolucaoLivro;
} EmprestimoDevolucao;

// 03 - Função para criar um EmprestimoDevolucao
EmprestimoDevolucao CriarEmprestimoDevolucao(int IdEmprestimoDevolucao, char * NomeEmprestimoDevolucao, char * DataEmprestimoDevolucao, int IdEmprestimoDevolucaoAfiliado, int IdEmprestimoDevolucaoLivro)
{
	EmprestimoDevolucao VarEmprestimoDevolucao;
	VarEmprestimoDevolucao.IdEmprestimoDevolucao = IdEmprestimoDevolucao;
	strcpy(VarEmprestimoDevolucao.NomeEmprestimoDevolucao, NomeEmprestimoDevolucao);
	strcpy(VarEmprestimoDevolucao.DataEmprestimoDevolucao, DataEmprestimoDevolucao);
	VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado = IdEmprestimoDevolucaoAfiliado;
	VarEmprestimoDevolucao.IdEmprestimoDevolucaoLivro = IdEmprestimoDevolucaoLivro;
	return VarEmprestimoDevolucao;
}

// 03 - Função para imprimir um EmprestimoDevolucao
void ImprimirEmprestimoDevolucao(EmprestimoDevolucao VarEmprestimoDevolucao)
{
	printf("|  %04d  |    %-11s   |   %-11s   |  %04d  |  %04d  |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado, VarEmprestimoDevolucao.IdEmprestimoDevolucaoLivro);
	printf("+--------+------------------+-----------------+--------+--------+\n");
}

// 03 - Função para escrever um EmprestimoDevolucao em um arquivo de base de dados
void EscreverEmprestimoDevolucao(FILE * fp, EmprestimoDevolucao VarEmprestimoDevolucao)
{
	fprintf(fp, "%d;%s;%s;%d;%d\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado, VarEmprestimoDevolucao.IdEmprestimoDevolucaoLivro);
}

// 03 - Função para escrever um EmprestimoDevolucao em um arquivo temporário
void EscreverTempEmprestimoDevolucao(FILE * fp, EmprestimoDevolucao VarEmprestimoDevolucao)
{
	fprintf(fp, "|  %04d  |    %-11s   |   %-11s   |  %04d  |  %04d  |\n+--------+------------------+-----------------+--------+--------+\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado, VarEmprestimoDevolucao.IdEmprestimoDevolucaoLivro);
}

// 03 - Função para ler um EmprestimoDevolucao de um arquivo de base de dados
int LerEmprestimoDevolucao(FILE * fp, EmprestimoDevolucao * VarEmprestimoDevolucao)
{
	return fscanf(fp, "%d;%10[^;];%10[^;];%d;%d\n", &VarEmprestimoDevolucao->IdEmprestimoDevolucao, VarEmprestimoDevolucao->NomeEmprestimoDevolucao, VarEmprestimoDevolucao->DataEmprestimoDevolucao, &VarEmprestimoDevolucao->IdEmprestimoDevolucaoAfiliado, &VarEmprestimoDevolucao->IdEmprestimoDevolucaoLivro);
}

// 03 - Função para obter o maior ID de EmprestimoDevolucao
int ObterMaiorIdEmprestimoDevolucao()
{
	FILE *fp = fopen("DadosEmprestimoDevolucaos.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}

	int MaiorIdEmprestimoDevolucao = 0;
	EmprestimoDevolucao VarEmprestimoDevolucao;
	while (LerEmprestimoDevolucao(fp, &VarEmprestimoDevolucao) == 5)
	{
		if (VarEmprestimoDevolucao.IdEmprestimoDevolucao > MaiorIdEmprestimoDevolucao)
		{
			MaiorIdEmprestimoDevolucao = VarEmprestimoDevolucao.IdEmprestimoDevolucao;
		}
	}

	fclose(fp);

	return MaiorIdEmprestimoDevolucao;
}


// 03.01 - Cadastrar novo EmprestimoDevolucao
void CadastrarNovoEmprestimoDevolucao()
{



	int temp;
	char NomeEmprestimoDevolucaoCadastrar[11], DataEmprestimoDevolucaoCadastrar[11];
	int IdEmprestimoDevolucaoAfiliadoCadastrar, IdEmprestimoDevolucaoLivroCadastrar;

	int IdEmprestimoDevolucaoCadastrar = ObterMaiorIdEmprestimoDevolucao() + 1;
	system("cls");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|  %04d  |                  |                 |        |        |\n", IdEmprestimoDevolucaoCadastrar);
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("\n");

	printf("Digite '1' para Empr%cstimo ou '2' para Devolu%c%co: ", 130, 135, 198);
	scanf("%d", &temp);
	if(temp == 1)
	{
		strcpy(NomeEmprestimoDevolucaoCadastrar, "EMPRESTIMO");
	}
	else if(temp == 2)
	{
		strcpy(NomeEmprestimoDevolucaoCadastrar, "DEVOLUCAO ");
	}
	else
	{
		strcpy(NomeEmprestimoDevolucaoCadastrar, "vazio     ");
	}
	system("cls");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|  %04d  |    %-11s   |                 |        |        |\n", IdEmprestimoDevolucaoCadastrar, NomeEmprestimoDevolucaoCadastrar);
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("\n");

	printf("Digite o Data: ");
	scanf("%s", DataEmprestimoDevolucaoCadastrar);
	system("cls");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|  %04d  |    %-11s   |   %-11s   |        |        |\n", IdEmprestimoDevolucaoCadastrar, NomeEmprestimoDevolucaoCadastrar, DataEmprestimoDevolucaoCadastrar);
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("\n");


	MostrarTodosAfiliados();
	printf("\n");
	printf("Digite o Id do Afiliado: ");
	scanf("%d", &IdEmprestimoDevolucaoAfiliadoCadastrar);
	system("cls");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|  %04d  |    %-11s   |   %-11s   |  %04d  |        |\n", IdEmprestimoDevolucaoCadastrar, NomeEmprestimoDevolucaoCadastrar, DataEmprestimoDevolucaoCadastrar, IdEmprestimoDevolucaoAfiliadoCadastrar);
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("\n");

	printf("+--------+------------------------------------------------------+\n");
	printf("|   ID   |                   NOME DO LIVRO                      |\n");
	printf("+--------+------------------------------------------------------+\n");
	MostrarTodosLivros();
	printf("\n");
	printf("Digite o Id do Livro: ");
	scanf("%d", &IdEmprestimoDevolucaoLivroCadastrar);
	system("cls");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("|  %04d  |    %-11s   |   %-11s   |  %04d  |  %04d  |\n", IdEmprestimoDevolucaoCadastrar, NomeEmprestimoDevolucaoCadastrar, DataEmprestimoDevolucaoCadastrar, IdEmprestimoDevolucaoAfiliadoCadastrar, IdEmprestimoDevolucaoLivroCadastrar);
	printf("+--------+------------------+-----------------+--------+--------+\n");
	printf("\n");

	EmprestimoDevolucao VarEmprestimoDevolucao = CriarEmprestimoDevolucao(IdEmprestimoDevolucaoCadastrar, NomeEmprestimoDevolucaoCadastrar, DataEmprestimoDevolucaoCadastrar, IdEmprestimoDevolucaoAfiliadoCadastrar, IdEmprestimoDevolucaoLivroCadastrar);

	FILE *fp = fopen("DadosEmprestimoDevolucaos.txt", "a");
	EscreverEmprestimoDevolucao(fp, VarEmprestimoDevolucao);
	fclose(fp);

	printf("Empr%cstimo Devolu%c%co cadastrado com sucesso!\n", 130, 135, 198);
}

// 03.02 - Mostrar todos os EmprestimoDevolucaos
void MostrarTodosEmprestimoDevolucaos()
{
	FILE *fp = fopen("DadosEmprestimoDevolucaos.txt", "r");
	if (fp == NULL)
	{
		system("cls");
		printf("Empr%cstimos ou Devolu%c%ces ainda não cadastrados!\n", 130, 135, 198);
		TempMostrarTodos = 1;
		Sleep(2500);
		system("cls");
	}
	else
	{
		system("cls");
		printf("+--------+------------------+-----------------+--------+--------+\n");
		printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
		printf("+--------+------------------+-----------------+--------+--------+\n");
		EmprestimoDevolucao VarEmprestimoDevolucao;
		while (LerEmprestimoDevolucao(fp, &VarEmprestimoDevolucao) == 5)
		{
			ImprimirEmprestimoDevolucao(VarEmprestimoDevolucao);
		}
	}
	fclose(fp);
}

// 03.02.01 - Imprimir todos os cadastros de EmprestimoDevolucaos em um arquivo temporário
void ImprimirTempEmprestimoDevolucao()
{
	char NomeArquivoTempEmprestimoDevolucao0[80], NomeArquivoTempEmprestimoDevolucao[80];
	printf("informe o nome do arquivo: \n");
	scanf("%s", NomeArquivoTempEmprestimoDevolucao0);
	sprintf(NomeArquivoTempEmprestimoDevolucao, "%s.txt", NomeArquivoTempEmprestimoDevolucao0);

	FILE *fpOld = fopen("DadosEmprestimoDevolucaos.txt", "r");
	FILE *fpNew = fopen(NomeArquivoTempEmprestimoDevolucao, "w");

	EmprestimoDevolucao VarEmprestimoDevolucao;
	fprintf(fpNew, "+--------+------------------+-----------------+--------+--------+\n");
	fprintf(fpNew, "|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
	fprintf(fpNew, "+--------+------------------+-----------------+--------+--------+\n");

	while (LerEmprestimoDevolucao(fpOld, &VarEmprestimoDevolucao) == 5)
	{
		EscreverTempEmprestimoDevolucao(fpNew, VarEmprestimoDevolucao);
	}

	fclose(fpOld);
	fclose(fpNew);

	printf("Arquivo impresso com sucesso!\n");
}

// 03.03 - Editar um cadastro de EmprestimoDevolucao
void EditarCadastroEmprestimoDevolucao()
{
	int IdEmprestimoDevolucaoEditar;
	printf("Digite o ID do Empr%cstimo Devolu%c%co a ser editado: ", 130, 135, 198);
	scanf("%d", &IdEmprestimoDevolucaoEditar);
	getchar();



	FILE *fpOld = fopen("DadosEmprestimoDevolucaos.txt", "r");
	FILE *fpNew = fopen("DadosEmprestimoDevolucaos_tmp.txt", "w");

	EmprestimoDevolucao VarEmprestimoDevolucao;
	while (LerEmprestimoDevolucao(fpOld, &VarEmprestimoDevolucao) == 5)
	{
		if (VarEmprestimoDevolucao.IdEmprestimoDevolucao == IdEmprestimoDevolucaoEditar)
		{
			system("cls");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|  %04d  |                  |                 |        |        |\n", IdEmprestimoDevolucaoEditar);
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("\n");
			int temp;
			printf("Digite '1' para Empr%cstimo ou '2' para Devolu%c%co: ", 130, 135, 198);
			scanf("%1d", &temp);
			if(temp == 1)
			{
				strcpy(VarEmprestimoDevolucao.NomeEmprestimoDevolucao, "EMPRESTIMO");
			}
			else if(temp == 2)
			{
				strcpy(VarEmprestimoDevolucao.NomeEmprestimoDevolucao, "DEVOLUCAO ");
			}
			else
			{
				strcpy(VarEmprestimoDevolucao.NomeEmprestimoDevolucao, "vazio     ");
			}
			system("cls");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|  %04d  |    %-11s   |                 |        |        |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao);
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("\n");

			printf("Digite o Data: ");
			scanf("%s", VarEmprestimoDevolucao.DataEmprestimoDevolucao);
			system("cls");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|  %04d  |    %-11s   |   %-11s   |        |        |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao);
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("\n");

			MostrarTodosAfiliados();
			printf("\n");
			printf("Digite o Id do Afiliado: ");
			scanf("%d", &VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado);
			system("cls");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|  %04d  |    %-11s   |   %-11s   |  %04d  |        |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado);
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("\n");

			printf("+--------+------------------------------------------------------+\n");
			printf("|   ID   |                   NOME DO LIVRO                      |\n");
			printf("+--------+------------------------------------------------------+\n");
			MostrarTodosLivros();
			printf("\n");
			printf("Digite o Id do Livro: ");
			scanf("%d", &VarEmprestimoDevolucao.IdEmprestimoDevolucaoLivro);
			system("cls");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("|  %04d  |    %-11s   |   %-11s   |  %04d  |  %04d  |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado, VarEmprestimoDevolucao.IdEmprestimoDevolucaoLivro);
			printf("+--------+------------------+-----------------+--------+--------+\n");
			printf("\n");
		}
		EscreverEmprestimoDevolucao(fpNew, VarEmprestimoDevolucao);
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosEmprestimoDevolucaos.txt");
	rename("DadosEmprestimoDevolucaos_tmp.txt", "DadosEmprestimoDevolucaos.txt");

	printf("Cadastro editado com sucesso!\n");
}

// 03.04 - Excluir um cadastro de EmprestimoDevolucao
void ExcluirCadastroEmprestimoDevolucao()
{
	int IdEmprestimoDevolucaoExcluir;
	printf("Digite o ID do EmprestimoDevolucao a ser excluído: ");
	scanf("%d", &IdEmprestimoDevolucaoExcluir);
	getchar();

	FILE *fpOld = fopen("DadosEmprestimoDevolucaos.txt", "r");
	FILE *fpNew = fopen("DadosEmprestimoDevolucaos_tmp.txt", "w");

	EmprestimoDevolucao VarEmprestimoDevolucao;
	while (LerEmprestimoDevolucao(fpOld, &VarEmprestimoDevolucao) == 5)
	{
		if (VarEmprestimoDevolucao.IdEmprestimoDevolucao != IdEmprestimoDevolucaoExcluir)
		{
			EscreverEmprestimoDevolucao(fpNew, VarEmprestimoDevolucao);
		}
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosEmprestimoDevolucaos.txt");
	rename("DadosEmprestimoDevolucaos_tmp.txt", "DadosEmprestimoDevolucaos.txt");

	printf("Cadastro excluído com sucesso!\n");
}

// 03 - Função para chamar Menu Cadastro EmprestimoDevolucao
void MenuCadastroEmprestimoDevolucao()
{
	system("color F0");
	int OpMenuCadastroEmprestimoDevolucao;
	do
	{
		system("cls");
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                  MENU DE EMPR%cSTIMO OU DEVOLU%c%cO              \xBA%*s\xB3\n", 27, "", 144, 128, 199, 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-EMPR%cSTIMOS E DEVOLU%c%cES    \xBA 2-MOSTRAR TODAS OS MOVIMENTOS \xBA%*s\xB3\n", 27, "", 144, 128, 229, 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-EDITAR UM MOVIMENTO         \xBA 4-EXCLUIR UM MOVIMENTO        \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                  0-VOLTAR PARA MENU PRINCIPAL                 \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s\xB3|\n", 27, "", 26, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenuCadastroEmprestimoDevolucao);
		getchar();

		switch (OpMenuCadastroEmprestimoDevolucao)
		{
		case 1:
		{
			system("cls");
			CadastrarNovoEmprestimoDevolucao();
			Sleep(2500);
			system("cls");
			break;
		}
		case 2:
		{
			MostrarTodosEmprestimoDevolucaos();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				system("pause");
				system("cls");
				printf("Gostaria de imprimir esse arquivo? '1' para SIM ou '2' para N%cO : ", 199);
				int temp;
				scanf("%d", &temp);
				if(temp == 1)
				{
					system("cls");
					ImprimirTempEmprestimoDevolucao();
					Sleep(2500);
					system("cls");
				}
				else
					system("cls");
			}
			break;
		}
		case 3:
		{
			MostrarTodosEmprestimoDevolucaos();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				EditarCadastroEmprestimoDevolucao();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 4:
		{
			MostrarTodosEmprestimoDevolucaos();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ExcluirCadastroEmprestimoDevolucao();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 0:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenuCadastroEmprestimoDevolucao != 0);
}










// 04 - Função para chamar Menu Impressão
void MenuImpressao()
{
	system("color F0");
	system("cls");
	int OpMenuCadastro;
	do
	{
		system("cls");
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                       MENU DE IMPRESS%cO                       \xBA%*s\xB3\n", 27, "", 199, 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-AFILIADO                    \xBA 2-LIVRO                       \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-STATUS LIVRO                \xBA 4-CATEGORIA LIVRO             \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 5-EMPR%cSTIMOS E DEVOLU%c%cO     \xBA 6-INVENT%cRIO                  \xBA%*s\xB3\n", 27, "", 144, 128, 199, 181, 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 7-ACESSO                      \xBA 0-VOLTAR PARA MENU PRINCIPAL  \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenuCadastro);
		getchar();

		switch (OpMenuCadastro)
		{
		case 1:
		{
			MostrarTodosAfiliados();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ImprimirTempAfiliado();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 2:
		{
			MostrarTodosLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ImprimirTempLivro();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 3:
		{
			MostrarTodosStatusLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ImprimirTempStatusLivro();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 4:
		{
			MostrarTodosCategoriaLivros();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ImprimirTempCategoriaLivro();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 5:
		{
			MostrarTodosEmprestimoDevolucaos();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ImprimirTempEmprestimoDevolucao();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 6:
		{
			MostrarTodosInventarios();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ImprimirTempInventario();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 7:
		{
			MostrarTodosAcessos();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ImprimirTempAcesso();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 0:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenuCadastro != 0);
}



// 01 - Função para chamar Menu Cadastro
void MenuCadastro()
{
	system("color F0");
	system("cls");
	int OpMenuCadastro;
	do
	{
		system("cls");
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                       MENU DE CADASTRO                        \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-AFILIADO                    \xBA 2-LIVRO                       \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-STATUS LIVRO                \xBA 4-CATEGORIA LIVRO             \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 5-ACESSO                      \xBA 0-VOLTAR PARA MENU PRINCIPAL  \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenuCadastro);
		getchar();

		switch (OpMenuCadastro)
		{
		case 1:
		{
			system("cls");
			MenuCadastroAfiliado();
			break;
		}
		case 2:
		{
			system("cls");
			MenuCadastroLivro();
			break;
		}
		case 3:
		{
			system("cls");
			MenuCadastroStatusLivro();
			break;
		}
		case 4:
		{
			system("cls");
			MenuCadastroCategoriaLivro();
			break;
		}
		case 5:
		{
			system("cls");
			MenuCadastroAcesso();
			break;
		}
		case 0:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenuCadastro != 0);
}







int main()
{
	//setlocale(LC_ALL, "Portuguese");
	system("color F0");
	Acesso Usuarios[30];
	Abertura();
	Login(Usuarios);
	system("cls");
	
	int OpMenu;
	do
	{
		system("color F0");
		system("cls");
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                         MENU PRINCIPAL                        \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-CADASTRO                    \xBA 2-INVENT%cRIO                  \xBA%*s\xB3\n", 27, "", 181, 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-EMPR%cSTIMOS E DEVOLU%c%cES    \xBA 4-IMPRESS%cO                   \xBA%*s\xB3\n", 27, "", 144, 128, 229, 199, 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                            0-SAIR                             \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenu);
		getchar();

		switch (OpMenu)
		{
		case 1:
		{
			system("cls");
			MenuCadastro();
			break;
		}
		case 2:
		{
			
			system("cls");
			MenuCadastroInventario();
			break;
		}
		case 3:
		{
			system("cls");
			MenuCadastroEmprestimoDevolucao();
			break;
		}
		case 4:
		{
			system("cls");
			MenuImpressao();
			break;
		}
		case 9:
		{
			system("cls");
			MenuCadastroAcesso();
			break;
		}
		case 0:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenu != 0);



	return 0;
}
