// 01.01 - Estrutura para representar um Acesso
int QtdCamposAcesso = 4;
typedef struct
{
	int IdAcesso;
	char NomeAcesso[50], LoginAcesso[50], SenhaAcesso[50];
} Acesso = {1;"Administrador", "adm", "123"};

// 01.01 - Função para criar um Acesso
Acesso CriarAcesso(int IdAcesso, char* NomeAcesso, char* LoginAcesso, char* SenhaAcesso)
{
	Acesso VarAcesso;
	VarAcesso.IdAcesso = IdAcesso;
	strcpy(VarAcesso.NomeAcesso, NomeAcesso);
	strcpy(VarAcesso.LoginAcesso, LoginAcesso);
	strcpy(VarAcesso.SenhaAcesso, SenhaAcesso);
	return VarAcesso;
}

// 01.01 - Função para imprimir um Acesso
void ImprimirAcesso(Acesso VarAcesso)
{
	printf("|  %04d  |  %-50s  |  %-50s  |  %-50s  |\n", VarAcesso.IdAcesso, VarAcesso.NomeAcesso, VarAcesso.LoginAcesso, VarAcesso.SenhaAcesso);
	printf("+--------+------------------------------------------------------+------------------------------------------------------+------------------------------------------------------+\n");
}

// 01.01 - Função para escrever um Acesso em um arquivo de base de dados
void EscreverAcesso(FILE* fp, Acesso VarAcesso)
{
	fprintf(fp, "%d;%49[^;];%49[^;];%49[^\n]\n", VarAcesso.IdAcesso, VarAcesso.NomeAcesso, VarAcesso.LoginAcesso, VarAcesso.SenhaAcesso);
}

// 01.01 - Função para escrever um Acesso em um arquivo temporário
void EscreverTempAcesso(FILE* fp, Acesso VarAcesso)
{
	fprintf(fp, "|  %04d  |  %-50s  |  %-50s  |  %-50s  |\n+--------+------------------------------------------------------++------------------------------------------------------++------------------------------------------------------+\n", VarAcesso.IdAcesso, VarAcesso.NomeAcesso, VarAcesso.LoginAcesso, VarAcesso.SenhaAcesso);
}

// 01.01 - Função para ler um Acesso de um arquivo de base de dados
int LerAcesso(FILE* fp, Acesso* VarAcesso)
{
	return fscanf(fp, "%d;%49[^;];%49[^;];%49[^\n]\n", &VarAcesso->IdAcesso, VarAcesso->NomeAcesso, VarAcesso->LoginAcesso, VarAcesso->SenhaAcesso);
}

// 01.01 - Função para obter o maior ID de Acesso
int ObterMaiorIdAcesso()
{
	FILE *fp = fopen("DadosAcessos.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}

	int MaiorIdAcesso = 0;
	Acesso VarAcesso;
	while (LerAcesso(fp, &VarAcesso) == QtdCamposAcesso)
	{
		if (VarAcesso.IdAcesso > MaiorIdAcesso)
		{
			MaiorIdAcesso = VarAcesso.IdAcesso;
		}
	}

	fclose(fp);

	return MaiorIdAcesso;
}


// 01.01.01 - Cadastrar novo Acesso
void CadastrarNovoAcesso()
{
	char NomeAcessoCadastrar[50];
	char LoginAcessoCadastrar[50];
	char SenhaAcessoCadastrar[50];
	printf("Digite o nome do Acesso: ");
	fgets(NomeAcessoCadastrar, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
	NomeAcessoCadastrar[strcspn(NomeAcessoCadastrar, "\n")] = 0; // Remove a nova linha do final
	
	printf("Digite o Login do Acesso: ");
	fgets(LoginAcessoCadastrar, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
	LoginAcessoCadastrar[strcspn(LoginAcessoCadastrar, "\n")] = 0; // Remove a nova linha do final
	
	printf("Digite a Senha do Acesso: ");
	fgets(SenhaAcessoCadastrar, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
	SenhaAcessoCadastrar[strcspn(SenhaAcessoCadastrar, "\n")] = 0; // Remove a nova linha do final

	int IdAcessoCadastrar = ObterMaiorIdAcesso() + 1;

	Acesso VarAcesso = CriarAcesso(IdAcessoCadastrar, NomeAcessoCadastrar, LoginAcessoCadastrar, SenhaAcessoCadastrar);

	FILE *fp = fopen("DadosAcessos.txt", "a");
	EscreverAcesso(fp, VarAcesso);
	fclose(fp);

	printf("Acesso cadastrado com sucesso!\n");
}

// 01.01.02 - Mostrar todos os Acessos
void MostrarTodosAcessos()
{
	FILE *fp = fopen("DadosAcessos.txt", "r");
	if (fp == NULL)
	{
		system("cls");
		printf("Acessos ainda n%co cadastrados!\n", 198);
		TempMostrarTodos = 1;
		Sleep(2500);
		system("cls");
	}
	else
	{
		system("cls");
		printf("+--------+------------------------------------------------------+------------------------------------------------------+------------------------------------------------------+\n");
		printf("|   ID   |                       NOME                           |                      LOGIN                           |                      SENHA                           |\n");
		printf("+--------+------------------------------------------------------+------------------------------------------------------+------------------------------------------------------+\n");
		Acesso VarAcesso;
		while (LerAcesso(fp, &VarAcesso) == 2)
		{
			ImprimirAcesso(VarAcesso);
		}
	}
	fclose(fp);
}

// 01.01.02.01 - Imprimir todos os cadastros de Acessos em um arquivo temporário
void ImprimirTempAcesso()
{
	char NomeArquivoTempAcesso0[80], NomeArquivoTempAcesso[80];
	printf("Informe o nome do arquivo: \n");
	scanf("%s", NomeArquivoTempAcesso0);
	sprintf(NomeArquivoTempAcesso, "%s.txt", NomeArquivoTempAcesso0);

	FILE *fpOld = fopen("DadosAcessos.txt", "r");
	FILE *fpNew = fopen(NomeArquivoTempAcesso, "w");

	Acesso VarAcesso;
	fprintf(fpNew, "+--------+------------------------------------------------------+------------------------------------------------------+------------------------------------------------------+\n");
	fprintf(fpNew, "|   ID   |                       NOME                           |                      LOGIN                           |                      SENHA                           |\n");
	fprintf(fpNew, "+--------+------------------------------------------------------+------------------------------------------------------+------------------------------------------------------+\n");

	while (LerAcesso(fpOld, &VarAcesso) == QtdCamposAcesso)
	{
		EscreverTempAcesso(fpNew, VarAcesso);
	}

	fclose(fpOld);
	fclose(fpNew);

	printf("Arquivo impresso com sucesso!\n");
}

// 01.01.03 - Editar um cadastro de Acesso
void EditarCadastroAcesso()
{
	int IdAcessoEditar;
	printf("Digite o ID do Acesso a ser editado: ");
	scanf("%d", &IdAcessoEditar);
	getchar(); // Consume o caractere de nova linha

	FILE *fpOld = fopen("DadosAcessos.txt", "r");
	FILE *fpNew = fopen("DadosAcessos_tmp.txt", "w");

	Acesso VarAcesso;
	while (LerAcesso(fpOld, &VarAcesso) == QtdCamposAcesso)
	{
		if (VarAcesso.IdAcesso == IdAcessoEditar)
		{
			printf("Digite o novo nome do Acesso: ");
			fgets(VarAcesso.NomeAcesso, 50, stdin);
			VarAcesso.NomeAcesso[strcspn(VarAcesso.NomeAcesso, "\n")] = 0;
			
			printf("Digite o novo login do Acesso: ");
			fgets(VarAcesso.NomeAcesso, 50, stdin);
			VarAcesso.NomeAcesso[strcspn(VarAcesso.NomeAcesso, "\n")] = 0;
			
			printf("Digite a nova senha do Acesso: ");
			fgets(VarAcesso.NomeAcesso, 50, stdin);
			VarAcesso.NomeAcesso[strcspn(VarAcesso.NomeAcesso, "\n")] = 0;
		}
		EscreverAcesso(fpNew, VarAcesso);
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosAcessos.txt");
	rename("DadosAcessos_tmp.txt", "DadosAcessos.txt");

	printf("Cadastro editado com sucesso!\n");
}

// 01.01.04 - Excluir um cadastro de Acesso
void ExcluirCadastroAcesso()
{
	int IdAcessoExcluir;
	printf("Digite o ID do Acesso a ser excluído: ");
	scanf("%d", &IdAcessoExcluir);
	getchar();

	FILE *fpOld = fopen("DadosAcessos.txt", "r");
	FILE *fpNew = fopen("DadosAcessos_tmp.txt", "w");

	Acesso VarAcesso;
	while (LerAcesso(fpOld, &VarAcesso) == QtdCamposAcesso)
	{
		if (VarAcesso.IdAcesso != IdAcessoExcluir)
		{
			EscreverAcesso(fpNew, VarAcesso);
		}
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosAcessos.txt");
	rename("DadosAcessos_tmp.txt", "DadosAcessos.txt");

	printf("Cadastro exclu%cdo com sucesso!\n", 161);
}


// 01.01 - Função para chamar Menu Cadastro Acesso
void MenuCadastroAcesso()
{
	int OpMenuCadastroAcesso;
	do
	{
		system("cls");
		printf("+----------------------------------------------------------------------------------------------------------------------+\n");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s|\n", 27, "", 26, "");
		printf("|%*s\xBA                  MENU DE CADASTRO DO ACESSO                 \xBA%*s|\n", 27, "", 26, "");
		printf("|%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s|\n", 27, "", 26, "");
		printf("|%*s\xBA 1-CADASTRAR NOVO ACESSO     \xBA 2-MOSTRAR TODOS OS ACESSOS  \xBA%*s|\n", 27, "", 26, "");
		printf("|%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s|\n", 27, "", 26, "");
		printf("|%*s\xBA 3-EDITAR UM ACESSO          \xBA 4-EXCLUIR UM ACESSO         \xBA%*s|\n", 27, "", 26, "");
		printf("|%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s|\n", 27, "", 26, "");
		printf("|%*s\xBA                0-VOLTAR PARA MENU DE CADASTRO                 \xBA%*s|\n", 27, "", 26, "");
		printf("|%*s\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC%*s|\n", 27, "", 26, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("|%*s|\n", 118, "");
		printf("+----------------------------------------------------------------------------------------------------------------------+\n");
		printf("Escolha uma op%c%co: ", 135, 198);
		scanf("%d", &OpMenuCadastroAcesso);
		getchar();

		switch (OpMenuCadastroAcesso)
		{
		case 1:
		{
			system("cls");
			CadastrarNovoAcesso();
			Sleep(2500);
			system("cls");
			break;
		}
		case 2:
		{
			MostrarTodosAcessos();
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
					ImprimirTempAcesso();
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
			MostrarTodosAcessos();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				EditarCadastroAcesso();
				Sleep(2500);
				system("cls");
			}
			break;
		}
		case 4:
		{
			MostrarTodosAcessos();
			if(TempMostrarTodos == 1)
			{
				TempMostrarTodos = 0;
			}
			else
			{
				ExcluirCadastroAcesso();
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
	while (OpMenuCadastroAcesso != 0);
}