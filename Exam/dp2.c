#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maximize_impact(int n, int cost[], int qty[], int reach[], int B) {
    int dp[n + 1][B + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= B; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (j < cost[i - 1])
                dp[i][j] = dp[i - 1][j];
            else {
                int max_impact = 0;
                int Tcost = qty[i-1]*cost[i-1];
                if (j>=Tcost)
                {
                    max_impact = max(max_impact,reach[i - 1] + dp[i - 1][j - Tcost]);
                }
                
                dp[i][j] = max(dp[i - 1][j], max_impact);
            }
        }
    }

    return dp[n][B];
}

int main() {
    int n = 4;
    int cost[] = {80, 40, 12, 20};
    int qty[] = {3, 4, 10, 6};
    int reach[] = {10, 8, 5, 6};
    int B = 240;

    int max_impact = maximize_impact(n, cost, qty, reach,B);
    printf("Maximized reach impact: %d\n", max_impact);

    return 0;
}
