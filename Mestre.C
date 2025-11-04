#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Estrutura do item
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Enum para critério de ordenação
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} Criterio;

// Funções auxiliares
void adicionarItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarSequencial(Item mochila[], int total);
void ordenarItens(Item mochila[], int total, Criterio criterio);
int compararItens(Item a, Item b, Criterio criterio);
void buscaBinaria(Item mochila[], int total, char nome[], bool ordenada);

// Programa principal
int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;
    bool ordenadaPorNome = false; // controle de estado da ordenação

    do {
        printf("\n=== MOCHILA DE SOBREVIVENCIA - NIVEL MESTRE ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar mochila\n");
        printf("5 - Buscar item por nome (busca binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &totalItens);
                ordenadaPorNome = false; // nova inserção invalida a ordenação
                break;

            case 2:
                removerItem(mochila, &totalItens);
                ordenadaPorNome = false;
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 4: {
                if (totalItens == 0) {
                    printf("📭 Nenhum item para ordenar.\n");
                    break;
                }

                int escolha;
                printf("\n--- Escolha o criterio de ordenacao ---\n");
                printf("1 - Nome\n2 - Tipo\n3 - Prioridade\n");
                printf("Opcao: ");
                scanf("%d", &escolha);
                getchar();

                if (escolha < 1 || escolha > 3) {
                    printf("❌ Criterio invalido!\n");
                    break;
                }

                ordenarItens(mochila, totalItens, (Criterio)escolha);
                ordenadaPorNome = (escolha == ORDENAR_NOME);
                break;
            }

            case 5: {
                if (totalItens == 0) {
                    printf("📭 Mochila vazia.\n");
                    break;
                }

                if (!ordenadaPorNome) {
                    printf("⚠️ A mochila precisa estar ordenada por nome antes da busca binaria!\n");
                    break;
                }

                char nomeBusca[50];
                printf("\nDigite o nome do item para buscar: ");
                fgets(nomeBusca, 50, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                buscaBinaria(mochila, totalItens, nomeBusca, ordenadaPorNome);
                break;
            }

            case 0:
                printf("\nEncerrando o programa... 🏝️\n");
                break;

            default:
                printf("❗ Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// ------------------------ IMPLEMENTAÇÕES ------------------------

void adicionarItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("⚠️ Mochila cheia! (máx. %d itens)\n", MAX_ITENS);
        return;
    }

    printf("\n--- Adicionar Item ---\n");
    printf("Nome: ");
    fgets(mochila[*total].nome, 50, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[*total].tipo, 30, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    getchar();

    do {
        printf("Prioridade (1 a 5): ");
        scanf("%d", &mochila[*total].prioridade);
        getchar();
    } while (mochila[*total].prioridade < 1 || mochila[*total].prioridade > 5);

    (*total)++;
    printf("✅ Item adicionado com sucesso!\n");
}

void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("⚠️ Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[50];
    printf("\nDigite o nome do item para remover: ");
    fgets(nomeRemover, 50, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("🗑️ Item removido com sucesso!\n");
            return;
        }
    }

    printf("❌ Item nao encontrado!\n");
}

void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\n📭 Mochila vazia.\n");
        return;
    }

    printf("\n--- Itens na Mochila ---\n");
    printf("%-20s %-15s %-12s %-10s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-20s %-15s %-12d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

int compararItens(Item a, Item b, Criterio criterio) {
    switch (criterio) {
        case ORDENAR_NOME:
            return strcmp(a.nome, b.nome);
        case ORDENAR_TIPO:
            return strcmp(a.tipo, b.tipo);
        case ORDENAR_PRIORIDADE:
            return a.prioridade - b.prioridade;
        default:
            return 0;
    }
}

void ordenarItens(Item mochila[], int total, Criterio criterio) {
    int comparacoes = 0;

    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0 && compararItens(mochila[j], chave, criterio) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }
        mochila[j + 1] = chave;
    }

    printf("\n✅ Mochila ordenada com sucesso!\n");
    printf("🔢 Total de comparacoes: %d\n", comparacoes);
}

void buscaBinaria(Item mochila[], int total, char nome[], bool ordenada) {
    if (!ordenada) {
        printf("⚠️ Lista não está ordenada por nome!\n");
        return;
    }

    int inicio = 0, fim = total - 1, meio;
    bool encontrado = false;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) {
            printf("\n🔍 Item encontrado!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            encontrado = true;
            break;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nome);
    }
}
