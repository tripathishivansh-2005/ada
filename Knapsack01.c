#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int max(int a, int b) {
    return (a > b) ? a : b;
}
int knapsack(int W, int wt[], int val[], int n) {
    int dp[n+1][W+1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i-1] <= w)
                dp[i][w] = max(val[i-1] + dp[i-1][w-wt[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][W];
}
int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    int val[n], wt[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        val[i] = (rand() % 100) + 1;
        wt[i] = (rand() % 50) + 1;
    }
    W = n * 15;
    printf("Generated knapsack capacity: %d\n", W);
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int result = knapsack(W, wt, val, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nMaximum value in Knapsack = %d\n", result);
    printf("Time taken to execute: %f seconds\n", cpu_time_used);
    return 0;
}

