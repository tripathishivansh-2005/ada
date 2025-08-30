#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void generaterandomarray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    int *copy = (int*)malloc(n * sizeof(int));

    generaterandomarray(arr, n);

    clock_t start = clock();
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < n; j++)
            copy[j] = arr[j];

        insertionSort(copy, n);
    }
    clock_t end = clock();

    double timetaken = ((double)(end - start)) / CLOCKS_PER_SEC / 1000.0;
    printf("Average time taken per sort (Insertion) = %f seconds\n", timetaken);

    free(arr);
    free(copy);
    return 0;
}
