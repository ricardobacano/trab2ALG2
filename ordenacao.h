#ifndef ORDENACAO_H_
#define ORDENACAO_H_

#include <stdint.h>
#include <sys/types.h>

#define MAX_CHAR 50

// estrutura do nodo
typedef struct Nodo {
    int chave;
    struct Nodo *prox;
} Nodo;

// estrutura da pilha 
typedef struct Pilha {
    Nodo *topo;
    size_t tamanho;
} Pilha;

// definições de funções para pilha, implementados no ordenação.c
Pilha* cria_pilha();

void destroi_pilha(Pilha *pilha);

void push(Pilha *pilha, int chave);

int pop(Pilha *pilha, int *chave);

int pilha_vazia(Pilha *pilha);

size_t tamanho_pilha(Pilha *pilha);

// a função getNome deve colocar o seu nome no vetor
// seu nome pode ter no máximo MAX_CHAR_NOME - 1 caracteres
void getNome(char nome[]);

// a função a seguir deve retornar o seu número de GRR
uint32_t getGRR();

// Cada uma das funções deve ordenar o vetor passado como parâmetro

// O retorno das funções de ordenação é o número de comparações
// entre elementos do vetor

uint64_t mergeSort(int vetor[], size_t tam);

uint64_t quickSort(int vetor[], size_t tam);

uint64_t heapSort(int vetor[], size_t tam);

// As funções que terminam em SR são "Sem Recursão"
uint64_t mergeSortSR(int vetor[], size_t tam);

uint64_t quickSortSR(int vetor[], size_t tam);

uint64_t heapSortSR(int vetor[], size_t tam);

uint64_t mergeR(int vetor[],size_t inicio, size_t meio, size_t fim, uint64_t* numComparacoesint,int vetor_u[]);

void imprimeVetor(int vetor[], int tam);

void copiar(int vetor[],size_t inicio, size_t fim, int vetor_u[]);

void preencherVetorAleatorio(int vetor[], size_t tam);

uint64_t mergir(int vetor[], int aux[], int esq, int meio, int dir);

uint64_t mergeSortAux(int vetor[], size_t inicio, size_t fim, uint64_t* numComparacoes, int vetor_u[]);

#endif  // ORDENACAO_H_