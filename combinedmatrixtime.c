#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** allocMatrix(int n) {
    int** m = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        m[i] = (int*)malloc(n * sizeof(int));
    return m;
}

void freeMatrix(int** m, int n) {
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void generateMatrix(int** m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = rand() % 10;
}

void addMatrix(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}


void iterativeMultiply(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

void dcMultiply(int n, int** A, int** B, int** C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int k = n / 2;

    int** A11 = allocMatrix(k);
    int** A12 = allocMatrix(k);
    int** A21 = allocMatrix(k);
    int** A22 = allocMatrix(k);
    int** B11 = allocMatrix(k);
    int** B12 = allocMatrix(k);
    int** B21 = allocMatrix(k);
    int** B22 = allocMatrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    int** C11 = allocMatrix(k);
    int** C12 = allocMatrix(k);
    int** C21 = allocMatrix(k);
    int** C22 = allocMatrix(k);
    int** T1 = allocMatrix(k);
    int** T2 = allocMatrix(k);

    dcMultiply(k, A11, B11, T1);
    dcMultiply(k, A12, B21, T2);
    addMatrix(k, T1, T2, C11);

    dcMultiply(k, A11, B12, T1);
    dcMultiply(k, A12, B22, T2);
    addMatrix(k, T1, T2, C12);

    dcMultiply(k, A21, B11, T1);
    dcMultiply(k, A22, B21, T2);
    addMatrix(k, T1, T2, C21);

    dcMultiply(k, A21, B12, T1);
    dcMultiply(k, A22, B22, T2);
    addMatrix(k, T1, T2, C22);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    freeMatrix(A11, k); freeMatrix(A12, k);
    freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k);
    freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(C11, k); freeMatrix(C12, k);
    freeMatrix(C21, k); freeMatrix(C22, k);
    freeMatrix(T1, k); freeMatrix(T2, k);
}
 
void strassenMultiply(int n, int** A, int** B, int** C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int k = n / 2;

    int** A11 = allocMatrix(k); int** A12 = allocMatrix(k);
    int** A21 = allocMatrix(k); int** A22 = allocMatrix(k);
    int** B11 = allocMatrix(k); int** B12 = allocMatrix(k);
    int** B21 = allocMatrix(k); int** B22 = allocMatrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    int** M1 = allocMatrix(k); int** M2 = allocMatrix(k);
    int** M3 = allocMatrix(k); int** M4 = allocMatrix(k);
    int** M5 = allocMatrix(k); int** M6 = allocMatrix(k);
    int** M7 = allocMatrix(k);
    int** T1 = allocMatrix(k); int** T2 = allocMatrix(k);

    addMatrix(k, A11, A22, T1);
    addMatrix(k, B11, B22, T2);
    strassenMultiply(k, T1, T2, M1);

    addMatrix(k, A21, A22, T1);
    strassenMultiply(k, T1, B11, M2);

    subMatrix(k, B12, B22, T2);
    strassenMultiply(k, A11, T2, M3);

    subMatrix(k, B21, B11, T2);
    strassenMultiply(k, A22, T2, M4);

    addMatrix(k, A11, A12, T1);
    strassenMultiply(k, T1, B22, M5);

    subMatrix(k, A21, A11, T1);
    addMatrix(k, B11, B12, T2);
    strassenMultiply(k, T1, T2, M6);

    subMatrix(k, A12, A22, T1);
    addMatrix(k, B21, B22, T2);
    strassenMultiply(k, T1, T2, M7);

    int** C11 = allocMatrix(k); int** C12 = allocMatrix(k);
    int** C21 = allocMatrix(k); int** C22 = allocMatrix(k);

    addMatrix(k, M1, M4, T1);
    subMatrix(k, T1, M5, T2);
    addMatrix(k, T2, M7, C11);

    addMatrix(k, M3, M5, C12);
    addMatrix(k, M2, M4, C21);

    subMatrix(k, M1, M2, T1);
    addMatrix(k, T1, M3, T2);
    addMatrix(k, T2, M6, C22);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    freeMatrix(A11, k); freeMatrix(A12, k);
    freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k);
    freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(M1, k); freeMatrix(M2, k); freeMatrix(M3, k);
    freeMatrix(M4, k); freeMatrix(M5, k); freeMatrix(M6, k); freeMatrix(M7, k);
    freeMatrix(T1, k); freeMatrix(T2, k);
    freeMatrix(C11, k); freeMatrix(C12, k);
    freeMatrix(C21, k); freeMatrix(C22, k);
}
int main() {
    srand(time(0));
    int n;
    printf("Enter matrix size (must be power of 2): ");
    scanf("%d", &n);

    int** A = allocMatrix(n);
    int** B = allocMatrix(n);
    int** C = allocMatrix(n);

    generateMatrix(A, n);
    generateMatrix(B, n);

    clock_t start, end;
    double time_naive, time_dc, time_strassen;

    // Naïve
    start = clock();
   iterativeMultiply(n, A, B, C);
    end = clock();
    time_naive = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Divide & Conquer
    start = clock();
    dcMultiply(n, A, B, C);
    end = clock();
    time_dc = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Strassen
    start = clock();
    strassenMultiply(n, A, B, C);
    end = clock();
    time_strassen = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nExecution times for %d x %d matrices:\n", n, n);
    printf("Iterative(O(n^3))          : %f s\n", time_naive);
    printf("Divide & Conquer (O(n^3)): %f s\n", time_dc);
    printf("Strassen (O(n^2.81))     : %f s\n", time_strassen);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}
