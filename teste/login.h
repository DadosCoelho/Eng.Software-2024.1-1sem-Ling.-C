

int TempMostrarTodos; // Variavel global


// 01.01 - Estrutura para representar um Acesso
int QtdCamposAcesso = 4;
typedef struct
{
	int IdAcesso;
	char NomeAcesso[50], UsuarioAcesso[15], SenhaAcesso[15];
} Acesso;

// 01.01 - Função para criar um Acesso
Acesso CriarAcesso(int IdAcesso, char* NomeAcesso, char* UsuarioAcesso, char* SenhaAcesso)
{
	Acesso VarAcesso;
	VarAcesso.IdAcesso = IdAcesso;
	strcpy(VarAcesso.NomeAcesso, NomeAcesso);
	strcpy(VarAcesso.UsuarioAcesso, UsuarioAcesso);
	strcpy(VarAcesso.SenhaAcesso, SenhaAcesso);
	return VarAcesso;
}

// 01.01 - Função para imprimir um Acesso
void ImprimirAcesso(Acesso VarAcesso)
{
	printf("|  %04d  |  %-50s  |  %-15s  |\n", VarAcesso.IdAcesso, VarAcesso.NomeAcesso, VarAcesso.UsuarioAcesso);
	printf("+--------+------------------------------------------------------+-------------------+\n");
}


// 01.01 - Função para escrever um Acesso em um arquivo de base de dados
void EscreverAcesso(FILE* fp, Acesso VarAcesso)
{
	fprintf(fp, "%d;%s;%s;%s\n", VarAcesso.IdAcesso, VarAcesso.NomeAcesso, VarAcesso.UsuarioAcesso, VarAcesso.SenhaAcesso);
}

// 01.01 - Função para escrever um Acesso em um arquivo temporário
void EscreverTempAcesso(FILE* fp, Acesso VarAcesso)
{
	fprintf(fp, "|  %04d  |  %-50s  |  %-15s  |  %-15s  |\n+--------+------------------------------------------------------+-------------------+-------------------+\n", VarAcesso.IdAcesso, VarAcesso.NomeAcesso, VarAcesso.UsuarioAcesso, VarAcesso.SenhaAcesso);
}

// 01.01 - Função para ler um Acesso de um arquivo de base de dados
int LerAcesso(FILE* fp, Acesso* VarAcesso)
{
	return fscanf(fp, "%d;%49[^;];%14[^;];%14[^\n]\n", &VarAcesso->IdAcesso, VarAcesso->NomeAcesso, VarAcesso->UsuarioAcesso, VarAcesso->SenhaAcesso);
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
	char UsuarioAcessoCadastrar[15];
	char SenhaAcessoCadastrar[15];
	printf("Digite o nome do Acesso: ");
	fgets(NomeAcessoCadastrar, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
	NomeAcessoCadastrar[strcspn(NomeAcessoCadastrar, "\n")] = 0; // Remove a nova linha do final

	
	printf("Digite o Usuario do Acesso: ");
	fgets(UsuarioAcessoCadastrar, 15, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
	UsuarioAcessoCadastrar[strcspn(UsuarioAcessoCadastrar, "\n")] = 0; // Remove a nova linha do final

	
	printf("Digite a Senha do Acesso: ");

	int i = 0;
	char c;
	while ((c = getch()) != '\r' && i < sizeof(SenhaAcessoCadastrar) - 1)
	{
		SenhaAcessoCadastrar[i++] = c;
		putchar('*');  // Exibe asteriscos no lugar dos caracteres da senha
	}
	SenhaAcessoCadastrar[i] = '\0';  // Termina a string


	int IdAcessoCadastrar = ObterMaiorIdAcesso() + 1;

	Acesso VarAcesso = CriarAcesso(IdAcessoCadastrar, NomeAcessoCadastrar, UsuarioAcessoCadastrar, SenhaAcessoCadastrar);

	FILE *fp = fopen("DadosAcessos.txt", "a");
	EscreverAcesso(fp, VarAcesso);
	fclose(fp);

	printf("\nAcesso cadastrado com sucesso!\n");
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
		printf("+--------+------------------------------------------------------+-------------------+\n");
		printf("|   ID   |                       NOME                           |       LOGIN       |\n");
		printf("+--------+------------------------------------------------------+-------------------+\n");
		Acesso VarAcesso;
		while (LerAcesso(fp, &VarAcesso) == QtdCamposAcesso)
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
	fprintf(fpNew, "+--------+------------------------------------------------------+-------------------+-------------------+\n");
	fprintf(fpNew, "|   ID   |                       NOME                           |       LOGIN       |       SENHA       |\n");
	fprintf(fpNew, "+--------+------------------------------------------------------+-------------------+-------------------+\n");

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

			printf("Digite o novo Usuario do Acesso: ");
			fgets(VarAcesso.UsuarioAcesso, 15, stdin);
			VarAcesso.UsuarioAcesso[strcspn(VarAcesso.UsuarioAcesso, "\n")] = 0;

			printf("Digite a nova senha do Acesso: ");
			int i = 0;
			char c;
			while ((c = getch()) != '\r' && i < sizeof(VarAcesso.SenhaAcesso) - 1)
			{
				VarAcesso.SenhaAcesso[i++] = c;
				putchar('*');  // Exibe asteriscos no lugar dos caracteres da senha
			}
			VarAcesso.SenhaAcesso[i] = '\0';  // Termina a string
		}
		EscreverAcesso(fpNew, VarAcesso);
	}

	fclose(fpOld);
	fclose(fpNew);

	remove("DadosAcessos.txt");
	rename("DadosAcessos_tmp.txt", "DadosAcessos.txt");

	printf("\nCadastro editado com sucesso!\n");
}

// 01.01.04 - Excluir um cadastro de Acesso
void ExcluirCadastroAcesso()
{
	int IdAcessoExcluir;
	printf("Digite o ID do Acesso a ser exclu%cdo: ", 161);
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
		printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xB3\n", 118, "");
		printf("\xB3%*s\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA                  MENU DE CADASTRO DO ACESSO                   \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 1-CADASTRAR NOVO ACESSO       \xBA 2-MOSTRAR TODOS OS ACESSOS    \xBA%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9%*s\xB3\n", 27, "", 26, "");
		printf("\xB3%*s\xBA 3-EDITAR UM ACESSO            \xBA 4-EXCLUIR UM ACESSO           \xBA%*s\xB3\n", 27, "", 26, "");
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

// 00 - Função para Abertura
void Abertura()
{

	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("                  \xDB\xDB\xDB\xDB                                                                                      \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                                                                                    \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                                                                                    \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                                                                                    \n");
	fflush(stdout);
	printf("                  \xDB\xDB                                                                                        \n");
	fflush(stdout);
	printf("                                                                                                            \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                          \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                  \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                  \n");
	fflush(stdout);
	printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                    \n");
	fflush(stdout);
	Sleep(2500);
	system("cls");

	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("                        \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB \n");
	printf("                        \xDB\xDB   \xDB\xDB \xDB\xDB \xDB\xDB   \xDB\xDB \xDB\xDB      \xDB\xDB \xDB\xDB    \xDB\xDB    \xDB\xDB    \xDB\xDB      \xDB\xDB      \xDB\xDB   \xDB\xDB\n");
	printf("                        \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB      \xDB\xDB \xDB\xDB    \xDB\xDB    \xDB\xDB    \xDB\xDB\xDB\xDB\xDB   \xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
	printf("                        \xDB\xDB   \xDB\xDB \xDB\xDB \xDB\xDB   \xDB\xDB \xDB\xDB      \xDB\xDB \xDB\xDB    \xDB\xDB    \xDB\xDB    \xDB\xDB      \xDB\xDB      \xDB\xDB   \xDB\xDB\n");
	printf("                        \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB     \xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB   \xDB\xDB\n");
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("%*s\n          ", 118, "");
	int i;
	for (i = 1; i <= 100; i++)
	{
		printf("%c", 219);
		Sleep(20);
	}

}








// 00 - Função para login
void Login(Acesso VarAcesso[])
{
	system("cls");
	

	int numUsuarios = 0; // Contador de usuários

	// Adicione manualmente o usuário "admin" à lista
	VarAcesso[numUsuarios].IdAcesso = 0;
	strcpy(VarAcesso[numUsuarios].NomeAcesso, "Administrador");
	strcpy(VarAcesso[numUsuarios].UsuarioAcesso, "admin");
	strcpy(VarAcesso[numUsuarios].SenhaAcesso, "123");
	numUsuarios++;

	// Abra o arquivo de Acesso
	FILE* arquivo = fopen("DadosAcessos.txt", "r");
	if (arquivo != NULL)
	{
		// Leia os dados do arquivo e armazene na lista de Acesso VarAcesso
		while (fscanf(arquivo, "%d;%49[^;];%14[^;];%14[^\n]\n",
					  &VarAcesso[numUsuarios].IdAcesso,
					  VarAcesso[numUsuarios].NomeAcesso,
					  VarAcesso[numUsuarios].UsuarioAcesso,
					  VarAcesso[numUsuarios].SenhaAcesso) == 4)
		{
			numUsuarios++;
		}
		fclose(arquivo); // Feche o arquivo
	}

	char UsuarioDigitado[15];
	char SenhaDigitada[15];
	int VerificaUsuario;
	int i;
	VerificaUsuario = 0; // 0 = usuario incorreto; 1 = senha incorreta; 2 senha correta
		system("cls");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("%*sDigite seu Usuario:\n\n", 50, "");
		printf(" %*s ", 50, "");
		scanf("%s", UsuarioDigitado);

		for (i = 0; i < numUsuarios; ++i)
		{
			if (strcmp(UsuarioDigitado, VarAcesso[i].UsuarioAcesso) == 0)
			{
				do
				{
					system("cls");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("%*s   Ol\xA0 %s!\n", 50, "", UsuarioDigitado);
					Sleep(1500);
					printf("\n%*sDigite sua Senha:\n\n", 50, "");
					printf(" %*s ", 55, "");
					
					// Oculta a senha digitada
			        int i2 = 0;
				    char c;
				    while ((c = getch()) != '\r' && i2 < sizeof(SenhaDigitada) - 1) {
				        SenhaDigitada[i2++] = c;
				        putchar('*');  // Exibe asteriscos no lugar dos caracteres da senha
				    }
				    SenhaDigitada[i2] = '\0';  // Termina a string
					
					//scanf("%s", SenhaDigitada);

					if (strcmp(SenhaDigitada, VarAcesso[i].SenhaAcesso) == 0)
					{
						system("cls");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("                                  \xDB\xDF\xDF \xDB\xDF\xDF \xDF\xDF\xDB \xDB\xDF\xDB   \xDB\xDF\xDC \xDB\xDF\xDF \xDB\xDC\xDB   \xDB \xDB \xDF\xDB\xDF \xDB\xDF\xDB \xDB\xDF\xDC \xDB\xDF\xDB \xDB                                 \n");
						printf("                                  \xDF\xDF\xDB \xDB\xDF\xDF   \xDB \xDB\xDF\xDB   \xDB\xDF\xDC \xDB\xDF\xDF \xDB \xDB   \xDF\xDC\xDF  \xDB  \xDB \xDB \xDB \xDB \xDB \xDB \xDF                                 \n");
						printf("                                  \xDF\xDF\xDF \xDF\xDF\xDF \xDF\xDF  \xDF \xDF   \xDF\xDF  \xDF\xDF\xDF \xDF \xDF    \xDF  \xDF\xDF\xDF \xDF \xDF \xDF\xDF  \xDF\xDF\xDF \xDF                                 \n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						Sleep(1500);
						VerificaUsuario = 2;
						break; // Saia do loop, pois encontramos o usuário
					}
					else
					{
						system("cls");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf(" %*s \n", 118, "");
						printf(" %*sSenha incorreta.\n", 50, "");
						printf(" %*s Pressione '1' para tentar novamente ou '2' para sair: \n", 30, "");
						printf(" %*s ", 55, "");

						VerificaUsuario = 1;
						int opcao;
						scanf("%d", &opcao);
						if (opcao != 1)
						{
							break;
							break;
							Acesso usuarios[30]; // Defina um tamanho adequado para o array
							Login(usuarios);
						}
					}
				}
				while (1);   // Loop infinito para senha incorreta
			}
		}
	

		if (VerificaUsuario == 0)
		{
			system("cls");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf(" %*s     Usuario n%co encontrado.    %*s \n", 38, "", 198, 43, "");
			printf(" %*s Escolha uma op%c%co: '1' para tentar novamente, '2' para sair: \n", 25, "", 135, 198);
			printf(" %*s ", 55, "");
						
			int opcaoUsuario;
			scanf("%d", &opcaoUsuario);

			if (opcaoUsuario == 1)
			{
				Acesso usuarios[30]; // Defina um tamanho adequado para o array
				Login(usuarios);
			}
			else if (opcaoUsuario == 2)
			{
				system("cls");
				exit(0); // Encerre o programa
			}
		}
		else if (VerificaUsuario == 1)
		{
			printf(" %*s Escolha uma op%c%co: '1' para digitar o usuario, '2' para sair: \n", 25, "", 135, 198);
			printf(" %*s ", 55, "");
			int opcaoUsuario;
			scanf("%d", &opcaoUsuario);

			if (opcaoUsuario == 1)
			{
				Acesso usuarios[30]; // Defina um tamanho adequado para o array
				Login(usuarios);
			}
			else if (opcaoUsuario == 2)
			{
				system("cls");
				exit(0); // Encerre o programa
			}

		}
		else
		{

		}




}
