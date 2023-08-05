#include <stdio.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

// Function to solve the knapsack problem using dynamic programming
int knapsack(int W, int weights[], int values[], int n) {
    int dp[n + 1][W + 1];

    // Initialize the dp array with zeros
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = 0;
        }
    }

    // Build the dp array using bottom-up approach
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Return the maximum value that can be achieved
    return dp[n][W];
}

int main() {
    int n, W;

    // Get the number of items and knapsack capacity from the user
    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the knapsack capacity: ");
    scanf("%d", &W);

    int weights[n];
    int values[n];

    // Get the weights and values of each item from the user
    printf("Enter the weight and value for each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &weights[i], &values[i]);
    }

    int max_value = knapsack(W, weights, values, n);
    printf("Maximum value that can be achieved: %d\n", max_value);

    return 0;
}
