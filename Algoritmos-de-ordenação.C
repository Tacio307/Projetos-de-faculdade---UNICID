#include <stdio.h>   // Inclui a biblioteca padrão de Entrada/Saída (para printf, scanf, operações de arquivo).
#include <stdlib.h>  // Inclui a biblioteca de utilidades gerais (para funções como rand, srand, exit).
#include <string.h>  // Inclui a biblioteca para manipulação de strings (embora pouco usada aqui).
#include <time.h>    // Inclui a biblioteca para funções de tempo (usada para gerar números aleatórios diferentes).

// --- Definições de Constantes ---
#define MAX 100               // Define o tamanho máximo do vetor (array) de inteiros na memória.
#define ARQ_ORIGINAL "dados.txt"  // Nome do arquivo para os dados não ordenados.
#define ARQ_ORDENADO "ordenado.txt" // Nome do arquivo para os dados ordenados.

// -------------------- Funções de ordenação --------------------

/**
 * @brief Ordena o vetor usando o algoritmo Bubble Sort.
 * * O Bubble Sort compara elementos adjacentes e os troca se estiverem fora de ordem.
 * Repete o processo até que a lista esteja totalmente ordenada.
 *
 * @param v O vetor de inteiros a ser ordenado.
 * @param n O número de elementos no vetor.
 */
void bubbleSort(int v[], int n) {
    // Loop externo: controla quantas passagens completas serão feitas.
    for (int i = 0; i < n - 1; i++)
        // Loop interno: faz as comparações e trocas em cada passagem.
        for (int j = 0; j < n - i - 1; j++)
            // Se o elemento atual for maior que o próximo (ordem errada)...
            if (v[j] > v[j + 1]) {
                // ... realiza a troca (swap).
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
}

/**
 * @brief Ordena o vetor usando o algoritmo Insertion Sort.
 * * O Insertion Sort insere cada elemento em sua posição correta
 * dentro da sub-lista já ordenada à sua esquerda.
 *
 * @param v O vetor de inteiros a ser ordenado.
 * @param n O número de elementos no vetor.
 */
void insertionSort(int v[], int n) {
    // Começa do segundo elemento (índice 1).
    for (int i = 1; i < n; i++) {
        int key = v[i]; // 'key' é o elemento a ser inserido.
        int j = i - 1;
        
        // Move os elementos da sub-lista ordenada que são maiores que 'key'
        // uma posição à frente do seu local atual.
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j--;
        }
        // Insere 'key' na sua posição correta.
        v[j + 1] = key;
    }
}

/**
 * @brief Ordena o vetor usando o algoritmo Selection Sort.
 * * O Selection Sort encontra repetidamente o menor elemento
 * na porção não ordenada e o coloca no início dessa porção.
 *
 * @param v O vetor de inteiros a ser ordenado.
 * @param n O número de elementos no vetor.
 */
void selectionSort(int v[], int n) {
    // Loop principal: percorre o array. 'i' marca o início da porção não ordenada.
    for (int i = 0; i < n - 1; i++) {
        int min = i; // Assume que o primeiro elemento não ordenado é o menor.
        
        // Loop interno: encontra o índice do menor elemento na porção não ordenada.
        for (int j = i + 1; j < n; j++)
            if (v[j] < v[min])
                min = j; // Atualiza o índice do menor elemento encontrado.
        
        // Troca o menor elemento encontrado com o elemento na posição 'i'.
        int temp = v[i];
        v[i] = v[min];
        v[min] = temp;
    }
}

// --- Funções de Merge Sort (Recursivo) ---

/**
 * @brief Combina duas sub-listas ordenadas em uma única lista ordenada.
 * @param v O vetor principal.
 * @param l Índice esquerdo (início da primeira sub-lista).
 * @param m Índice do meio (fim da primeira sub-lista, início da segunda).
 * @param r Índice direito (fim da segunda sub-lista).
 */
void merge(int v[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2]; // Cria arrays temporários para as duas metades.

    // Copia dados para os arrays temporários L[] e R[].
    for (int i = 0; i < n1; i++) L[i] = v[l + i];
    for (int j = 0; j < n2; j++) R[j] = v[m + 1 + j];

    int i = 0, j = 0, k = l; // 'k' é o índice de mesclagem no vetor original 'v'.
    
    // Mescla os arrays temporários de volta em v[l..r]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) v[k++] = L[i++];
        else v[k++] = R[j++];
    }
    // Copia os elementos restantes de L[], se houver.
    while (i < n1) v[k++] = L[i++];
    // Copia os elementos restantes de R[], se houver.
    while (j < n2) v[k++] = R[j++];
}

/**
 * @brief Ordena o vetor usando o algoritmo Merge Sort (Divisão e Conquista).
 * * Divide o vetor recursivamente em sub-vetores e depois os mescla (merge) de forma ordenada.
 *
 * @param v O vetor de inteiros a ser ordenado.
 * @param l Índice inicial.
 * @param r Índice final.
 */
void mergeSort(int v[], int l, int r) {
    // Condição de parada da recursão: quando l >= r (sub-lista com 0 ou 1 elemento).
    if (l < r) {
        int m = l + (r - l) / 2; // Calcula o ponto médio para dividir o vetor.
        mergeSort(v, l, m);      // Ordena a primeira metade (recursão).
        mergeSort(v, m + 1, r);  // Ordena a segunda metade (recursão).
        merge(v, l, m, r);       // Combina as duas metades ordenadas.
    }
}

// --- Funções de Quick Sort (Recursivo) ---

/**
 * @brief Ordena o vetor usando o algoritmo Quick Sort (Divisão e Conquista).
 * * Escolhe um pivô, particiona o vetor (elementos menores à esquerda, maiores à direita)
 * e ordena recursivamente as sub-listas.
 *
 * @param v O vetor de inteiros a ser ordenado.
 * @param low Índice inicial da sub-lista.
 * @param high Índice final da sub-lista.
 */
void quickSort(int v[], int low, int high) {
    if (low < high) {
        // Escolhe o último elemento como pivô.
        int pivot = v[high];
        int i = (low - 1); // Índice do elemento menor.
        
        // Particionamento: move elementos menores que o pivô para a esquerda.
        for (int j = low; j < high; j++) {
            if (v[j] < pivot) {
                i++;
                // Troca v[i] e v[j]
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
        
        // Coloca o pivô em sua posição correta (entre os menores e os maiores).
        int temp = v[i + 1];
        v[i + 1] = v[high];
        v[high] = temp;
        
        int pi = i + 1; // pi é o índice final do pivô.
        
        // Chamadas recursivas para ordenar as sub-listas à esquerda e à direita do pivô.
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

// -------------------- Funções de arquivo --------------------

/**
 * @brief Cria e preenche o arquivo ARQ_ORIGINAL com números aleatórios.
 */
void criarArquivo() {
    // Abre o arquivo para escrita ("w" - write). Se não existir, cria. Se existir, apaga o conteúdo.
    FILE *f = fopen(ARQ_ORIGINAL, "w");
    if (!f) {
        printf("Erro ao criar arquivo!\n");
        return;
    }
    int qtd;
    printf("Quantos valores deseja gerar? ");
    scanf("%d", &qtd);

    // Inicializa o gerador de números aleatórios com a hora atual, para que os números
    // gerados sejam diferentes a cada execução do programa.
    srand(time(NULL));
    
    // Gera 'qtd' números aleatórios entre 0 e 99 e escreve cada um em uma nova linha no arquivo.
    for (int i = 0; i < qtd; i++) {
        int val = rand() % 100;
        fprintf(f, "%d\n", val);
    }
    
    fclose(f); // Fecha o arquivo.
    printf("Arquivo '%s' criado com %d valores.\n", ARQ_ORIGINAL, qtd);
}

/**
 * @brief Lê dados de um arquivo e os armazena em um vetor.
 *
 * @param nome O nome do arquivo a ser lido.
 * @param v O vetor (array) onde os dados serão armazenados.
 * @return O número de elementos lidos.
 */
int lerArquivo(const char *nome, int v[]) {
    // Abre o arquivo para leitura ("r" - read).
    FILE *f = fopen(nome, "r");
    if (!f) {
        printf("Erro ao abrir o arquivo '%s'\n", nome);
        return 0; // Retorna 0 se houver erro ou o arquivo estiver vazio.
    }
    int i = 0;
    // Lê um inteiro por vez do arquivo e armazena em v[i].
    // Continua enquanto a leitura for bem-sucedida (retorna 1) e o limite MAX não for atingido.
    while (fscanf(f, "%d", &v[i]) == 1 && i < MAX)
        i++;
    
    fclose(f); // Fecha o arquivo.
    return i;  // Retorna o número de elementos lidos.
}

/**
 * @brief Salva os dados de um vetor em um arquivo.
 *
 * @param nome O nome do arquivo a ser salvo (ex: "ordenado.txt").
 * @param v O vetor com os dados a serem salvos.
 * @param n O número de elementos no vetor.
 */
void salvarArquivo(const char *nome, int v[], int n) {
    // Abre o arquivo para escrita ("w").
    FILE *f = fopen(nome, "w");
    if (!f) {
        printf("Erro ao salvar no arquivo '%s'\n", nome);
        return;
    }
    // Escreve cada elemento do vetor em uma nova linha no arquivo.
    for (int i = 0; i < n; i++)
        fprintf(f, "%d\n", v[i]);
    
    fclose(f); // Fecha o arquivo.
    printf("Arquivo '%s' salvo com sucesso.\n", nome);
}

/**
 * @brief Exibe o conteúdo de um vetor na tela.
 *
 * @param v O vetor a ser exibido.
 * @param n O número de elementos no vetor.
 */
void mostrar(int v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

// -------------------- Programa Principal --------------------

int main() {
    // Declaração do vetor 'v' (com tamanho MAX), e variáveis de controle.
    int v[MAX], n, opcao, indice, novoValor;

    // Loop principal para manter o menu ativo.
    while (1) {
        printf("\n----------------------------- MENU ------------------------------------\n");
        printf("1. Criar arquivo com dados aleatorios\n");
        printf("2. Ler e ordenar arquivo\n");
        printf("3. Alterar um valor e reordenar\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
    
        if (opcao == 0) break; // Sai do loop se a opção for 0.

        if (opcao == 1) {
            // Opção 1: Cria o arquivo de dados.
            criarArquivo();
        }
        else if (opcao == 2 || opcao == 3) {
            // Opções 2 e 3: Leitura e Ordenação.
            
            // Tenta ler o arquivo original para o vetor 'v'. 'n' armazena o número de elementos lidos.
            n = lerArquivo(ARQ_ORIGINAL, v);
            if (n == 0) continue; // Volta ao menu se não houver dados.

            // Bloco específico para a Opção 3 (Alterar um valor).
            if (opcao == 3) {
                mostrar(v, n);
                printf("Informe o indice (0 a %d) do valor a alterar: ", n - 1);
                scanf("%d", &indice);
                
                // Verifica se o índice é válido.
                if (indice < 0 || indice >= n) {
                    printf("Indice invalido!\n");
                    continue; // Volta ao menu.
                }
                
                printf("Novo valor: ");
                scanf("%d", &novoValor);
                v[indice] = novoValor; // Atualiza o valor no vetor.
                salvarArquivo(ARQ_ORIGINAL, v, n); // Salva o vetor alterado de volta em 'dados.txt'.
            }

            // --- Seleção do Método de Ordenação ---
            printf("\nEscolha o metodo de ordenacao:\n");
            printf("1 - Bubble Sort\n");
            printf("2 - Insertion Sort\n");
            printf("3 - Selection Sort\n");
            printf("4 - Merge Sort\n");
            printf("5 - Quick Sort\n");
            printf("Opcao: ");
            int metodo;
            scanf("%d", &metodo);

            // 'switch' para chamar a função de ordenação correta.
            switch (metodo) {
                case 1: bubbleSort(v, n); break;
                case 2: insertionSort(v, n); break;
                case 3: selectionSort(v, n); break;
                case 4: mergeSort(v, 0, n - 1); break; // Merge Sort precisa dos índices inicial e final.
                case 5: quickSort(v, 0, n - 1); break;   // Quick Sort precisa dos índices inicial e final.
                default: printf("Opcao invalida!\n"); continue;
            }

            // --- Finalização ---
            printf("\nValores ordenados:\n");
            mostrar(v, n); // Mostra o resultado ordenado na tela.
            salvarArquivo(ARQ_ORDENADO, v, n); // Salva o resultado em 'ordenado.txt'.
        }
        else {
            printf("Opcao invalida!\n");
        }
    }

    printf("Programa encerrado.\n");
    return 0;
}