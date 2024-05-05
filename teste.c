#include <stdio.h>
#include <string.h>

// Estrutura para representar um estudante
typedef struct {
    int IdEstudante;
    char NomeEstudante[50];
} Estudante;

// Função para criar um estudante
Estudante criarEstudante(int IdEstudante, char* NomeEstudante) {
    Estudante e;
    e.IdEstudante = IdEstudante;
    strcpy(e.NomeEstudante, NomeEstudante);
    return e;
}

// Função para imprimir um estudante
void imprimirEstudante(Estudante e) {
    printf("%d %s\n", e.IdEstudante, e.NomeEstudante);
}

// Função para escrever um estudante em um arquivo
void escreverEstudante(FILE* fp, Estudante e) {
    fprintf(fp, "%d %s\n", e.IdEstudante, e.NomeEstudante);
}

// Função para ler um estudante de um arquivo
Estudante lerEstudante(FILE* fp) {
    Estudante e;
    fscanf(fp, "%d %s\n", &e.IdEstudante, e.NomeEstudante);
    return e;
}

// Função para obter o maior ID de estudante
int obterMaiorId() {
    FILE *fp = fopen("estudantes.txt", "r");
    if (fp == NULL) {
        return 0;
    }

    int maiorId = 0;
    while (!feof(fp)) {
        Estudante e = lerEstudante(fp);
        if (e.IdEstudante > maiorId) {
            maiorId = e.IdEstudante;
        }
    }

    fclose(fp);

    return maiorId;
}

int main() {
    int opcao;
    do {
        printf("1. Cadastrar novo estudante\n");
        printf("2. Mostrar todos os estudantes\n");
        printf("3. Editar um cadastro\n");
        printf("4. Excluir um cadastro\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // Cadastrar novo aluno
                char NomeEstudanteCadastrar[50];
                printf("Digite o nome do estudante: ");
                scanf("%s", NomeEstudanteCadastrar);

                int IdEstudanteCadastrar = obterMaiorId() + 1;

                Estudante e = criarEstudante(IdEstudanteCadastrar, NomeEstudanteCadastrar);

                FILE *fp = fopen("estudantes.txt", "a");
                escreverEstudante(fp, e);
                fclose(fp);

                printf("Estudante cadastrado com sucesso!\n");
                break;
            }
            case 2: {
                // Mostrar todos os alunos
                FILE *fp = fopen("estudantes.txt", "r");
                if (fp == NULL) {
                    printf("Erro ao abrir o arquivo!\n");
                    return 1;
                }

                while (!feof(fp)) {
                    Estudante e = lerEstudante(fp);
                    imprimirEstudante(e);
                }

                fclose(fp);
                break;
            }
            case 3: {
                // Editar um cadastro
                int IdEstudanteEditar;
                printf("Digite o ID do estudante a ser editado: ");
                scanf("%d", &IdEstudanteEditar);

                FILE *fpOld = fopen("estudantes.txt", "r");
                FILE *fpNew = fopen("estudantes_tmp.txt", "w");

                while (!feof(fpOld)) {
                    Estudante e = lerEstudante(fpOld);
                    if (e.IdEstudante == IdEstudanteEditar) {
                        printf("Digite o novo nome do estudante: ");
                        scanf("%s", e.NomeEstudante);
                    }
                    escreverEstudante(fpNew, e);
                }

                fclose(fpOld);
                fclose(fpNew);

                remove("estudantes.txt");
                rename("estudantes_tmp.txt", "estudantes.txt");

                printf("Cadastro editado com sucesso!\n");
                break;
            }
            case 4: {
                // Excluir um cadastro
                int IdEstudanteExcluir;
                printf("Digite o ID do estudante a ser excluído: ");
                scanf("%d", &IdEstudanteExcluir);

                FILE *fpOld = fopen("estudantes.txt", "r");
                FILE *fpNew = fopen("estudantes_tmp.txt", "w");

                while (!feof(fpOld)) {
                    Estudante e = lerEstudante(fpOld);
                    if (e.IdEstudante != IdEstudanteExcluir) {
                        escreverEstudante(fpNew, e);
                    }
                }

                fclose(fpOld);
                fclose(fpNew);

                remove("estudantes.txt");
                rename("estudantes_tmp.txt", "estudantes.txt");

                printf("Cadastro excluído com sucesso!\n");
                break;
            }
        }
    } while (opcao != 5);

    return 0;
}
