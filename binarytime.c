#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary Search Function
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Not found
}

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, result = 0;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    srand(time(0));

    //  Generate random numbers
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  // values between 0 and 999
    }

    //  Sort array for binary search
    qsort(arr, n, sizeof(int), compare);

    // Generate random target key
    int target = rand() % 1000;
    printf("Randomly generated key to search: %d\n", target);

    //  Start time measurement
    clock_t start = clock();

    for (int i = 0; i < 100000; i++) {
        result = binarySearch(arr, n, target);
    }

    //  End time measurement
    clock_t end = clock();

    // Average time per search
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC / 100000.0)*1000;

    if (result != -1) {
        printf("Element %d found at index %d (after sorting).\n", target, result);
    } else {
        printf("Element %d not found in the array.\n", target);
    }

    printf("Average time taken for binary search: %f milliseconds\n", time_taken);

    free(arr);
    return 0;
}
