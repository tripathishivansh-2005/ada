#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiplyMatrices(int n, int **matrixA, int **matrixB, int **resultMatrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < n; k++) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter the size (N) for the N x N matrices: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Matrix size must be positive.\n");
        return 1;
    }

    int **matrixA = (int **)malloc(n * sizeof(int *));
    int **matrixB = (int **)malloc(n * sizeof(int *));
    int **resultMatrix = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        matrixA[i] = (int *)malloc(n * sizeof(int));
        matrixB[i] = (int *)malloc(n * sizeof(int));
        resultMatrix[i] = (int *)malloc(n * sizeof(int));
    }

    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }

    start = clock();
    multiplyMatrices(n, matrixA, matrixB, resultMatrix);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Matrix multiplication for %d x %d matrices took %f seconds to execute.\n", n, n, cpu_time_used);

    for (int i = 0; i < n; i++) {
        free(matrixA[i]);
        free(matrixB[i]);
        free(resultMatrix[i]);
    }
    free(matrixA);
    free(matrixB);
    free(resultMatrix);

    return 0;
}