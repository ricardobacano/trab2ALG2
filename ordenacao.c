#include "ordenacao.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define MAX_VAL 1000

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//=================================Funcções de Pilha==============================
Pilha* cria_pilha(int capacidade) {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->elementos = (int*)malloc(capacidade * sizeof(int));
    return pilha;
}

// Função para destruir a pilha
void destroi_pilha(Pilha* pilha) {
    free(pilha->elementos);
    free(pilha);
}

// Função para verificar se a pilha está vazia
int pilha_vazia(Pilha* pilha) {
    return pilha->topo == -1;
}

// Função para empilhar um elemento
void push(Pilha* pilha, int valor) {
    if (pilha->topo < pilha->capacidade - 1) {
        pilha->elementos[++(pilha->topo)] = valor;
    }
}

// Função para desempilhar um elemento
void pop(Pilha* pilha, int* valor) {
    if (!pilha_vazia(pilha)) {
        *valor = pilha->elementos[(pilha->topo)--];
    }
}

void getNome(char nome[]) {
    // substitua por seu nome
    strncpy(nome, "Ricardo Quer do Nascimento Filho", MAX_CHAR);
    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

// a função a seguir deve retornar o seu número de GRR
uint32_t getGRR() { return 20224827; }

void preencherVetorAleatorio(int vetor[], size_t tam, int min, int max) {
    srand((unsigned int)time(NULL));
    
    for (size_t i = 0; i < tam; i++) {
        vetor[i] = min + rand() % (max - min + 1); // gera 
    }
}

//===============Imprimir Vetor =====================================================
void imprimeVetor(int vetor[], int tam) {

    /*for (size_t i = 0; i < tam; i++)  {
        printf("%d, ", vetor[i]);
    }
    printf("\n");
    if (tam <= 0) {
        printf("[]\n");
        return;
    }*/

    printf("[ ");
    if (tam <= 10) {
        // Imprime todos os elementos se o tamanho for menor ou igual a 10
        for (int i = 0; i < tam; i++) {
            printf("%d", vetor[i]);
            if (i < tam - 1) {
                printf(", ");
            }
        }
    } else {
        // Imprime os primeiros 5 elementos
        for (int i = 0; i < 5; i++) {
            printf("%d", vetor[i]);
            if (i < 4) {
                printf(", ");
            }
        }
        printf(" ... ");
        // Imprime os últimos 5 elementos
        for (int i = tam - 5; i < tam; i++) {
            printf("%d", vetor[i]);
            if (i < tam - 1) {
                printf(", ");
            }
        }
    }
    printf(" ]\n");
}

//===============Merge Sort Recursivo ===============================================
uint64_t mergeSort(int vetor[], size_t tam) {
    if (tam <= 0) {
        return 0;
    }

    int *vetor_u = (int *)malloc(tam * sizeof(int));
    if (vetor_u == NULL) {
        return 0; // falha na alocação de memória
    }

    uint64_t numComparacoes = 0;
    numComparacoes = mergeSortAux(vetor, 0, tam - 1, &numComparacoes, vetor_u);

    free(vetor_u);
    return numComparacoes;
}

uint64_t mergeSortAux(int vetor[], size_t inicio, size_t fim, uint64_t* numComparacoes, int vetor_u[]) {
    if (inicio >= fim) {
        return 0; 
    }

    size_t meio = (inicio + fim) / 2;

    // dividir e conquistar
    mergeSortAux(vetor, inicio, meio, numComparacoes, vetor_u);
    mergeSortAux(vetor, meio + 1, fim, numComparacoes, vetor_u);

    // mesclar as duas metades
    return mergeR(vetor, inicio, meio, fim, numComparacoes, vetor_u);
}

uint64_t mergeR(int vetor[], size_t inicio, size_t meio, size_t fim, uint64_t* numComparacoes, int vetor_u[]) {
    size_t k = 0;
    size_t i = inicio;
    size_t j = meio + 1;

    // Copiar o intervalo para o vetor auxiliar
    for (size_t idx = inicio; idx <= fim; idx++) {
        vetor_u[idx - inicio] = vetor[idx];
    }

    // Mesclar os intervalos
    while (i <= meio && j <= fim) {
        (*numComparacoes)++;
        if (vetor_u[i - inicio] <= vetor_u[j - inicio]) {
            vetor[inicio + k++] = vetor_u[i - inicio];
            i++;
        } else {
            vetor[inicio + k++] = vetor_u[j - inicio];
            j++;
        }
    }

    // Copiar os elementos restantes da parte esquerda, se houver
    while (i <= meio) {
        vetor[inicio + k++] = vetor_u[i - inicio];
        i++;
    }

    // Copiar os elementos restantes da parte direita, se houver
    while (j <= fim) {
        vetor[inicio + k++] = vetor_u[j - inicio];
        j++;
    }

    return *numComparacoes;
}

void copiar(int vetor[],size_t inicio, size_t fim, int vetor_u[]){
    size_t i;

    for (i = inicio; i <= fim; i++){
        /* a posição do vetor_u é (i - inicio) */
        vetor[i] = vetor_u[i - inicio];
    } 
}

//===============================Quick Sort Recursivo=================================
int particionar(int vetor[], int a, int b, uint64_t *comparacoes) {
    int pivo = vetor[a];
    int i = a;
    int j = b;

    while (i < j) {
        // Encontra o primeiro elemento maior que o pivô
        while (vetor[i] <= pivo && i <= b - 1) {
            i++;
            (*comparacoes)++;
        }

        // Encontra o primeiro elemento menor que o pivô
        while (vetor[j] > pivo && j >= a + 1) {
            j--;
            (*comparacoes)++;
        }

        if (i < j) {
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[a], &vetor[j]);
    return j;
}

// Função de ordenação rápida (QuickSort)
void quickSortRecursivo(int vetor[], int a, int b, uint64_t *comparacoes) {
    if (a < b) {
        int i = particionar(vetor, a, b, comparacoes);
        quickSortRecursivo(vetor, a, i - 1, comparacoes);
        quickSortRecursivo(vetor, i + 1, b, comparacoes);
    }
}

// Função principal do QuickSort com contagem de comparações
uint64_t quickSort(int vetor[], size_t tam) {
    uint64_t comparacoes = 0;
    quickSortRecursivo(vetor, 0, tam - 1, &comparacoes);
    return comparacoes;
}

//================================Heap Sort Recursivo================================
uint64_t max_heapify(int h[], int i, int n) {
    int l = 2 * i + 1;     //índice do filho esquerdo
    int r = 2 * i + 2; //índice do filho direito
    int maior = i;
    uint64_t comparacoes = 0;

    //verifica se o filho esquerdo é maior que o pai
    if (l < n) {
        comparacoes++;
        if (h[l] > h[i]) {
            maior = l;
        }
    }

    //verifica se o filho direito é maior que o maior até agora
    if (r < n) {
        comparacoes++;
        if (h[r] > h[maior]) {
            maior = r;
        }
    }

    //se o maior não for o pai, troca e aplica heapify recursivamente
    if (maior != i) {
        trocar(&h[i], &h[maior]);
        comparacoes += max_heapify(h, maior, n); // Contagem de comparações recursivas
    }

    return comparacoes;
}

// função para construir um max-heap
uint64_t construir_max_heap(int v[], int n) {
    uint64_t comparacoes = 0;
    for (int i = (n / 2) - 1; i >= 0; i--) {
        comparacoes += max_heapify(v, i, n);
    }
    return comparacoes;
}

// função para ordenar um vetor usando heap sort
uint64_t heapSort(int v[], size_t tam) {
    int n = (int)tam;
    uint64_t comparacoes = 0;

    comparacoes += construir_max_heap(v, n);

    for (int i = n - 1; i > 0; i--) {
        trocar(&v[0], &v[i]);  // Move o maior elemento para o final
        comparacoes += max_heapify(v, 0, i); // Reajusta o heap
    }

    return comparacoes;
}

//==============================Merge Sort Iterativo=================================
void mesclar(int vetor[], int esq, int meio, int dir, uint64_t *comparacoes) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int *E = (int *)malloc(n1 * sizeof(int));
    int *D = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) 
        E[i] = vetor[esq + i];
    for (int j = 0; j < n2; j++) 
        D[j] = vetor[meio + 1 + j];

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        (*comparacoes)++;
        if (E[i] <= D[j]) {
            vetor[k] = E[i];
            i++;
        } else {
            vetor[k] = D[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vetor[k] = E[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetor[k] = D[j];
        j++;
        k++;
    }

    free(E);
    free(D);
}

// Função de ordenação por mescla (MergeSort) iterativa usando pilha
uint64_t mergeSortSR(int vetor[], size_t tam) {
    uint64_t comparacoes = 0;

    // Inicializa as pilhas para armazenar os índices
    int *pilhaEsq = (int *)malloc(tam * sizeof(int));
    int *pilhaDir = (int *)malloc(tam * sizeof(int));
    int topo = -1;

    // Empilha os índices iniciais
    pilhaEsq[++topo] = 0;
    pilhaDir[topo] = (int)tam - 1;

    // Loop até a pilha estar vazia
    while (topo >= 0) {
        // Desempilha esq e dir
        int esq = pilhaEsq[topo];
        int dir = pilhaDir[topo];
        topo--;

        if (esq < dir) {
            int meio = esq + (dir - esq) / 2;

            // Empilha os índices para as duas metades
            pilhaEsq[++topo] = esq;
            pilhaDir[topo] = meio;

            pilhaEsq[++topo] = meio + 1;
            pilhaDir[topo] = dir;

            // Mescla as duas metades
            mesclar(vetor, esq, meio, dir, &comparacoes);
        }
    }

    // Libera a memória alocada para as pilhas
    free(pilhaEsq);
    free(pilhaDir);

    return comparacoes;
}

//=================================Quick Sort Iterativo==============================
uint64_t quickSortSR(int vetor[], size_t tam) {
    uint64_t comparacoes = 0;

    // Inicializa a pilha
    int *pilha = (int *)malloc(tam * sizeof(int));
    int topo = -1;

    // Empilha os índices iniciais
    pilha[++topo] = 0;
    pilha[++topo] = tam - 1;

    // Loop até a pilha estar vazia
    while (topo >= 0) {
        // Desempilha alto e baixo
        int b = pilha[topo--];
        int a = pilha[topo--];

        // Particiona o vetor e obtém o índice do pivô
        int i = particionar(vetor, a, b, &comparacoes);

        // Se houver elementos à esquerda do pivô, empilha os índices
        if (i - 1 > a) {
            pilha[++topo] = a;
            pilha[++topo] = i - 1;
        }

        // Se houver elementos à direita do pivô, empilha os índices
        if (i + 1 < b) {
            pilha[++topo] = i + 1;
            pilha[++topo] = b;
        }
    }

    // Libera a memória alocada para a pilha
    free(pilha);

    return comparacoes;
}


//================================Heap Sort Iterativo================================
uint64_t buildMaxHeap(int arr[], int n) {
    uint64_t comparacoes = 0;
    
    for (int i = 1; i < n; i++) {
        comparacoes++;
        if (arr[i] > arr[(i - 1) / 2]) {
            int j = i;
            while (arr[j] > arr[(j - 1) / 2]) {
                trocar(&arr[j], &arr[(j - 1) / 2]);
                j = (j - 1) / 2;
                comparacoes++;
            }
        }
    }
    
    return comparacoes;
}

uint64_t heapSortSR(int arr[], size_t n) {
    uint64_t comparacoes = buildMaxHeap(arr, n);
    
    for (int i = n - 1; i > 0; i--) {
        trocar(&arr[0], &arr[i]);
        
        int j = 0, index;
        do {
            index = (2 * j + 1);
            
            if (index < (i - 1)) {
                comparacoes++;
                if (arr[index] < arr[index + 1]) {
                    index++;
                }
            }
            
            if (index < i) {
                comparacoes++;
                if (arr[j] < arr[index]) {
                    trocar(&arr[j], &arr[index]);
                }
            }
            
            j = index;
        } while (index < i);
    }
    
    return comparacoes;
}

