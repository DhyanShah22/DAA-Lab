#include<stdio.h>
#include<stdlib.h>

typedef struct {
    char name;
    int start;
    int end;
    int profit;
} Job;

int compare(const void *a, const void* b){
    return (((Job*)a)->end - ((Job*)b)->end); 
}

int maxProf(Job jobs[], int n, int* maxProfit){
    qsort(jobs, n, sizeof(Job), compare);

    int *dp = (int *)malloc(n  * sizeof(int));
    dp[0] = 1;

    int* profits = (int * )malloc(sizeof(int));
    profits[0] = jobs[0].profit;

    for(int i=1; i<n; i++){
        dp[i] = 1;
        profits[i] = jobs[i].profit;

        for(int j=0; j<i-1; j++){
            if(jobs[i].start >= jobs[j].end){
                if(dp[i] < dp[j] +1 ){
                    dp[i] = dp[j] +1;
                    profits[i] = profits[j] + jobs[i].profit;
                }
            }
        }
    }

    *maxProfit = 0;
    int max = 0;
    for(int i=0;i<n; i++){
        if(dp[i] > max){
            max=dp[i];
            *maxProfit = profits[i];
        }
    }
}
int main() {
    int n, i;

    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    Job* jobs = (Job *)malloc(n * sizeof(Job)); // Correct allocation

    printf("Enter job details: ");
    for(i = 0; i < n; i++) {
        printf("Job %d (Name Start End Profit): ", i + 1); // Added %d for job index
        scanf(" %c %d %d %d", &jobs[i].name, &jobs[i].start, &jobs[i].end, &jobs[i].profit); // Corrected format specifier
    }

    int maxProfit;
    int max = maxProf(jobs, n, &maxProfit);
    
    printf("\nMaximum Profit can be made by assigning following jobs:\n\n");
    for(i = 0; i < max ; i++)
        printf("Job %c \n", jobs[i].name);
        
    printf("\nMaximum Profit is: %d\n", maxProfit);

    free(jobs); // Freeing allocated memory
    return 0;
}
