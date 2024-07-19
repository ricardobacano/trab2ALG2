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

Pilha* cria_pilha() {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha != NULL) {
        pilha->topo = NULL;
        pilha->tamanho = 0;
    }
    return pilha;
}

void destroi_pilha(Pilha *pilha) {
    Nodo *atual = pilha->topo;
    while (atual != NULL) {
        Nodo *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(pilha);
}

void push(Pilha *pilha, int chave) {
    Nodo *novo_nodo = (Nodo *)malloc(sizeof(Nodo));
    if (novo_nodo != NULL) {
        novo_nodo->chave = chave;
        novo_nodo->prox = pilha->topo;
        pilha->topo = novo_nodo;
        pilha->tamanho++;
    }
}

int pop(Pilha *pilha, int *chave) {
    if (pilha_vazia(pilha)) {
        return 0;
    }
    Nodo *temp = pilha->topo;
    *chave = temp->chave;
    pilha->topo = temp->prox;
    free(temp);
    pilha->tamanho--;
    return 1;
}

int pilha_vazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

size_t tamanho_pilha(Pilha *pilha) {
    return pilha->tamanho;
}

void getNome(char nome[]) {
    // substitua por seu nome
    strncpy(nome, "Ricardo Quer do Nascimento Filho", MAX_CHAR);
    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

// a função a seguir deve retornar o seu número de GRR
uint32_t getGRR() { return 20224827; }

void preencherVetorAleatorio(int vetor[], size_t tam) {
    srand((unsigned int)time(NULL));
    
    for (size_t i = 0; i < tam; i++) {
        vetor[i] = rand() % tam; // gera valores apartir do tamanho do
    }
}

//===============Imprimir Vetor =====================================================
void imprimeVetor(int vetor[], int tam) {
    if (tam <= 0) {
        printf("[]\n");
        return;
    }

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

    size_t tam = fim - inicio + 1;

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
uint64_t particionar(int vetor[], int a, int b, int* m) {
    int x = vetor[b]; // pivô
    int i, j = a;
    uint64_t comparacoes = 0;

    for (i = a; i < b; i++) {
        comparacoes++;
        if (vetor[i] <= x) {
            trocar(&vetor[i], &vetor[j]);
            j++;
        }
    }

    trocar(&vetor[j], &vetor[b]);
    *m = j;

    return comparacoes;
}

//função recursiva
uint64_t quickSortRec(int vetor[], int a, int b) {
    if (a >= b) return 0;

    int m;
    uint64_t comparacoes = particionar(vetor, a, b, &m);

    comparacoes += quickSortRec(vetor, a, m - 1);
    comparacoes += quickSortRec(vetor, m + 1, b);

    return comparacoes;
}

// função principal 
uint64_t quickSort(int vetor[], size_t tam) {
    return quickSortRec(vetor, 0, tam - 1);
}

//================================Heap Sort Recursivo================================
uint64_t max_heapify(int h[], int i, int n) {
    int l = 2 * i + 1;     // Índice do filho esquerdo
    int r = 2 * i + 2; // Índice do filho direito
    int maior = i;
    uint64_t comparacoes = 0;

    // Verifica se o filho esquerdo é maior que o pai
    if (l < n) {
        comparacoes++;
        if (h[l] > h[i]) {
            maior = l;
        }
    }

    // Verifica se o filho direito é maior que o maior até agora
    if (r < n) {
        comparacoes++;
        if (h[r] > h[maior]) {
            maior = r;
        }
    }

    // Se o maior não for o pai, troca e aplica heapify recursivamente
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

//=================================Quick Sort Iterativo==============================
uint64_t quickSortSR(int vetor[], size_t tam) {
    vetor[0] = 99;
    return -1;
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

//==============================Merge Sort Iterativo=================================
uint64_t mergeSortSR(int vetor[], size_t tam) {
    int* aux = (int*)malloc(tam * sizeof(int));
    if (aux == NULL) {
        return 0;
    }

    Pilha* stack = cria_pilha();
    if (stack == NULL) {
        free(aux);
        return 0;
    }

    uint64_t comparacoes = 0;

    // Primeira passagem: Divisão
    push(stack, 0);
    push(stack, tam - 1);

    while (!pilha_vazia(stack)) {
        int dir, esq;
        pop(stack, &dir);
        pop(stack, &esq);

        if (esq < dir) {
            int meio = esq + (dir - esq) / 2;

            // Empilha os intervalos direito e esquerdo
            push(stack, esq);
            push(stack, meio);
            push(stack, meio + 1);
            push(stack, dir);
        }
    }

    // Segunda passagem: Mesclagem
    for (int curr_size = 1; curr_size <= tam - 1; curr_size = 2 * curr_size) {
        for (int esq = 0; esq < tam - 1; esq += 2 * curr_size) {
            int meio = esq + curr_size - 1;
            int dir = ((esq + 2 * curr_size - 1) < (tam - 1)) ? (esq + 2 * curr_size - 1) : (tam - 1);

            comparacoes += mergir(vetor, aux, esq, meio, dir);
        }
    }

    free(aux);
    destroi_pilha(stack);
    return comparacoes;
}


uint64_t mergir(int vetor[], int aux[], int esq, int meio, int dir) {
    int i, j, k;
    uint64_t comparacoes = 0;

    // copia os dados para o array auxiliar
    for (i = esq; i <= dir; i++) {
        aux[i] = vetor[i];
    }

    i = esq;
    j = meio + 1;
    k = esq;

    while (i <= meio && j <= dir) {
        comparacoes++;
        if (aux[i] <= aux[j]) {
            vetor[k++] = aux[i++];
        } else {
            vetor[k++] = aux[j++];
        }
    }

    // copia o restante dos elementos
    while (i <= meio) {
        vetor[k++] = aux[i++];
    }

    while (j <= dir) {
        vetor[k++] = aux[j++];
    }

    return comparacoes;
}
