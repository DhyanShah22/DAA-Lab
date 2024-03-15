#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name;
    int start;
    int end;
    int weight;
} Event;

int compare(const void *a, const void *b) {
    return (((Event*)a)->end - ((Event*)b)->end);
}

int maxEvents(Event events[], int n, int *maxWeight) {
    qsort(events, n, sizeof(Event), compare);
    
    int *dp = (int*)malloc(n * sizeof(int));
    int *weights = (int*)malloc(n * sizeof(int));
    
    dp[0] = 1; 
    weights[0] = events[0].weight;
    
    for (int i = 1; i < n; i++) {
        dp[i] = 1; 
        weights[i] = events[i].weight;
        
        for (int j = 0; j < i; j++) {
            if (events[i].start >= events[j].end) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    weights[i] = weights[j] + events[i].weight;
                }
            }
        }
    }
    
    int max = 0;
    *maxWeight = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max) {
            max = dp[i];
            *maxWeight = weights[i];
        }
    }
    
    free(dp);
    free(weights);
    
    return max;
}

int main() {
    printf("Dhyan Shah\n");
    printf("22BCP269\n");
    int n;
    printf("Enter the number of events: ");
    scanf("%d", &n);
    
    Event *events = (Event*)malloc(n * sizeof(Event));
    
    printf("Enter the events:\n");
    for (int i = 0; i < n; i++) {
        printf("Event %d (Name Start End Weight): ", i + 1);
        scanf(" %c %d %d %d", &events[i].name, &events[i].start, &events[i].end, &events[i].weight);
    }
    
    int maxWeight;
    int max = maxEvents(events, n, &maxWeight);
    
    printf("Maximum number of events that can be scheduled: %d\n", max);
    printf("Maximum weight when all events are scheduled: %d\n", maxWeight);
    
    free(events);
    
    return 0;
}