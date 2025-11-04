#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura do item
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n=== MOCHILA DE SOBREVIVENCIA ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n"); // 🆕 nova opção
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1: // Adicionar item
                if (totalItens < MAX_ITENS) {
                    printf("\n--- Adicionar Item ---\n");
                    printf("Nome do item: ");
                    fgets(mochila[totalItens].nome, 50, stdin);
                    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';

                    printf("Tipo do item: ");
                    fgets(mochila[totalItens].tipo, 30, stdin);
                    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';

                    printf("Quantidade: ");
                    scanf("%d", &mochila[totalItens].quantidade);
                    getchar();

                    totalItens++;
                    printf("✅ Item adicionado com sucesso!\n");
                } else {
                    printf("⚠️ Mochila cheia! (máx. %d itens)\n", MAX_ITENS);
                }
                break;

            case 2: { // Remover item
                if (totalItens == 0) {
                    printf("⚠️ Nenhum item para remover.\n");
                    break;
                }

                char nomeRemover[50];
                printf("\n--- Remover Item ---\n");
                printf("Digite o nome do item a remover: ");
                fgets(nomeRemover, 50, stdin);
                nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

                int encontrado = 0;
                for (int i = 0; i < totalItens; i++) {
                    if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                        for (int j = i; j < totalItens - 1; j++) {
                            mochila[j] = mochila[j + 1];
                        }
                        totalItens--;
                        encontrado = 1;
                        printf("🗑️ Item removido com sucesso!\n");
                        break;
                    }
                }

                if (!encontrado) {
                    printf("❌ Item não encontrado!\n");
                }
                break;
            }

            case 3: // Listar itens
                if (totalItens == 0) {
                    printf("\n📭 Mochila vazia.\n");
                } else {
                    printf("\n--- Itens na Mochila ---\n");
                    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
                    printf("---------------------------------------------\n");
                    for (int i = 0; i < totalItens; i++) {
                        printf("%-20s %-15s %-10d\n",
                               mochila[i].nome,
                               mochila[i].tipo,
                               mochila[i].quantidade);
                    }
                }
                break;

            case 4: { // 🆕 Buscar item por nome
                if (totalItens == 0) {
                    printf("📭 Mochila vazia. Nenhum item para buscar.\n");
                    break;
                }

                char nomeBusca[50];
                printf("\n--- Buscar Item ---\n");
                printf("Digite o nome do item a buscar: ");
                fgets(nomeBusca, 50, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                int encontrado = 0;
                for (int i = 0; i < totalItens; i++) {
                    if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                        printf("\n🔍 Item encontrado!\n");
                        printf("Nome: %s\n", mochila[i].nome);
                        printf("Tipo: %s\n", mochila[i].tipo);
                        printf("Quantidade: %d\n", mochila[i].quantidade);
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
                }
                break;
            }

            case 0:
                printf("\nSaindo do programa... 🏝️\n");
                break;

            default:
                printf("❗ Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
