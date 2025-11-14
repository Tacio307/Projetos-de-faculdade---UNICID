#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ====================================================
// Estrutura do Produto
// ====================================================
typedef struct {
    int id;
    char nome[50];
    char categoria[30];
    float preco;
    int quantidade;
    char fornecedor[50];
} Produto;

// ====================================================
// Funções utilitárias
// ====================================================

// Remove '\n'
void trim(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Converte para minúsculas
void toLower(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

// ====================================================
// Carregar produtos
// ====================================================
int carregarProdutos(Produto **lista) {
    FILE *fp = fopen("produtos.txt", "r");
    if (!fp) return 0;

    Produto temp;
    int count = 0;

    while (fscanf(fp, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]\n",
                  &temp.id, temp.nome, temp.categoria,
                  &temp.preco, &temp.quantidade, temp.fornecedor) == 6) {
        *lista = realloc(*lista, (count + 1) * sizeof(Produto));
        (*lista)[count++] = temp;
    }
    fclose(fp);
    return count;
}

// ====================================================
// Salvar produtos
// ====================================================
void salvarProdutos(Produto *lista, int n) {
    FILE *fp = fopen("produtos.txt", "w");
    if (!fp) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d;%s;%s;%.2f;%d;%s\n",
                lista[i].id, lista[i].nome, lista[i].categoria,
                lista[i].preco, lista[i].quantidade, lista[i].fornecedor);
    }

    fclose(fp);
}

// ====================================================
// Geração automática de ID
// ====================================================
int gerarID(Produto *lista, int n) {
    int max = 0;
    for (int i = 0; i < n; i++)
        if (lista[i].id > max)
            max = lista[i].id;
    return max + 1;
}

// ====================================================
// Verifica duplicado
// ====================================================
int nomeDuplicado(Produto *lista, int n, const char *nome) {
    char nomeA[50], nomeB[50];
    strcpy(nomeA, nome);
    toLower(nomeA);

    for (int i = 0; i < n; i++) {
        strcpy(nomeB, lista[i].nome);
        toLower(nomeB);
        if (strcmp(nomeA, nomeB) == 0)
            return 1;
    }
    return 0;
}

// ====================================================
// Inserir produto (CORRIGIDO PREÇO COM VÍRGULA)
// ====================================================
int inserirProduto(Produto **lista, int n) {
    Produto novo;

    printf("Nome do produto: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    trim(novo.nome);

    if (nomeDuplicado(*lista, n, novo.nome)) {
        printf("Erro: Produto já cadastrado!\n");
        return n;
    }

    printf("Categoria: ");
    fgets(novo.categoria, sizeof(novo.categoria), stdin);
    trim(novo.categoria);

    // ----------- CORREÇÃO DO PREÇO -----------
    printf("Preço (R$): ");
    char precoStr[20];
    fgets(precoStr, sizeof(precoStr), stdin);
    trim(precoStr);

    for (int i = 0; precoStr[i]; i++)
        if (precoStr[i] == ',')
            precoStr[i] = '.';

    novo.preco = atof(precoStr);
    // -----------------------------------------

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    printf("Fornecedor: ");
    fgets(novo.fornecedor, sizeof(novo.fornecedor), stdin);
    trim(novo.fornecedor);

    novo.id = gerarID(*lista, n);

    *lista = realloc(*lista, (n + 1) * sizeof(Produto));
    (*lista)[n] = novo;

    salvarProdutos(*lista, n + 1);

    printf("Produto cadastrado com sucesso! ID: %d\n", novo.id);
    return n + 1;
}

// ====================================================
// Listar produtos
// ====================================================
void listarProdutos(Produto *lista, int n) {
    printf("\n-------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-15s | %-8s | %-10s | %-15s |\n",
           "ID", "Produto", "Categoria", "Preço", "Qtd", "Fornecedor");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("| %-3d | %-20s | %-15s | R$ %-6.2f | %-10d | %-15s |\n",
               lista[i].id, lista[i].nome, lista[i].categoria,
               lista[i].preco, lista[i].quantidade, lista[i].fornecedor);
    }
    printf("-------------------------------------------------------------------------------\n");
}

// ====================================================
// Buscar por nome
// ====================================================
void buscarPorNome(Produto *lista, int n) {
    char busca[50], temp[50];
    printf("Digite o nome: ");
    fgets(busca, sizeof(busca), stdin);
    trim(busca);
    toLower(busca);

    for (int i = 0; i < n; i++) {
        strcpy(temp, lista[i].nome);
        toLower(temp);
        if (strstr(temp, busca))
            printf("%d - %s (R$ %.2f)\n", lista[i].id, lista[i].nome, lista[i].preco);
    }
}

// ====================================================
// Buscar por categoria
// ====================================================
void buscarPorCategoria(Produto *lista, int n) {
    char busca[30], temp[30];
    printf("Categoria: ");
    fgets(busca, sizeof(busca), stdin);
    trim(busca);
    toLower(busca);

    for (int i = 0; i < n; i++) {
        strcpy(temp, lista[i].categoria);
        toLower(temp);
        if (strstr(temp, busca))
            printf("%d - %s (%s)\n", lista[i].id, lista[i].nome, lista[i].categoria);
    }
}

// ====================================================
// Alterar produto (CORRIGIDO PREÇO COM VÍRGULA)
// ====================================================
void alterarProduto(Produto *lista, int n) {
    int id;
    printf("ID do produto para alterar: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < n; i++) {
        if (lista[i].id == id) {

            printf("Novo nome: ");
            fgets(lista[i].nome, sizeof(lista[i].nome), stdin);
            trim(lista[i].nome);

            printf("Nova categoria: ");
            fgets(lista[i].categoria, sizeof(lista[i].categoria), stdin);
            trim(lista[i].categoria);

            // ----------- CORREÇÃO DO PREÇO -----------
            printf("Novo preço: ");
            char precoStr[20];
            fgets(precoStr, sizeof(precoStr), stdin);
            trim(precoStr);

            for (int j = 0; precoStr[j]; j++)
                if (precoStr[j] == ',')
                    precoStr[j] = '.';

            lista[i].preco = atof(precoStr);
            // -----------------------------------------

            printf("Nova quantidade: ");
            scanf("%d", &lista[i].quantidade);
            getchar();

            printf("Novo fornecedor: ");
            fgets(lista[i].fornecedor, sizeof(lista[i].fornecedor), stdin);
            trim(lista[i].fornecedor);

            salvarProdutos(lista, n);

            printf("Produto alterado com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

// ====================================================
// Excluir produto
// ====================================================
int excluirProduto(Produto *lista, int n) {
    int id;
    printf("ID para excluir: ");
    scanf("%d", &id);
    getchar();

    int pos = -1;
    for (int i = 0; i < n; i++)
        if (lista[i].id == id)
            pos = i;

    if (pos == -1) {
        printf("Produto não encontrado!\n");
        return n;
    }

    for (int i = pos; i < n - 1; i++)
        lista[i] = lista[i + 1];

    salvarProdutos(lista, n - 1);
    printf("Produto excluído!\n");

    return n - 1;
}

// ====================================================
// Ordenações
// ====================================================
void ordenarPorNome(Produto *lista, int n, int crescente) {
    Produto temp;

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            int cmp = strcasecmp(lista[j].nome, lista[j + 1].nome);
            if ((crescente && cmp > 0) || (!crescente && cmp < 0)) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    listarProdutos(lista, n);
}

void ordenarPorPreco(Produto *lista, int n, int crescente) {
    Produto temp;

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            if ((crescente && lista[j].preco > lista[j + 1].preco) ||
                (!crescente && lista[j].preco < lista[j + 1].preco)) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    listarProdutos(lista, n);
}

// ====================================================
// Main
// ====================================================
int main() {
    Produto *lista = NULL;
    int n = carregarProdutos(&lista);
    int opcao;

    do {
        printf("\n=========== CADASTRO DE LOJA ===========\n");
        printf("1. Inserir produto\n");
        printf("2. Listar produtos\n");
        printf("3. Buscar por nome\n");
        printf("4. Buscar por categoria\n");
        printf("5. Alterar produto\n");
        printf("6. Excluir produto\n");
        printf("7. Ordenar por nome (A–Z)\n");
        printf("8. Ordenar por nome (Z–A)\n");
        printf("9. Ordenar por preço (menor→maior)\n");
        printf("10. Ordenar por preço (maior→menor)\n");
        printf("0. Sair\n");
        printf("=========================================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: n = inserirProduto(&lista, n); break;
            case 2: listarProdutos(lista, n); break;
            case 3: buscarPorNome(lista, n); break;
            case 4: buscarPorCategoria(lista, n); break;
            case 5: alterarProduto(lista, n); break;
            case 6: n = excluirProduto(lista, n); break;
            case 7: ordenarPorNome(lista, n, 1); break;
            case 8: ordenarPorNome(lista, n, 0); break;
            case 9: ordenarPorPreco(lista, n, 1); break;
            case 10: ordenarPorPreco(lista, n, 0); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    free(lista);
    return 0;
}
