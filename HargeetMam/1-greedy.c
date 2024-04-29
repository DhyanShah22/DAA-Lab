#include<stdio.h>
#include<stdlib.h>

typedef struct{
    char job;
    int start;
    int end;
    int profit;
} Job;

int compare(const void *a, const void* b){
    return ((Job*)a)->end - ((Job*)b)->end;  
}
int maxPro(Job jobs[], int n,int *maxprofit) {
    qsort(jobs, n, sizeof(Job), compare);  

    int *dp = (int *)malloc(n * sizeof(int));
    dp[0] = 1;

    int *profit = (int *)malloc(n * sizeof(int));
    profit[0] = jobs[0].profit;
    
    for(int i=1;i<n;i++){
        dp[i] = 1;
        profit[i] = jobs[i].profit;
        for(int j=0; j<=i; j++){
            if(jobs[i].start >= jobs[j].end){
                if(dp[i] < dp[j] +1){
                    dp[i] = dp[j] + 1;
                    profit[i] = profit[j] + jobs[i].profit;
                }
            }
        }
    }

    int max = 0;
    *maxprofit = 0;
    for(int i=0;i<n;i++){
        if(dp[i] > max){
            max = dp[i];
            *maxprofit = profit[i];
        }
    }

    free(dp);
    free(profit);
    return max;
}

int main(){
    int  n, i;

    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    Job* j = (Job*)malloc(sizeof(Job)*n);

    printf("Enter the Jobs:\n");
    for (int i = 0; i < n; i++) {
        printf("Event %d (Name Start End Weight): ", i + 1);
        scanf(" %c %d %d %d", &j[i].job, &j[i].start, &j[i].end, &j[i].profit);
    }

    int maxProfit;
    int max_profit = maxPro(j, n, &maxProfit);

    printf("Maximum number of events that can be scheduled: %d\n", max_profit);
    printf("Maximum profit when all events are scheduled: %d\n", maxProfit);

    free(j);

    return 0;
}