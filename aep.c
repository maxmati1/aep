#include <stdio.h>
#include <string.h>

void criptografar(char senha[]) {
    int i = 0;
    while (senha[i] != '\0') {
        senha[i] = ((senha[i] + (i + 1) * 3) % 94) + 33; 
        i++;
    }
}

void salvar(char nomes[][50], char senhas[][20], int total) {
    FILE *arq = fopen("usuarios.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }
    int i;
    for (i = 0; i < total; i++) {
        fprintf(arq, "%s; %s\n", nomes[i], senhas[i]);
    }
    fclose(arq);
}

int carregar(char nomes[][50], char senhas[][20]) {
    FILE *arq = fopen("usuarios.txt", "r");
    int total = 0;
    if (arq != NULL) {
        while (fscanf(arq, "%49s %19s", nomes[total], senhas[total]) == 2) {
            total++;
        }
        fclose(arq);
    }
    return total;
}

int main() {
    char nomes[100][50];
    char senhas[100][20];
    int total = carregar(nomes, senhas);
    int opcao, i;

    do {
        printf("\n--- Sistema de Gerenciamento de Usuarios ---\n");
        printf("1. Incluir novo usuario\n");
        printf("2. Alterar usuario\n");
        printf("3. Excluir usuario\n");
        printf("4. Listar usuarios\n");
        printf("0. Sair\n");

        while (1) {
            printf("Escolha uma opcao: ");
            if (scanf("%d", &opcao) == 1) {
                break;
            }
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n');
        }

        if (opcao == 1) {
            if (total >= 100) {
                printf("Limite de usuarios atingido.\n");
            } else {
                printf("Digite o nome do usuario: ");
                scanf(" %49[^\n]", nomes[total]);
                printf("Digite a senha: ");
                scanf(" %19s", senhas[total]);
                criptografar(senhas[total]);
                total++;
                printf("Usuario incluido com sucesso. Seu ID e %d\n", total);
                salvar(nomes, senhas, total);
            }
        } else if (opcao == 2) {
            int id;
            printf("Digite o ID do usuario a alterar: ");
            scanf("%d", &id);
            if (id < 1 || id > total) {
                printf("Usuario nao encontrado.\n");
            } else {
                printf("Digite o novo nome: ");
                scanf(" %49[^\n]", nomes[id - 1]);
                printf("Digite a nova senha: ");
                scanf(" %19s", senhas[id - 1]);
                criptografar(senhas[id - 1]);
                printf("Usuario alterado com sucesso.\n");
                salvar(nomes, senhas, total);
            }
        } else if (opcao == 3) {
            int id;
            printf("Digite o ID do usuario a excluir: ");
            scanf("%d", &id);
            if (id < 1 || id > total) {
                printf("Usuario nao encontrado.\n");
            } else {
                for (i = id - 1; i < total - 1; i++) {
                    strcpy(nomes[i], nomes[i + 1]);
                    strcpy(senhas[i], senhas[i + 1]);
                }
                total--;
                printf("Usuario excluido com sucesso.\n");
                salvar(nomes, senhas, total);
            }
        } else if (opcao == 4) {
            if (total == 0) {
                printf("Nenhum usuario cadastrado.\n");
            } else {
                for (i = 0; i < total; i++) {
                    printf("ID: %d, Nome: %s, Senha criptografada: %s\n", i + 1, nomes[i], senhas[i]);
                }
            }
        } else if (opcao != 0) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    printf("Encerrando o programa.\n");
    return 0;
}

