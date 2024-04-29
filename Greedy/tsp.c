#include<stdio.h>

int a[10][10], visited[10], n, cost = 0;

void get() {
    int i, j;
    printf("Enter No. of Cities: ");
    scanf("%d", &n);
    printf("\nEnter Cost Matrix:");
    for (i = 0; i < n; i++) {
        printf("\nEnter Elements of Row# : %d\n", i + 1);
        
        for (j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

        visited[i] = 0;
    }
    printf("\nThe cost list is:");
    for (i = 0; i < n; i++) {
        printf("\n");
        for (j = 0; j < n; j++)
            printf("%d \t", a[i][j]);
    }
}

int least(int city) {
    int i, ncindex = 999;
    int mincost = 999;
    for (i = 0; i < n; i++) {
        if ((a[city][i] != 0) && (visited[i] == 0)){
            if (a[city][i] < mincost) {
                mincost = a[city][i];
                ncindex = i;
            }
        }
    }
    if (mincost != 999)
        cost += mincost;
    return ncindex;
}

void mincost(int city) {
    int i, ncity;
    visited[city] = 1;
    printf(" %d ->", city + 1);
    ncity = least(city);
    if (ncity == 999) {
        ncity = 0;
        printf(" %d", ncity + 1);
        cost += a[city][ncity];
        return;
    }
    mincost(ncity);
}

void put() {
    printf("\nMinimum cost: ");
    printf("%d", cost);
}

int main() {
    get();
    printf("\n\nThe Path is: ");
    mincost(0);
    put();
}