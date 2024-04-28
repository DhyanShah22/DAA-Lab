#include <stdio.h>

#define MAX_N 100
#define MAX_B 10000

int maximizeReturns(int n, int b, int t, int c[], int q[], int r[]) {
    int DP[MAX_N + 1][MAX_B + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= b; j++) {
            DP[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= b; j++) {
            for (int q_asset = 0; q_asset <= (j / c[i]); q_asset++) {
                DP[i][j] = DP[i - 1][j]; 
                if (q_asset <= q[i]) {
                    if (DP[i][j] > DP[i - 1][j - q_asset * c[i]] + q_asset * r[i]) {
                        DP[i][j] = DP[i][j];
                    } else {
                        DP[i][j] = DP[i - 1][j - q_asset * c[i]] + q_asset * r[i];
                    }
                }
            }
        }
    }

    return DP[n][b];
}

int main() {
    int n, b, t;
    printf("Enter the number of assets: ");
    scanf("%d", &n);
    printf("Enter the maximum budget: ");
    scanf("%d", &b);
    printf("Enter the number of months: ");
    scanf("%d", &t);

    int c[MAX_N + 1], q[MAX_N + 1], r[MAX_N + 1];

    printf("Enter the cost, quantity, and expected return for each asset:\n");
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &c[i], &q[i], &r[i]);
    }

    int max_returns = maximizeReturns(n, b, t, c, q, r);
    printf("Maximum returns after %d months: %d\n", t, max_returns);

    return 0;
}
