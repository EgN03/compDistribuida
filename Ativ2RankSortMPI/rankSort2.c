// Identificação do grupo:
// - Enrique Granado Novaes, 10276914
// Gabriel Santos, 10388025
// Paulo Henrique Camargo, 10389453


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void rankSort(int *a, int n) {
    int *b = (int *)malloc(n * sizeof(int));
    int i, j, x, cont;

    // Processamento local
    for (i = 0; i < n; i++) {
        cont = 0;
        for (j = 0; j < n; j++) {
            if (a[i] > a[j] || (a[i] == a[j] && i > j)) {
                cont++;
            }
        }
        b[cont] = a[i];
    }

    // Imprime o resultado.
    printf("Resultado ordenado:\n");
    for (i = 0; i < n; i++)
        printf("%d ", b[i]);
    printf("\n");

    free(b);
}

int main(int argc, char *argv[]) {
    int myrank;
    int *data;
    int n = 10; // Tamanho do vetor

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank == 0) {
        data = (int *)malloc(n * sizeof(int));
        
        // Gera num aleatórios.
        printf("Vetor original:\n");
        for (int i = 0; i < n; i++) {
            data[i] = rand() % 100; // Gera num aleatórios de 0 a 99
            printf("%d ", data[i]);
        }
        printf("\n");

        rankSort(data, n);

        free(data);
    }

    MPI_Finalize();

    return 0;
}
