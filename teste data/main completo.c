#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Biblioteca para usar caracteres especiais
#include <windows.h> // Para a função Sleep
#include <conio.h> // Para a função Getch

int TempMostrarTodos;

void DifData(int day1, int month1, int year1, int day2, int month2, int year2) {
    struct tm tm1, tm2;
    time_t time1, time2;
    double elapsed_days;

    // Preenche as estruturas tm com os valores fornecidos pelo usuário
    tm1.tm_mday = day1;
    tm1.tm_mon = month1 - 1; // Mês é base 0 (janeiro = 0, fevereiro = 1, etc.)
    tm1.tm_year = year1 - 1900; // Ano é base 1900

    tm2.tm_mday = day2;
    tm2.tm_mon = month2 - 1;
    tm2.tm_year = year2 - 1900;

    // Ajusta os valores para o formato esperado pela função mktime
    tm1.tm_hour = 0;
    tm1.tm_min = 0;
    tm1.tm_sec = 0;

    tm2.tm_hour = 23;
    tm2.tm_min = 59;
    tm2.tm_sec = 59;

    // Converte as estruturas tm para time_t
    time1 = mktime(&tm1);
    time2 = mktime(&tm2);

    // Calcula a diferença em segundos
    elapsed_days = difftime(time2, time1) / (60 * 60 * 24);

    printf("Tempo decorrido: %.0lf dias\n", elapsed_days);
}

// 03 - Estrutura para representar um EmprestimoDevolucao
int QtdCamposEmprestimoDevolucao = 4;
typedef struct
{
	int IdEmprestimoDevolucao;
	char NomeEmprestimoDevolucao[11];
	char DataEmprestimoDevolucao[11];
	int DiasDesdeEmprestimo; // Campo adicional para armazenar a diferença em dias
} EmprestimoDevolucao;

// 03 - Função para criar um EmprestimoDevolucao
EmprestimoDevolucao CriarEmprestimoDevolucao(int IdEmprestimoDevolucao, char * NomeEmprestimoDevolucao, char * DataEmprestimoDevolucao, int DiasDesdeEmprestimo)
{
	EmprestimoDevolucao VarEmprestimoDevolucao;
	VarEmprestimoDevolucao.IdEmprestimoDevolucao = IdEmprestimoDevolucao;
	strcpy(VarEmprestimoDevolucao.NomeEmprestimoDevolucao, NomeEmprestimoDevolucao);
	strcpy(VarEmprestimoDevolucao.DataEmprestimoDevolucao, DataEmprestimoDevolucao);
	VarEmprestimoDevolucao.DiasDesdeEmprestimo = DiasDesdeEmprestimo;
	return VarEmprestimoDevolucao;
}

// 03 - Função para imprimir um EmprestimoDevolucao
void ImprimirEmprestimoDevolucao(EmprestimoDevolucao VarEmprestimoDevolucao)
{
	printf("|  %04d  |    %-11s   |   %-11s   |  %04d  |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.DiasDesdeEmprestimo);
	printf("+--------+------------------+-----------------+--------+\n");
}

// 03 - Função para escrever um EmprestimoDevolucao em um arquivo de base de dados
void EscreverEmprestimoDevolucao(FILE * fp, EmprestimoDevolucao VarEmprestimoDevolucao)
{
	fprintf(fp, "%d;%s;%s;%d\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.DiasDesdeEmprestimo);
}

// 03 - Função para escrever um EmprestimoDevolucao em um arquivo temporário
void EscreverTempEmprestimoDevolucao(FILE * fp, EmprestimoDevolucao VarEmprestimoDevolucao)
{
	fprintf(fp, "|  %04d  |    %-11s   |   %-11s   |  %04d  |\n+--------+------------------+-----------------+--------+\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.DiasDesdeEmprestimo);
}

// Função para ler um EmprestimoDevolucao de um arquivo de base de dados
int LerEmprestimoDevolucao(FILE* fp, EmprestimoDevolucao *VarEmprestimoDevolucao)
{
	int day1, month1, year1;
	int result = fscanf(fp, "%d;%10[^;];%d/%d/%d;%d\n", &VarEmprestimoDevolucao->IdEmprestimoDevolucao, VarEmprestimoDevolucao->NomeEmprestimoDevolucao, &day1, &month1, &year1, &VarEmprestimoDevolucao->DiasDesdeEmprestimo);

	if (result == 5)
	{
		// Ajusta os valores para o formato esperado pela estrutura tm
		VarEmprestimoDevolucao->DataEmprestimoDevolucao[0] = day1;
		VarEmprestimoDevolucao->DataEmprestimoDevolucao[1] = month1;
		VarEmprestimoDevolucao->DataEmprestimoDevolucao[2] = year1;
	}

	return result;
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
	int DiasDesdeEmprestimo;

	int IdEmprestimoDevolucaoCadastrar = ObterMaiorIdEmprestimoDevolucao() + 1;
	system("cls");
	printf("+--------+------------------+-----------------+--------+\n");
	printf("|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
	printf("+--------+------------------+-----------------+--------+\n");
	printf("|  %04d  |                  |                 |        |\n", IdEmprestimoDevolucaoCadastrar);
	printf("+--------+------------------+-----------------+--------+\n");
	printf("\n");

	printf("Digite '1' para Emprestimo ou '2' para Devolucao: ");
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
	printf("+--------+------------------+-----------------+--------+\n");
	printf("|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
	printf("+--------+------------------+-----------------+--------+\n");
	printf("|  %04d  |    %-11s   |                 |        |\n", IdEmprestimoDevolucaoCadastrar, NomeEmprestimoDevolucaoCadastrar);
	printf("+--------+------------------+-----------------+--------+\n");
	printf("\n");

	printf("Digite o Data: ");
	scanf("%s", DataEmprestimoDevolucaoCadastrar);
	system("cls");
	printf("+--------+------------------+-----------------+--------+\n");
	printf("|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
	printf("+--------+------------------+-----------------+--------+\n");
	printf("|  %04d  |    %-11s   |   %-11s   |        |\n", IdEmprestimoDevolucaoCadastrar, NomeEmprestimoDevolucaoCadastrar, DataEmprestimoDevolucaoCadastrar);
	printf("+--------+------------------+-----------------+--------+\n");
	printf("\n");


	system("cls");
	printf("+--------+------------------+-----------------+----------------+\n");
	printf("|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
	printf("+--------+------------------+-----------------+--------+\n");
	printf("|  %04d  |    %-11s   |   %-11s   |  %04d  |\n", IdEmprestimoDevolucaoCadastrar, NomeEmprestimoDevolucaoCadastrar, DataEmprestimoDevolucaoCadastrar, DiasDesdeEmprestimo);
	printf("+--------+------------------+-----------------+--------+\n");
	printf("\n");


	EmprestimoDevolucao VarEmprestimoDevolucao = CriarEmprestimoDevolucao(IdEmprestimoDevolucaoCadastrar, NomeEmprestimoDevolucaoCadastrar, DataEmprestimoDevolucaoCadastrar, DiasDesdeEmprestimo);

	FILE *fp = fopen("DadosEmprestimoDevolucaos.txt", "a");
	EscreverEmprestimoDevolucao(fp, VarEmprestimoDevolucao);
	fclose(fp);

	printf("EmprestimoDevolucao cadastrado com sucesso!\n");
}

// 03.02 - Mostrar todos os EmprestimoDevolucaos
void MostrarTodosEmprestimoDevolucaos()
{
	FILE *fp = fopen("DadosEmprestimoDevolucaos.txt", "r");
	if (fp == NULL)
	{
		system("cls");
		printf("Emprestimos ou Devoluções ainda não cadastrados!\n");
		TempMostrarTodos = 1;
		Sleep(2500);
		system("cls");
	}
	else
	{
		system("cls");
		printf("+--------+------------------+-----------------+--------+\n");
		printf("|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
		printf("+--------+------------------+-----------------+--------+\n");
		EmprestimoDevolucao VarEmprestimoDevolucao;
		while (LerEmprestimoDevolucao(fp, &VarEmprestimoDevolucao) == QtdCamposEmprestimoDevolucao)
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
	fprintf(fpNew, "+--------+------------------+-----------------+--------+\n");
	fprintf(fpNew, "|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
	fprintf(fpNew, "+--------+------------------+-----------------+--------+\n");

	while (LerEmprestimoDevolucao(fpOld, &VarEmprestimoDevolucao) == QtdCamposEmprestimoDevolucao)
	{
		EscreverTempEmprestimoDevolucao(fpNew, VarEmprestimoDevolucao);
	}

	fclose(fpOld);
	fclose(fpNew);

	printf("Arquivo impresso com sucesso!\n");
}



// Função para atualizar o campo DiasDesdeEmprestimo com base na data atual
void AtualizarDiasDesdeEmprestimo(EmprestimoDevolucao *VarEmprestimoDevolucao)
{
	
	FILE *fpOld = fopen("DadosEmprestimoDevolucaos.txt", "r");
	FILE *fpNew = fopen("DadosEmprestimoDevolucaos_tmp.txt", "w");
	
	
	// Extrai os valores de dia, mês e ano da string DataEmprestimoDevolucao
	int day1, month1, year1;
	sscanf(VarEmprestimoDevolucao->DataEmprestimoDevolucao, "%d/%d/%d", &day1, &month1, &year1);
	
	
	time_t now;
	struct tm *local_time;

	time(&now);
	local_time = localtime(&now);
	
	int day2, month2, year2;
	day2 = local_time->tm_mday;
	month2 = local_time->tm_mon + 1;
	year2 = local_time->tm_year + 1900;
	

	/*VarEmprestimoDevolucao->DiasDesdeEmprestimo*/DifData(day1, month1, year1, day2, month2, year2);
}



// 03.03 - Editar um cadastro de EmprestimoDevolucao
void EditarCadastroEmprestimoDevolucao()
{
	int IdEmprestimoDevolucaoEditar;
	printf("Digite o ID do EmprestimoDevolucao a ser editado: ");
	scanf("%d", &IdEmprestimoDevolucaoEditar);
	getchar();



	FILE *fpOld = fopen("DadosEmprestimoDevolucaos.txt", "r");
	FILE *fpNew = fopen("DadosEmprestimoDevolucaos_tmp.txt", "w");

	EmprestimoDevolucao VarEmprestimoDevolucao;
	while (LerEmprestimoDevolucao(fpOld, &VarEmprestimoDevolucao) == QtdCamposEmprestimoDevolucao)
	{
		if (VarEmprestimoDevolucao.IdEmprestimoDevolucao == IdEmprestimoDevolucaoEditar)
		{
			system("cls");
			printf("+--------+------------------+-----------------+--------+\n");
			printf("|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
			printf("+--------+------------------+-----------------+--------+\n");
			printf("|  %04d  |                  |                 |        |\n", IdEmprestimoDevolucaoEditar);
			printf("+--------+------------------+-----------------+--------+\n");
			printf("\n");
			int temp;
			printf("Digite '1' para Emprestimo ou '2' para Devolucao: ");
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
			printf("+--------+------------------+-----------------+--------+\n");
			printf("|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
			printf("+--------+------------------+-----------------+--------+\n");
			printf("|  %04d  |    %-11s   |                 |        |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao);
			printf("+--------+------------------+-----------------+--------+\n");
			printf("\n");

			printf("Digite o Data: ");
			scanf("%s", VarEmprestimoDevolucao.DataEmprestimoDevolucao);
			system("cls");
			printf("+--------+------------------+-----------------+--------+\n");
			printf("|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
			printf("+--------+------------------+-----------------+--------+\n");
			printf("|  %04d  |    %-11s   |   %-11s   |        |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao);
			printf("+--------+------------------+-----------------+--------+\n");
			printf("\n");


			system("cls");
			printf("+--------+------------------+-----------------+--------+\n");
			printf("|   ID   |    EMP OU DEV    |       DATA      | Q DIAS |\n");
			printf("+--------+------------------+-----------------+--------+\n");
			printf("|  %04d  |    %-11s   |   %-11s   |  %04d  |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.DiasDesdeEmprestimo);
			printf("+--------+------------------+-----------------+--------+\n");
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
	while (LerEmprestimoDevolucao(fpOld, &VarEmprestimoDevolucao) == QtdCamposEmprestimoDevolucao)
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
	int OpMenuCadastroEmprestimoDevolucao;
	do
	{
		printf("+---------------------------------------------------------------+\n");
		printf("|             MENU DE CADASTRO DA CATEGORIA DO LIVRO            |\n");
		printf("+-------------------------------+-------------------------------+\n");
		printf("| 1-NOVO EMPRESTIMO OU DEVOLUCAO| 2-MOSTRAR TODAS OS MOVIMENTOS |\n");
		printf("+-------------------------------+-------------------------------+\n");
		printf("| 3-EDITAR UM MOVIMENTO         | 4-EXCLUIR UM MOVIMENTO        |\n");
		printf("+-------------------------------+-------------------------------+\n");
		printf("|                  5-VOLTAR PARA MENU PRINCIPAL                 |\n");
		printf("+-------------------------------+-------------------------------+\n");
		printf("Escolha uma opção: ");
		scanf("%d", &OpMenuCadastroEmprestimoDevolucao);
		getchar();

		switch (OpMenuCadastroEmprestimoDevolucao)
		{
		case 1:
		{
			system("cls");
			AtualizarDiasDesdeEmprestimo();
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
				printf("Gostaria de imprimir esse arquivo? (1) para SIM : ");
				int temp;
				scanf("%d", &temp);
				if(temp == 1)
				{
					system("cls");
					AtualizarDiasDesdeEmprestimo();
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
			AtualizarDiasDesdeEmprestimo();
			MostrarTodosEmprestimoDevolucaos();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				AtualizarDiasDesdeEmprestimo();
				EditarCadastroEmprestimoDevolucao();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 4:
		{
			AtualizarDiasDesdeEmprestimo();
			MostrarTodosEmprestimoDevolucaos();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				AtualizarDiasDesdeEmprestimo();
				ExcluirCadastroEmprestimoDevolucao();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 5:
		{
			system("cls");
			break;
		}
		}
	}
	while (OpMenuCadastroEmprestimoDevolucao != 5);

}


int main()
{

	MenuCadastroEmprestimoDevolucao();

	return 0;

}









