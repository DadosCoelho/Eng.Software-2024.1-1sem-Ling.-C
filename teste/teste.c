#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h> // Biblioteca para usar caracteres especiais

// 01.01 - Estrutura para representar um Afiliado
typedef struct {
    int IdAfiliado;
    char NomeAfiliado[50];
} Afiliado;

// 01.01 - Função para criar um Afiliado
Afiliado CriarAfiliado(int IdAfiliado, char* NomeAfiliado) {
    Afiliado VarAfiliado;
    VarAfiliado.IdAfiliado = IdAfiliado;
    strcpy(VarAfiliado.NomeAfiliado, NomeAfiliado);
    return VarAfiliado;
}

// 01.01 - Função para imprimir um Afiliado
void ImprimirAfiliado(Afiliado VarAfiliado) {
    printf("|  %04d  |  %-50s  |\n", VarAfiliado.IdAfiliado, VarAfiliado.NomeAfiliado);
    printf("+--------+------------------------------------------------------+\n");
}

// 01.01 - Função para escrever um Afiliado em um arquivo
void EscreverAfiliado(FILE* fp, Afiliado VarAfiliado) {
    fprintf(fp, "%d;%s\n", VarAfiliado.IdAfiliado, VarAfiliado.NomeAfiliado);
}

// 01.01 - Função para ler um Afiliado de um arquivo
int LerAfiliado(FILE* fp, Afiliado* VarAfiliado) {
    return fscanf(fp, "%d;%49[^\n]\n", &VarAfiliado->IdAfiliado, VarAfiliado->NomeAfiliado);
}

// 01.01 - Função para obter o maior ID de Afiliado
int ObterMaiorIdAfiliado() {
    FILE *fp = fopen("Afiliados.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    int MaiorIdAfiliado = 0;
    Afiliado VarAfiliado;
    while (LerAfiliado(fp, &VarAfiliado) == 2) {
        if (VarAfiliado.IdAfiliado > MaiorIdAfiliado) {
            MaiorIdAfiliado = VarAfiliado.IdAfiliado;
        }
    }

    fclose(fp);

    return MaiorIdAfiliado;
}


// 01.01.01 - Cadastrar novo Afiliado
void CadastrarNovoAfiliado(){
    char NomeAfiliadoCadastrar[50];
    printf("Digite o nome do Afiliado: ");
    fgets(NomeAfiliadoCadastrar, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
    NomeAfiliadoCadastrar[strcspn(NomeAfiliadoCadastrar, "\n")] = 0; // Remove a nova linha do final

    int IdAfiliadoCadastrar = ObterMaiorIdAfiliado() + 1;

    Afiliado VarAfiliado = CriarAfiliado(IdAfiliadoCadastrar, NomeAfiliadoCadastrar);

    FILE *fp = fopen("Afiliados.txt", "a");
    EscreverAfiliado(fp, VarAfiliado);
    fclose(fp);

    printf("Afiliado cadastrado com sucesso!\n");
}

// 01.01.02 - Mostrar todos os Afiliados
void MostrarTodosAfiliados(){
	FILE *fp = fopen("Afiliados.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    Afiliado VarAfiliado;
    while (LerAfiliado(fp, &VarAfiliado) == 2) {
        ImprimirAfiliado(VarAfiliado);
    }

    fclose(fp);
}

// 01.01.03 - Editar um cadastro de Afiliado
void EditarCadastroAfiliado(){
	int IdAfiliadoEditar;
    printf("Digite o ID do Afiliado a ser editado: ");
    scanf("%d", &IdAfiliadoEditar);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("Afiliados.txt", "r");
    FILE *fpNew = fopen("Afiliados_tmp.txt", "w");

    Afiliado VarAfiliado;
    while (LerAfiliado(fpOld, &VarAfiliado) == 2) {
        if (VarAfiliado.IdAfiliado == IdAfiliadoEditar) {
            printf("Digite o novo nome do Afiliado: ");
            fgets(VarAfiliado.NomeAfiliado, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
            VarAfiliado.NomeAfiliado[strcspn(VarAfiliado.NomeAfiliado, "\n")] = 0; // Remove a nova linha do final
        }
        EscreverAfiliado(fpNew, VarAfiliado);
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("Afiliados.txt");
    rename("Afiliados_tmp.txt", "Afiliados.txt");

    printf("Cadastro editado com sucesso!\n");
}

// 01.01.04 - Excluir um cadastro de Afiliado
void ExcluirCadastroAfiliado(){
	int IdAfiliadoExcluir;
    printf("Digite o ID do Afiliado a ser excluído: ");
    scanf("%d", &IdAfiliadoExcluir);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("Afiliados.txt", "r");
    FILE *fpNew = fopen("Afiliados_tmp.txt", "w");

    Afiliado VarAfiliado;
    while (LerAfiliado(fpOld, &VarAfiliado) == 2) {
        if (VarAfiliado.IdAfiliado != IdAfiliadoExcluir) {
            EscreverAfiliado(fpNew, VarAfiliado);
        }
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("Afiliados.txt");
    rename("Afiliados_tmp.txt", "Afiliados.txt");

    printf("Cadastro excluído com sucesso!\n");
}

// 01.01 - Função para chamar Menu Cadastro Afiliado
void MenuCadastroAfiliado(){
    int OpMenuCadastroAfiliado;
    do {
    	printf("+---------------------------------------------------------------+\n");
    	printf("|                  MENU DE CADASTRO DO AFILIADO                 |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 1-CADASTRAR NOVO AFILIADO     | 2-MOSTRAR TODOS OS AFILIADOS  |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 3-EDITAR UM AFILIADO          | 4-EXCLUIR UM AFILIADO         |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("|                5-VOLTAR PARA MENU DE CADASTRO                 |\n");
		printf("+-------------------------------+-------------------------------+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &OpMenuCadastroAfiliado);
        getchar(); // Consume o caractere de nova linha
        
        switch (OpMenuCadastroAfiliado) {
            case 1: {
            	system("cls");
            	CadastrarNovoAfiliado();
            	system("pause");
                system("cls");
                break;
            }
            case 2: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |                  NOME DO AFILIADO                    |\n");
				printf("+--------+------------------------------------------------------+\n");
                MostrarTodosAfiliados();
                system("pause");
                system("cls");
                break;
            }
            case 3: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |                  NOME DO AFILIADO                    |\n");
				printf("+--------+------------------------------------------------------+\n");
				MostrarTodosAfiliados();
                EditarCadastroAfiliado();
                system("pause");
                system("cls");
                break;
            }
            case 4: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |                  NOME DO AFILIADO                    |\n");
				printf("+--------+------------------------------------------------------+\n");
				MostrarTodosAfiliados();
                ExcluirCadastroAfiliado();
                system("pause");
                system("cls");
                break;
            }
            case 5: {
				system("cls");
				break;
			}
        }
    } while (OpMenuCadastroAfiliado != 5);
}





// 01.02 - Estrutura para representar um Livro
typedef struct {
    int IdLivro;
    char NomeLivro[50];
} Livro;

// 01.02 - Função para criar um Livro
Livro CriarLivro(int IdLivro, char* NomeLivro) {
    Livro VarLivro;
    VarLivro.IdLivro = IdLivro;
    strcpy(VarLivro.NomeLivro, NomeLivro);
    return VarLivro;
}

// 01.02 - Função para imprimir um Livro
void ImprimirLivro(Livro VarLivro) {
    printf("|  %04d  |  %-50s  |\n", VarLivro.IdLivro, VarLivro.NomeLivro);
    printf("+--------+------------------------------------------------------+\n");
}

// 01.02 - Função para escrever um Livro em um arquivo
void EscreverLivro(FILE* fp, Livro VarLivro) {
    fprintf(fp, "%d;%s\n", VarLivro.IdLivro, VarLivro.NomeLivro);
}

// 01.02 - Função para ler um Livro de um arquivo
int LerLivro(FILE* fp, Livro* VarLivro) {
    return fscanf(fp, "%d;%49[^\n]\n", &VarLivro->IdLivro, VarLivro->NomeLivro);
}

// 01.02 - Função para obter o maior ID de Livro
int ObterMaiorIdLivro() {
    FILE *fp = fopen("Livros.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    int MaiorIdLivro = 0;
    Livro VarLivro;
    while (LerLivro(fp, &VarLivro) == 2) {
        if (VarLivro.IdLivro > MaiorIdLivro) {
            MaiorIdLivro = VarLivro.IdLivro;
        }
    }

    fclose(fp);

    return MaiorIdLivro;
}


// 01.02.01 - Cadastrar novo Livro
void CadastrarNovoLivro(){
    char NomeLivroCadastrar[50];
    printf("Digite o nome do Livro: ");
    fgets(NomeLivroCadastrar, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
    NomeLivroCadastrar[strcspn(NomeLivroCadastrar, "\n")] = 0; // Remove a nova linha do final

    int IdLivroCadastrar = ObterMaiorIdLivro() + 1;

    Livro VarLivro = CriarLivro(IdLivroCadastrar, NomeLivroCadastrar);

    FILE *fp = fopen("Livros.txt", "a");
    EscreverLivro(fp, VarLivro);
    fclose(fp);

    printf("Livro cadastrado com sucesso!\n");
}

// 01.02.02 - Mostrar todos os Livros
void MostrarTodosLivros(){
	FILE *fp = fopen("Livros.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    Livro VarLivro;
    while (LerLivro(fp, &VarLivro) == 2) {
        ImprimirLivro(VarLivro);
    }

    fclose(fp);
}

// 01.02.03 - Editar um cadastro de Livro
void EditarCadastroLivro(){
	int IdLivroEditar;
    printf("Digite o ID do Livro a ser editado: ");
    scanf("%d", &IdLivroEditar);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("Livros.txt", "r");
    FILE *fpNew = fopen("Livros_tmp.txt", "w");

    Livro VarLivro;
    while (LerLivro(fpOld, &VarLivro) == 2) {
        if (VarLivro.IdLivro == IdLivroEditar) {
            printf("Digite o novo nome do Livro: ");
            fgets(VarLivro.NomeLivro, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
            VarLivro.NomeLivro[strcspn(VarLivro.NomeLivro, "\n")] = 0; // Remove a nova linha do final
        }
        EscreverLivro(fpNew, VarLivro);
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("Livros.txt");
    rename("Livros_tmp.txt", "Livros.txt");

    printf("Cadastro editado com sucesso!\n");
}

// 01.02.04 - Excluir um cadastro de Livro
void ExcluirCadastroLivro(){
	int IdLivroExcluir;
    printf("Digite o ID do Livro a ser excluído: ");
    scanf("%d", &IdLivroExcluir);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("Livros.txt", "r");
    FILE *fpNew = fopen("Livros_tmp.txt", "w");

    Livro VarLivro;
    while (LerLivro(fpOld, &VarLivro) == 2) {
        if (VarLivro.IdLivro != IdLivroExcluir) {
            EscreverLivro(fpNew, VarLivro);
        }
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("Livros.txt");
    rename("Livros_tmp.txt", "Livros.txt");

    printf("Cadastro excluído com sucesso!\n");
}

// 01.02 - Função para chamar Menu Cadastro Livro
void MenuCadastroLivro(){
    int OpMenuCadastroLivro;
    do {
    	printf("+---------------------------------------------------------------+\n");
    	printf("|                  MENU DE CADASTRO DO LIVRO                    |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 1-CADASTRAR NOVO LIVRO        | 2-MOSTRAR TODOS OS LIVROS     |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 3-EDITAR UM LIVRO             | 4-EXCLUIR UM LIVRO            |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("|                5-VOLTAR PARA MENU DE CADASTRO                 |\n");
		printf("+-------------------------------+-------------------------------+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &OpMenuCadastroLivro);
        getchar(); // Consume o caractere de nova linha
        
        switch (OpMenuCadastroLivro) {
            case 1: {
            	system("cls");
            	CadastrarNovoLivro();
            	system("pause");
                system("cls");
                break;
            }
            case 2: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |                   NOME DO LIVRO                      |\n");
				printf("+--------+------------------------------------------------------+\n");
                MostrarTodosLivros();
                system("pause");
                system("cls");
                break;
            }
            case 3: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |                   NOME DO LIVRO                      |\n");
				printf("+--------+------------------------------------------------------+\n");
            	MostrarTodosLivros();
                EditarCadastroLivro();
                system("pause");
                system("cls");
                break;
            }
            case 4: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |                   NOME DO LIVRO                      |\n");
				printf("+--------+------------------------------------------------------+\n");
            	MostrarTodosLivros();
                ExcluirCadastroLivro();
                system("pause");
                system("cls");
                break;
            }
            case 5: {
				system("cls");
				break;
			}
        }
    } while (OpMenuCadastroLivro != 5);
}





// 01.03 - Estrutura para representar um StatusLivro
typedef struct {
    int IdStatusLivro;
    char NomeStatusLivro[50];
} StatusLivro;

// 01.03 - Função para criar um StatusLivro
StatusLivro CriarStatusLivro(int IdStatusLivro, char* NomeStatusLivro) {
    StatusLivro VarStatusLivro;
    VarStatusLivro.IdStatusLivro = IdStatusLivro;
    strcpy(VarStatusLivro.NomeStatusLivro, NomeStatusLivro);
    return VarStatusLivro;
}

// 01.03 - Função para imprimir um StatusLivro
void ImprimirStatusLivro(StatusLivro VarStatusLivro) {
    printf("|  %04d  |  %-50s  |\n", VarStatusLivro.IdStatusLivro, VarStatusLivro.NomeStatusLivro);
    printf("+--------+------------------------------------------------------+\n");
}

// 01.03 - Função para escrever um StatusLivro em um arquivo
void EscreverStatusLivro(FILE* fp, StatusLivro VarStatusLivro) {
    fprintf(fp, "%d;%s\n", VarStatusLivro.IdStatusLivro, VarStatusLivro.NomeStatusLivro);
}

// 01.03 - Função para ler um StatusLivro de um arquivo
int LerStatusLivro(FILE* fp, StatusLivro* VarStatusLivro) {
    return fscanf(fp, "%d;%49[^\n]\n", &VarStatusLivro->IdStatusLivro, VarStatusLivro->NomeStatusLivro);
}

// 01.03 - Função para obter o maior ID de StatusLivro
int ObterMaiorIdStatusLivro() {
    FILE *fp = fopen("StatusLivros.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    int MaiorIdStatusLivro = 0;
    StatusLivro VarStatusLivro;
    while (LerStatusLivro(fp, &VarStatusLivro) == 2) {
        if (VarStatusLivro.IdStatusLivro > MaiorIdStatusLivro) {
            MaiorIdStatusLivro = VarStatusLivro.IdStatusLivro;
        }
    }

    fclose(fp);

    return MaiorIdStatusLivro;
}


// 01.03.01 - Cadastrar novo StatusLivro
void CadastrarNovoStatusLivro(){
    char NomeStatusLivroCadastrar[50];
    printf("Digite o nome do StatusLivro: ");
    fgets(NomeStatusLivroCadastrar, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
    NomeStatusLivroCadastrar[strcspn(NomeStatusLivroCadastrar, "\n")] = 0; // Remove a nova linha do final

    int IdStatusLivroCadastrar = ObterMaiorIdStatusLivro() + 1;

    StatusLivro VarStatusLivro = CriarStatusLivro(IdStatusLivroCadastrar, NomeStatusLivroCadastrar);

    FILE *fp = fopen("StatusLivros.txt", "a");
    EscreverStatusLivro(fp, VarStatusLivro);
    fclose(fp);

    printf("StatusLivro cadastrado com sucesso!\n");
}

// 01.03.02 - Mostrar todos os StatusLivros
void MostrarTodosStatusLivros(){
	FILE *fp = fopen("StatusLivros.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    StatusLivro VarStatusLivro;
    while (LerStatusLivro(fp, &VarStatusLivro) == 2) {
        ImprimirStatusLivro(VarStatusLivro);
    }

    fclose(fp);
}

// 01.03.03 - Editar um cadastro de StatusLivro
void EditarCadastroStatusLivro(){
	int IdStatusLivroEditar;
    printf("Digite o ID do StatusLivro a ser editado: ");
    scanf("%d", &IdStatusLivroEditar);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("StatusLivros.txt", "r");
    FILE *fpNew = fopen("StatusLivros_tmp.txt", "w");

    StatusLivro VarStatusLivro;
    while (LerStatusLivro(fpOld, &VarStatusLivro) == 2) {
        if (VarStatusLivro.IdStatusLivro == IdStatusLivroEditar) {
            printf("Digite o novo nome do StatusLivro: ");
            fgets(VarStatusLivro.NomeStatusLivro, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
            VarStatusLivro.NomeStatusLivro[strcspn(VarStatusLivro.NomeStatusLivro, "\n")] = 0; // Remove a nova linha do final
        }
        EscreverStatusLivro(fpNew, VarStatusLivro);
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("StatusLivros.txt");
    rename("StatusLivros_tmp.txt", "StatusLivros.txt");

    printf("Cadastro editado com sucesso!\n");
}

// 01.03.04 - Excluir um cadastro de StatusLivro
void ExcluirCadastroStatusLivro(){
	int IdStatusLivroExcluir;
    printf("Digite o ID do StatusLivro a ser excluído: ");
    scanf("%d", &IdStatusLivroExcluir);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("StatusLivros.txt", "r");
    FILE *fpNew = fopen("StatusLivros_tmp.txt", "w");

    StatusLivro VarStatusLivro;
    while (LerStatusLivro(fpOld, &VarStatusLivro) == 2) {
        if (VarStatusLivro.IdStatusLivro != IdStatusLivroExcluir) {
            EscreverStatusLivro(fpNew, VarStatusLivro);
        }
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("StatusLivros.txt");
    rename("StatusLivros_tmp.txt", "StatusLivros.txt");

    printf("Cadastro excluído com sucesso!\n");
}

// 01.03 - Função para chamar Menu Cadastro StatusLivro
void MenuCadastroStatusLivro(){
	system("cls");
    int OpMenuCadastroStatusLivro;
    do {
    	printf("+---------------------------------------------------------------+\n");
    	printf("|                MENU DE CADASTRO DO STATUS DO LIVRO            |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 1-CADASTRAR NOVO STATUS       | 2-MOSTRAR TODOS OS STATUS     |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 3-EDITAR UM STATUS            | 4-EXCLUIR UM STATUS           |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("|                5-VOLTAR PARA MENU DE CADASTRO                 |\n");
		printf("+-------------------------------+-------------------------------+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &OpMenuCadastroStatusLivro);
        getchar(); // Consume o caractere de nova linha
        
        switch (OpMenuCadastroStatusLivro) {
            case 1: {
            	system("cls");
            	CadastrarNovoStatusLivro();
            	system("pause");
                system("cls");
                break;
            }
            case 2: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |              NOME DO STATUS DO LIVRO                 |\n");
				printf("+--------+------------------------------------------------------+\n");
                MostrarTodosStatusLivros();
                system("pause");
                system("cls");
                break;
            }
            case 3: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |              NOME DO STATUS DO LIVRO                 |\n");
				printf("+--------+------------------------------------------------------+\n");
            	MostrarTodosStatusLivros();
                EditarCadastroStatusLivro();
                system("pause");
                system("cls");
                break;
            }
            case 4: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |              NOME DO STATUS DO LIVRO                 |\n");
				printf("+--------+------------------------------------------------------+\n");
            	MostrarTodosStatusLivros();
                ExcluirCadastroStatusLivro();
                system("pause");
                system("cls");
                break;
            }
            case 5: {
				system("cls");
				break;
			}
        }
    } while (OpMenuCadastroStatusLivro != 5);
}







// 01.04 - Estrutura para representar um CategoriaLivro
typedef struct {
    int IdCategoriaLivro;
    char NomeCategoriaLivro[50];
} CategoriaLivro;

// 01.04 - Função para criar um CategoriaLivro
CategoriaLivro CriarCategoriaLivro(int IdCategoriaLivro, char* NomeCategoriaLivro) {
    CategoriaLivro VarCategoriaLivro;
    VarCategoriaLivro.IdCategoriaLivro = IdCategoriaLivro;
    strcpy(VarCategoriaLivro.NomeCategoriaLivro, NomeCategoriaLivro);
    return VarCategoriaLivro;
}

// 01.04 - Função para imprimir um CategoriaLivro
void ImprimirCategoriaLivro(CategoriaLivro VarCategoriaLivro) {
    printf("|  %04d  |  %-50s  |\n", VarCategoriaLivro.IdCategoriaLivro, VarCategoriaLivro.NomeCategoriaLivro);
    printf("+--------+------------------------------------------------------+\n");
}

// 01.04 - Função para escrever um CategoriaLivro em um arquivo
void EscreverCategoriaLivro(FILE* fp, CategoriaLivro VarCategoriaLivro) {
    fprintf(fp, "%d;%s\n", VarCategoriaLivro.IdCategoriaLivro, VarCategoriaLivro.NomeCategoriaLivro);
}

// 01.04 - Função para ler um CategoriaLivro de um arquivo
int LerCategoriaLivro(FILE* fp, CategoriaLivro* VarCategoriaLivro) {
    return fscanf(fp, "%d;%49[^\n]\n", &VarCategoriaLivro->IdCategoriaLivro, VarCategoriaLivro->NomeCategoriaLivro);
}

// 01.04 - Função para obter o maior ID de CategoriaLivro
int ObterMaiorIdCategoriaLivro() {
    FILE *fp = fopen("CategoriaLivros.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    int MaiorIdCategoriaLivro = 0;
    CategoriaLivro VarCategoriaLivro;
    while (LerCategoriaLivro(fp, &VarCategoriaLivro) == 2) {
        if (VarCategoriaLivro.IdCategoriaLivro > MaiorIdCategoriaLivro) {
            MaiorIdCategoriaLivro = VarCategoriaLivro.IdCategoriaLivro;
        }
    }

    fclose(fp);

    return MaiorIdCategoriaLivro;
}


// 01.04.01 - Cadastrar novo CategoriaLivro
void CadastrarNovoCategoriaLivro(){
    char NomeCategoriaLivroCadastrar[50];
    printf("Digite o nome do CategoriaLivro: ");
    fgets(NomeCategoriaLivroCadastrar, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
    NomeCategoriaLivroCadastrar[strcspn(NomeCategoriaLivroCadastrar, "\n")] = 0; // Remove a nova linha do final

    int IdCategoriaLivroCadastrar = ObterMaiorIdCategoriaLivro() + 1;

    CategoriaLivro VarCategoriaLivro = CriarCategoriaLivro(IdCategoriaLivroCadastrar, NomeCategoriaLivroCadastrar);

    FILE *fp = fopen("CategoriaLivros.txt", "a");
    EscreverCategoriaLivro(fp, VarCategoriaLivro);
    fclose(fp);

    printf("CategoriaLivro cadastrado com sucesso!\n");
}

// 01.04.02 - Mostrar todos os CategoriaLivros
void MostrarTodosCategoriaLivros(){
	FILE *fp = fopen("CategoriaLivros.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    CategoriaLivro VarCategoriaLivro;
    while (LerCategoriaLivro(fp, &VarCategoriaLivro) == 2) {
        ImprimirCategoriaLivro(VarCategoriaLivro);
    }

    fclose(fp);
}

// 01.04.03 - Editar um cadastro de CategoriaLivro
void EditarCadastroCategoriaLivro(){
	int IdCategoriaLivroEditar;
    printf("Digite o ID do CategoriaLivro a ser editado: ");
    scanf("%d", &IdCategoriaLivroEditar);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("CategoriaLivros.txt", "r");
    FILE *fpNew = fopen("CategoriaLivros_tmp.txt", "w");

    CategoriaLivro VarCategoriaLivro;
    while (LerCategoriaLivro(fpOld, &VarCategoriaLivro) == 2) {
        if (VarCategoriaLivro.IdCategoriaLivro == IdCategoriaLivroEditar) {
            printf("Digite o novo nome do CategoriaLivro: ");
            fgets(VarCategoriaLivro.NomeCategoriaLivro, 50, stdin); // Diferente do scanf, o fgets armazena permitindo o espaço
            VarCategoriaLivro.NomeCategoriaLivro[strcspn(VarCategoriaLivro.NomeCategoriaLivro, "\n")] = 0; // Remove a nova linha do final
        }
        EscreverCategoriaLivro(fpNew, VarCategoriaLivro);
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("CategoriaLivros.txt");
    rename("CategoriaLivros_tmp.txt", "CategoriaLivros.txt");

    printf("Cadastro editado com sucesso!\n");
}

// 01.04.04 - Excluir um cadastro de CategoriaLivro
void ExcluirCadastroCategoriaLivro(){
	int IdCategoriaLivroExcluir;
    printf("Digite o ID do CategoriaLivro a ser excluído: ");
    scanf("%d", &IdCategoriaLivroExcluir);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("CategoriaLivros.txt", "r");
    FILE *fpNew = fopen("CategoriaLivros_tmp.txt", "w");

    CategoriaLivro VarCategoriaLivro;
    while (LerCategoriaLivro(fpOld, &VarCategoriaLivro) == 2) {
        if (VarCategoriaLivro.IdCategoriaLivro != IdCategoriaLivroExcluir) {
            EscreverCategoriaLivro(fpNew, VarCategoriaLivro);
        }
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("CategoriaLivros.txt");
    rename("CategoriaLivros_tmp.txt", "CategoriaLivros.txt");

    printf("Cadastro excluído com sucesso!\n");
}

// 01.04 - Função para chamar Menu Cadastro CategoriaLivro
void MenuCadastroCategoriaLivro(){
    int OpMenuCadastroCategoriaLivro;
    do {
    	printf("+---------------------------------------------------------------+\n");
    	printf("|             MENU DE CADASTRO DA CATEGORIA DO LIVRO            |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 1-CADASTRAR NOVA CATEGORIA    | 2-MOSTRAR TODAS AS CATEGORIAS |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 3-EDITAR UMA CATEGORIA        | 4-EXCLUIR UMA CATEGORIA       |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("|                5-VOLTAR PARA MENU DE CADASTRO                 |\n");
		printf("+-------------------------------+-------------------------------+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &OpMenuCadastroCategoriaLivro);
        getchar(); // Consume o caractere de nova linha
        
        switch (OpMenuCadastroCategoriaLivro) {
            case 1: {
            	system("cls");
            	CadastrarNovoCategoriaLivro();
            	system("pause");
                system("cls");
                break;
            }
            case 2: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |             NOME DA CATEGORIA DO LIVRO               |\n");
				printf("+--------+------------------------------------------------------+\n");
                MostrarTodosCategoriaLivros();
                system("pause");
                system("cls");
                break;
            }
            case 3: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |             NOME DA CATEGORIA DO LIVRO               |\n");
				printf("+--------+------------------------------------------------------+\n");
            	MostrarTodosCategoriaLivros();
                EditarCadastroCategoriaLivro();
                system("pause");
                system("cls");
                break;
            }
            case 4: {
            	system("cls");
            	printf("+--------+------------------------------------------------------+\n");
				printf("|   ID   |             NOME DA CATEGORIA DO LIVRO               |\n");
				printf("+--------+------------------------------------------------------+\n");
            	MostrarTodosCategoriaLivros();
                ExcluirCadastroCategoriaLivro();
                system("pause");
                system("cls");
                break;
            }
            case 5: {
				system("cls");
				break;
			}
        }
    } while (OpMenuCadastroCategoriaLivro != 5);
}





// 02 - Estrutura para representar um EmprestimoDevolucao
typedef struct {
    int IdEmprestimoDevolucao;
    char NomeEmprestimoDevolucao[11];
    char DataEmprestimoDevolucao[11];
    int IdEmprestimoDevolucaoAfiliado;
    int IdEmprestimoDevolucaoLivro;
} EmprestimoDevolucao;

// 02 - Função para criar um EmprestimoDevolucao
EmprestimoDevolucao CriarEmprestimoDevolucao(int IdEmprestimoDevolucao, char* NomeEmprestimoDevolucao, char* DataEmprestimoDevolucao, int IdEmprestimoDevolucaoAfiliado, int IdEmprestimoDevolucaoLivro) {
    EmprestimoDevolucao VarEmprestimoDevolucao;
    VarEmprestimoDevolucao.IdEmprestimoDevolucao = IdEmprestimoDevolucao;
    strcpy(VarEmprestimoDevolucao.NomeEmprestimoDevolucao, NomeEmprestimoDevolucao);
    strcpy(VarEmprestimoDevolucao.DataEmprestimoDevolucao, DataEmprestimoDevolucao);
    VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado = IdEmprestimoDevolucaoAfiliado;
    VarEmprestimoDevolucao.IdEmprestimoDevolucaoLivro = IdEmprestimoDevolucaoLivro;
    return VarEmprestimoDevolucao;
}

// 02 - Função para imprimir um EmprestimoDevolucao
void ImprimirEmprestimoDevolucao(EmprestimoDevolucao VarEmprestimoDevolucao) {
    printf("|  %04d  |    %-11s   |   %-11s   |  %04d  |  %04d  |\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado, VarEmprestimoDevolucao.IdEmprestimoDevolucaoLivro);
    printf("+--------+------------------+-----------------+--------+--------+\n");
}

// 02 - Função para escrever um EmprestimoDevolucao em um arquivo
void EscreverEmprestimoDevolucao(FILE* fp, EmprestimoDevolucao VarEmprestimoDevolucao) {
    fprintf(fp, "%d;%s;%s;%d;%d\n", VarEmprestimoDevolucao.IdEmprestimoDevolucao, VarEmprestimoDevolucao.NomeEmprestimoDevolucao, VarEmprestimoDevolucao.DataEmprestimoDevolucao, VarEmprestimoDevolucao.IdEmprestimoDevolucaoAfiliado, VarEmprestimoDevolucao.IdEmprestimoDevolucaoLivro);
}

// 02 - Função para ler um EmprestimoDevolucao de um arquivo
int LerEmprestimoDevolucao(FILE* fp, EmprestimoDevolucao* VarEmprestimoDevolucao) {
    return fscanf(fp, "%d;%10[^;];%10[^;];%d;%d\n", &VarEmprestimoDevolucao->IdEmprestimoDevolucao, VarEmprestimoDevolucao->NomeEmprestimoDevolucao, VarEmprestimoDevolucao->DataEmprestimoDevolucao, &VarEmprestimoDevolucao->IdEmprestimoDevolucaoAfiliado, &VarEmprestimoDevolucao->IdEmprestimoDevolucaoLivro);
}

// 02 - Função para obter o maior ID de EmprestimoDevolucao
int ObterMaiorIdEmprestimoDevolucao() {
    FILE *fp = fopen("EmprestimoDevolucaos.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    int MaiorIdEmprestimoDevolucao = 0;
    EmprestimoDevolucao VarEmprestimoDevolucao;
    while (LerEmprestimoDevolucao(fp, &VarEmprestimoDevolucao) == 5) {
        if (VarEmprestimoDevolucao.IdEmprestimoDevolucao > MaiorIdEmprestimoDevolucao) {
            MaiorIdEmprestimoDevolucao = VarEmprestimoDevolucao.IdEmprestimoDevolucao;
        }
    }

    fclose(fp);

    return MaiorIdEmprestimoDevolucao;
}


// 02.01 - Cadastrar novo EmprestimoDevolucao
void CadastrarNovoEmprestimoDevolucao(){
    
    
    
    int temp;
    char NomeEmprestimoDevolucaoCadastrar[11], DataEmprestimoDevolucaoCadastrar[11];
    int IdEmprestimoDevolucaoAfiliadoCadastrar, IdEmprestimoDevolucaoLivroCadastrar;
	
	int IdEmprestimoDevolucaoCadastrar = ObterMaiorIdEmprestimoDevolucao() + 1;
	
	printf("\n");
	printf("Digite '1' para Emprestimo ou '2' para Devolucao: ");
    scanf("%d", &temp);
    if(temp == 1){
        strcpy(NomeEmprestimoDevolucaoCadastrar, "EMPRESTIMO");
    } else if(temp == 2){
        strcpy(NomeEmprestimoDevolucaoCadastrar, "DEVOLUCAO ");
    } else {
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
    
    
	printf("+--------+------------------------------------------------------+\n");
	printf("|   ID   |                  NOME DO AFILIADO                    |\n");
	printf("+--------+------------------------------------------------------+\n");    
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

    FILE *fp = fopen("EmprestimoDevolucaos.txt", "a");
    EscreverEmprestimoDevolucao(fp, VarEmprestimoDevolucao);
    fclose(fp);

    printf("EmprestimoDevolucao cadastrado com sucesso!\n");
}

// 02.02 - Mostrar todos os EmprestimoDevolucaos
void MostrarTodosEmprestimoDevolucaos(){
	FILE *fp = fopen("EmprestimoDevolucaos.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    EmprestimoDevolucao VarEmprestimoDevolucao;
    while (LerEmprestimoDevolucao(fp, &VarEmprestimoDevolucao) == 5) {
        ImprimirEmprestimoDevolucao(VarEmprestimoDevolucao);
    }

    fclose(fp);
}

// 02.03 - Editar um cadastro de EmprestimoDevolucao
void EditarCadastroEmprestimoDevolucao(){
	int IdEmprestimoDevolucaoEditar;
    printf("Digite o ID do EmprestimoDevolucao a ser editado: ");
    scanf("%d", &IdEmprestimoDevolucaoEditar);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("EmprestimoDevolucaos.txt", "r");
    FILE *fpNew = fopen("EmprestimoDevolucaos_tmp.txt", "w");

    EmprestimoDevolucao VarEmprestimoDevolucao;
    while (LerEmprestimoDevolucao(fpOld, &VarEmprestimoDevolucao) == 5) {
        if (VarEmprestimoDevolucao.IdEmprestimoDevolucao == IdEmprestimoDevolucaoEditar) {
        	
			int temp;
			system("cls");
			printf("Digite '1' para Emprestimo ou '2' para Devolucao: ");
		    scanf("%1d", &temp);
		    if(temp == 1){
		        strcpy(VarEmprestimoDevolucao.NomeEmprestimoDevolucao, "EMPRESTIMO");
		    } else if(temp == 2){
		        strcpy(VarEmprestimoDevolucao.NomeEmprestimoDevolucao, "DEVOLUCAO ");
		    } else {
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
		    
		    printf("+--------+------------------------------------------------------+\n");
			printf("|   ID   |                  NOME DO AFILIADO                    |\n");
			printf("+--------+------------------------------------------------------+\n");    
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

    remove("EmprestimoDevolucaos.txt");
    rename("EmprestimoDevolucaos_tmp.txt", "EmprestimoDevolucaos.txt");

    printf("Cadastro editado com sucesso!\n");
}

// 02.04 - Excluir um cadastro de EmprestimoDevolucao
void ExcluirCadastroEmprestimoDevolucao(){
	int IdEmprestimoDevolucaoExcluir;
    printf("Digite o ID do EmprestimoDevolucao a ser excluído: ");
    scanf("%d", &IdEmprestimoDevolucaoExcluir);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("EmprestimoDevolucaos.txt", "r");
    FILE *fpNew = fopen("EmprestimoDevolucaos_tmp.txt", "w");

    EmprestimoDevolucao VarEmprestimoDevolucao;
    while (LerEmprestimoDevolucao(fpOld, &VarEmprestimoDevolucao) == 5) {
        if (VarEmprestimoDevolucao.IdEmprestimoDevolucao != IdEmprestimoDevolucaoExcluir) {
            EscreverEmprestimoDevolucao(fpNew, VarEmprestimoDevolucao);
        }
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("EmprestimoDevolucaos.txt");
    rename("EmprestimoDevolucaos_tmp.txt", "EmprestimoDevolucaos.txt");

    printf("Cadastro excluído com sucesso!\n");
}

// 02 - Função para chamar Menu Cadastro EmprestimoDevolucao
void MenuCadastroEmprestimoDevolucao(){
    int OpMenuCadastroEmprestimoDevolucao;
    do {
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
        getchar(); // Consume o caractere de nova linha
        
        switch (OpMenuCadastroEmprestimoDevolucao) {
            case 1: {
            	system("cls");
            	CadastrarNovoEmprestimoDevolucao();
            	system("pause");
                system("cls");
                break;
            }
            case 2: {
            	system("cls");
            	printf("+--------+------------------+-----------------+--------+--------+\n");
				printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
				printf("+--------+------------------+-----------------+--------+--------+\n");
                MostrarTodosEmprestimoDevolucaos();
                system("pause");
                system("cls");
                break;
            }
            case 3: {
            	system("cls");
            	printf("+--------+------------------+-----------------+--------+--------+\n");
				printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
				printf("+--------+------------------+-----------------+--------+--------+\n");
				MostrarTodosEmprestimoDevolucaos();
                EditarCadastroEmprestimoDevolucao();
                system("pause");
                system("cls");
                break;
            }
            case 4: {
            	system("cls");
            	printf("+--------+------------------+-----------------+--------+--------+\n");
				printf("|   ID   |    EMP OU DEV    |       DATA      | ID AFI | ID LIV |\n");
				printf("+--------+------------------+-----------------+--------+--------+\n");
				MostrarTodosEmprestimoDevolucaos();
                ExcluirCadastroEmprestimoDevolucao();
                system("pause");
                system("cls");
                break;
            }
            case 5: {
				system("cls");
				break;
			}
        }
    } while (OpMenuCadastroEmprestimoDevolucao != 5);
}






// 02 - Estrutura para representar um Inventario
typedef struct {
    int IdInventario;
    int IdInventarioLivro;
    char NomeLivroInventario[50];
    int IdInventarioCategoria;
    int IdInventarioStatus;
    
} Inventario;

// 02 - Função para criar um Inventario
Inventario CriarInventario(int IdInventario, int IdInventarioLivro, char* NomeLivroInventario, int IdInventarioCategoria, int IdInventarioStatus) {
    Inventario VarInventario;
    VarInventario.IdInventario = IdInventario;
    VarInventario.IdInventarioLivro = IdInventarioLivro;
    strcpy(VarInventario.NomeLivroInventario, NomeLivroInventario);
    VarInventario.IdInventarioCategoria = IdInventarioCategoria;
    VarInventario.IdInventarioStatus = IdInventarioStatus;
    return VarInventario;
}

// 02 - Função para imprimir um Inventario
void ImprimirInventario(Inventario VarInventario) {
    printf("|  %04d  |  %04d  |  %-50s  |  %04d  |  %04d  |\n", VarInventario.IdInventario, VarInventario.IdInventarioLivro, VarInventario.NomeLivroInventario, VarInventario.IdInventarioCategoria, VarInventario.IdInventarioStatus);
    printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
}

// 02 - Função para escrever um Inventario em um arquivo
void EscreverInventario(FILE* fp, Inventario VarInventario) {
    fprintf(fp, "%d;%d;%s;%d;%d\n", VarInventario.IdInventario, VarInventario.IdInventarioLivro, VarInventario.NomeLivroInventario, VarInventario.IdInventarioCategoria, VarInventario.IdInventarioStatus);
}

// 02 - Função para ler um Inventario de um arquivo
int LerInventario(FILE* fp, Inventario* VarInventario) {
    return fscanf(fp, "%d;%d;%49[^;];%d;%d\n", &VarInventario->IdInventario, &VarInventario->IdInventarioLivro, VarInventario->NomeLivroInventario, &VarInventario->IdInventarioCategoria, &VarInventario->IdInventarioStatus);
}

// 02 - Função para obter o maior ID de Inventario
int ObterMaiorIdInventario() {
    FILE *fp = fopen("Inventarios.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    int MaiorIdInventario = 0;
    Inventario VarInventario;
    while (LerInventario(fp, &VarInventario) == 5) {
        if (VarInventario.IdInventario > MaiorIdInventario) {
            MaiorIdInventario = VarInventario.IdInventario;
        }
    }

    fclose(fp);

    return MaiorIdInventario;
}


// 02.01 - Cadastrar novo Inventario
void CadastrarNovoInventario(){
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
	
	FILE *fp = fopen("Livros.txt", "r");
    Livro VarLivro;
    while (LerLivro(fp, &VarLivro) == 2) {
        if (VarLivro.IdLivro == IdInventarioLivroCadastrar) {
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

    FILE *fp2 = fopen("Inventarios.txt", "a");
    EscreverInventario(fp2, VarInventario);
    fclose(fp2);

    printf("Inventario cadastrado com sucesso!\n");
}

// 02.02 - Mostrar todos os Inventarios
void MostrarTodosInventarios(){
	FILE *fp = fopen("Inventarios.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    Inventario VarInventario;
    while (LerInventario(fp, &VarInventario) == 5) {
        ImprimirInventario(VarInventario);
    }

    fclose(fp);
}

// 02.03 - Editar um cadastro de Inventario
void EditarCadastroInventario(){
/*	int IdInventarioEditar;
    printf("Digite o ID do Inventario a ser editado: ");
    scanf("%d", &IdInventarioEditar);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("Inventarios.txt", "r");
    FILE *fpNew = fopen("Inventarios_tmp.txt", "w");

    Inventario VarInventario;
    while (LerInventario(fpOld, &VarInventario) == 5) {
        if (VarInventario.IdInventario == IdInventarioEditar) {
        	
			int temp;
			printf("Digite '1' para Emprestimo ou '2' para Devolucao: ");
		    scanf("%1d", &temp);
		    if(temp == 1){
		        strcpy(VarInventario.NomeInventario, "EMPRESTIMO");
		    } else if(temp == 2){
		        strcpy(VarInventario.NomeInventario, "DEVOLUCAO ");
		    } else {
		        strcpy(VarInventario.NomeInventario, "vazio     ");
		    }
		    printf("Digite o Data: ");
		    scanf("%s", VarInventario.DataInventario);
		    printf("Digite o Id do Afiliado: ");
		    scanf("%d", &VarInventario.IdInventarioAfiliado);
			printf("Digite o Id do Livro: ");
		    scanf("%d", &VarInventario.IdInventarioLivro);
		}
        EscreverInventario(fpNew, VarInventario);
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("Inventarios.txt");
    rename("Inventarios_tmp.txt", "Inventarios.txt");

    printf("Cadastro editado com sucesso!\n");
*/}

// 02.04 - Excluir um cadastro de Inventario
void ExcluirCadastroInventario(){
	int IdInventarioExcluir;
    printf("Digite o ID do Inventario a ser excluído: ");
    scanf("%d", &IdInventarioExcluir);
    getchar(); // Consume o caractere de nova linha

    FILE *fpOld = fopen("Inventarios.txt", "r");
    FILE *fpNew = fopen("Inventarios_tmp.txt", "w");

    Inventario VarInventario;
    while (LerInventario(fpOld, &VarInventario) == 5) {
        if (VarInventario.IdInventario != IdInventarioExcluir) {
            EscreverInventario(fpNew, VarInventario);
        }
    }

    fclose(fpOld);
    fclose(fpNew);

    remove("Inventarios.txt");
    rename("Inventarios_tmp.txt", "Inventarios.txt");

    printf("Cadastro excluído com sucesso!\n");
}

// 02 - Função para chamar Menu Cadastro Inventario
void MenuCadastroInventario(){
    int OpMenuCadastroInventario;
    do {
		printf("+---------------------------------------------------------------+\n");
    	printf("|                      MENU DE INVENTARIO                       |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 1-NOVO INVENTARIO             | 2-MOSTRAR TODAS OS INVENTARIOS|\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 3-EDITAR UM INVENTARIO        | 4-EXCLUIR UM INVENTARIO       |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("|                  5-VOLTAR PARA MENU PRINCIPAL                 |\n");
		printf("+-------------------------------+-------------------------------+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &OpMenuCadastroInventario);
        getchar(); // Consume o caractere de nova linha
        
        switch (OpMenuCadastroInventario) {
            case 1: {
            	system("cls");
            	CadastrarNovoInventario();
            	system("pause");
                system("cls");
                break;
            }
            case 2: {
            	system("cls");
            	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
				printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
				printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
                MostrarTodosInventarios();
                system("pause");
                system("cls");
                break;
            }
            case 3: {
            	system("cls");
            	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
				printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
				printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
				MostrarTodosInventarios();
                EditarCadastroInventario();
                system("pause");
                system("cls");
                break;
            }
            case 4: {
            	system("cls");
            	printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
				printf("|   ID   | ID LIV |                        LIVRO                         | ID CAT | ID STS |\n");
				printf("+--------+--------+------------------------------------------------------+--------+--------+\n");
				MostrarTodosInventarios();
                ExcluirCadastroInventario();
                system("pause");
                system("cls");
                break;
            }
            case 5: {
				system("cls");
				break;
			}
        }
    } while (OpMenuCadastroInventario != 5);
}








// 00 - Função para chamar Menu Cadastro
void MenuCadastro(){system("cls");
    int OpMenuCadastro;
    do {
    	printf("+---------------------------------------------------------------+\n");
    	printf("|                       MENU DE CADASTRO                        |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 1-AFILIADO                    | 2-LIVRO                       |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 3-STATUS LIVRO                | 4-CATEGORIA LIVRO             |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("|                  5-VOLTAR PARA MENU PRINCIPAL                 |\n");
		printf("+-------------------------------+-------------------------------+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &OpMenuCadastro);
        getchar(); // Consume o caractere de nova linha
        
        switch (OpMenuCadastro) {
            case 1: {
            	system("cls");
            	MenuCadastroAfiliado();
                break;
            }
            case 2: {
				system("cls");
                MenuCadastroLivro();
                break;
            }
            case 3: {
            	system("cls");
            	MenuCadastroStatusLivro();
                break;
            }
            case 4: {
            	system("cls");
            	MenuCadastroCategoriaLivro();
                break;
            }
            case 5: {
				system("cls");
				break;
			}
        }
    } while (OpMenuCadastro != 5);
}







int main() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	int OpMenu;
    do {
    	printf("+---------------------------------------------------------------+\n");
    	printf("|                         MENU PRINCIPAL                        |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 1-CADASTRO                    | 2-EMPRESTIMOS E DEVOLUCOES    |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("| 3-INVENTARIO                  | 4-IMPRESSAO                   |\n");
    	printf("+-------------------------------+-------------------------------+\n");
    	printf("|                            5-SAIR                             |\n");
		printf("+-------------------------------+-------------------------------+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &OpMenu);
        getchar(); // Consume o caractere de nova linha
        
        switch (OpMenu) {
            case 1: {
            	system("cls");
            	MenuCadastro();
                break;
            }
            case 2: {
				system("cls");
                MenuCadastroEmprestimoDevolucao();
                break;
            }
            case 3: {
            	system("cls");
            	MenuCadastroInventario();
                break;
            }
            case 4: {
            	system("cls");
            	printf("Ainda em desenvolvimento!\n");
            	system("pause");
                break;
            }
            case 5: {
				system("cls");
				break;
			}
        }
    } while (OpMenu != 5);
	
	

    return 0;
}