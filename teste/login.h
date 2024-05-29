



// 00 - Função para deixar o texto negrito
void bold(int status)
{
	static const char *seq[] = {"\x1b[0m", "\x1b[1m"};
	printf("%s", seq[!!status]);
	//bold(1); // Ativa o negrito
	//bold(0); // Volta ao normal
}



// 00 - Função para login
void login()
{


/*	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|------------------------------|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 0%%         %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);// Espera meio segunde

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|===---------------------------|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 10%%        %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|======------------------------|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 20%%        %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|=========---------------------|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 30%%        %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|============------------------|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 40%%        %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|===============---------------|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 50%%        %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|==================------------|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 60%%        %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|=====================---------|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 70%%        %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|========================------|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 80%%        %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|===========================---|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 90%%        %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(600);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|==============================|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 100%%       %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(100);

	system("cls");
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s|==========CONCLUIDO===========|%*s|\n", 43, "", 43, "");
	printf("|%*s+------------------------------+%*s|\n", 43, "", 43, "");
	printf("|%*s         Carregando: 100%%       %*s|\n", 43, "", 43, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
	printf("|%*s|\n", 118, "");
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
	Sleep(1500);
	system("cls");
*/
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
	printf("%*s\n", 118, "");
    printf("                  \xDB\xDB\xDB\xDB                                                                                      \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                                                                                    \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                                                                                    \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                                                                                    \n");fflush(stdout);
    printf("                  \xDB\xDB                                                                                        \n");fflush(stdout);
    printf("                                                                                                            \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                          \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB            \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB              \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                  \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                  \n");fflush(stdout);
    printf("                \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB          \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB        \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                    \n");fflush(stdout);
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
	for (i=1;i<=100;i++){
      printf("%c", 219);
	  Sleep(25);
	}

	char Usuario[50];
	char Senha[50];
	const char UsuarioCorreto[] = "adm";
	const char SenhaCorreta[] = "123";


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
		printf("%*s        Digite seu Usuario: ", 33, "");

		scanf("%s", Usuario);
		if (strcmp(Usuario, UsuarioCorreto) == 0)
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
				printf("%*s             Ol\xA0 %s!", 33, "", Usuario);
				Sleep(1500);
				
				printf("\n%*s        Digite sua Senha: ", 33, "");
				
				
				//scanf("%s", Senha);
				
				// Oculta a senha digitada
		        int i = 0;
			    char c;
			    while ((c = getch()) != '\r' && i < sizeof(Senha) - 1) {
			        Senha[i++] = c;
			        putchar('*');  // Exibe asteriscos no lugar dos caracteres da senha
			    }
			    Senha[i] = '\0';  // Termina a string
		        
				if (strcmp(Senha, SenhaCorreta) == 0)
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
					break;
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
					printf(" %*s         Senha incorreta.       %*s \n", 43, "", 43, "");
					printf(" %*s         Tente novamente.       %*s \n", 43, "", 43, "");
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
					printf("\n");
					Sleep(1500);
				}
			}
			while(strcmp(Senha, SenhaCorreta) != 0);
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
			printf("\n");
			printf(" %*s     Usuario n%co encontrado.    %*s \n", 43, "", 198, 43, "");
			printf(" %*s         Tente novamente.       %*s \n", 43, "", 43, "");
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
			printf("\n");
			Sleep(1500);
			system("cls");
		}
	}
	while(strcmp(Usuario, UsuarioCorreto) != 0);
}
