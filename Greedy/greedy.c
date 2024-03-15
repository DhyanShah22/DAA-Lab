#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent an event
typedef struct {
    char name;
    int start;
    int end;
    int weight;
} Event;

// Function to compare events by their ending time (used for sorting)
int compare(const void *a, const void *b) {
    return (((Event*)a)->end - ((Event*)b)->end);
}

// Function to find the maximum number of events that can be scheduled
int maxEvents(Event events[], int n, int *maxWeight) {
    // Sort the events based on their ending times
    qsort(events, n, sizeof(Event), compare);
    
    // Initialize an array to store the maximum number of events that can be scheduled
    int *dp = (int*)malloc(n * sizeof(int));
    int *weights = (int*)malloc(n * sizeof(int));
    
    // Base case
    dp[0] = 1; // The first event can always be scheduled
    weights[0] = events[0].weight;
    
    // Dynamic programming to compute the maximum number of events that can be scheduled
    for (int i = 1; i < n; i++) {
        dp[i] = 1; // Initialize the maximum number of events that can be scheduled with the current event
        weights[i] = events[i].weight;
        
        // Iterate through previous events to find the maximum number of events that can be scheduled with the current event
        for (int j = 0; j < i; j++) {
            if (events[i].start >= events[j].end) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    weights[i] = weights[j] + events[i].weight;
                }
            }
        }
    }
    
    // Find the maximum number of events that can be scheduled
    int max = 0;
    *maxWeight = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max) {
            max = dp[i];
            *maxWeight = weights[i];
        }
    }
    
    // Free dynamically allocated memory
    free(dp);
    free(weights);
    
    return max;
}

int main() {
    int n;
    printf("Enter the number of events: ");
    scanf("%d", &n);
    
    // Allocate memory for events
    Event *events = (Event*)malloc(n * sizeof(Event));
    
    // Input events
    printf("Enter the events:\n");
    for (int i = 0; i < n; i++) {
        printf("Event %d (Name Start End Weight): ", i + 1);
        scanf(" %c %d %d %d", &events[i].name, &events[i].start, &events[i].end, &events[i].weight);
    }
    
    // Calculate the maximum number of events that can be scheduled
    int maxWeight;
    int max = maxEvents(events, n, &maxWeight);
    
    // Print the result
    printf("Maximum number of events that can be scheduled: %d\n", max);
    printf("Maximum weight when all events are scheduled: %d\n", maxWeight);
    
    // Free dynamically allocated memory
    free(events);
    
    return 0;
}