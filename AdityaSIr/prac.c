#include<stdio.h>

#define MAX_N 100
#define MAX_B 10000

int maxReturns(int n, int b, int t, int c[], int q[], int r[]){
    int DP[MAX_N + 1][MAX_B + 1];

    for(int i =0; i<=n; i++){
        for(int j=0; j<=b; j++){
            DP[i][j]=0;
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=b; j++){
            for(int q_asset = 0; q_asset<=(j/c[i]); q_asset++){
                DP[i][j] =  DP[i-1][j] ;
                if(q_asset <= q[i]){
                     if (DP[i][j] > DP[i - 1][j - q_asset * c[i]] + q_asset * r[i]) {
                        DP[i][j] = DP[i][j];
                    } else {
                        DP[i][j] = DP[i - 1][j - q_asset * c[i]] + q_asset * r[i];
                    }
                }
            }
        }
    }
}

int main() {
    int n,b,t;

    printf("Enter the number of assests: ");
    scanf("%d", &n);
    printf("Enter the amount of money: ");
    scanf("%d", &b);
    printf("Enter the total number of months: ");
    scanf("%d", &t);

    int c[MAX_N + 1], q[MAX_N + 1], r[MAX_N + 1];

    for(int i = 1; i<=n; i++){
        printf("Enter cost of asset %d\n: ",i);
        scanf("%d %d %ld", &c[i], &q[i], &r[i]);
    } 

    int max_returns = maxReturns(n,b,t, c, q, r);
    printf("The max returns are %d\n", max_returns);

    return 0;
}