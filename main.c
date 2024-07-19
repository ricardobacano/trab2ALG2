#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

int main() {
    char nome[MAX_CHAR];
    int numComp;
    size_t tamVetor;

    printf("Digite o tamanho do vetor: ");
    scanf("%zu", &tamVetor);
    // printf("Tamanho do vetor: %zu\n", tamVetor);

    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());

    preencherVetorAleatorio(vetor,tamVetor);

    imprimeVetor(vetor, tamVetor);
    printf("\n");

    clock_t start, end;
    double total;

//======================Merge Sort Recursivo====================================

    numComp = 0;
    start = clock();
    numComp = mergeSort(vetor, tamVetor);
    end = clock();
    total = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Merge Sort Recursivo\n");
    imprimeVetor(vetor, tamVetor);
    printf("Comparações: %d\n", numComp);
    printf("Tempo: %f segundos\n", total);
    printf("\n");

//======================Merge Sort Iterativo====================================

    numComp = 0;
    start = clock();
    numComp = mergeSortSR(vetor, tamVetor);
    end = clock();
    total = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Merge Sort Iterativo\n");
    imprimeVetor(vetor, tamVetor);
    printf("Comparações: %d\n", numComp);
    printf("Tempo: %f segundos\n", total);
    printf("\n");


//======================Heap Sort Recursivo====================================

    numComp = 0;
    start = clock();
    numComp = heapSort(vetor, tamVetor);
    end = clock();
    total = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Heap Sort Recursivo\n");
    imprimeVetor(vetor, tamVetor);
    printf("Comparações: %d\n", numComp);
    printf("Tempo: %f segundos\n", total);

    /*printf("NumComp: %d\n", numComp);
    numComp = quickSort(vetor, 3);
    printf("NumComp: %d\n", numComp);
    numComp = quickSortSR(vetor, 3);

    printf("NumComp: %d\n", numComp);
    numComp = heapSort(vetor, 3);
    printf("NumComp: %d\n", numComp);
    numComp = heapSortSR(vetor, 3);
    printf("NumComp: %d\n", numComp); */

    free(vetor);

    return 0;
}
