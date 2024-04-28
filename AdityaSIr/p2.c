#include<stdio.h>

int totalprofit = 0;
int array[10];
int size = sizeof(array) / sizeof(array[0]);
int visited[10];
int k = 0;
int count = 0;

void maxprofit(int array[10]) {
    if (count == 5) {
        return;
    }
    count += 1;
    int max_profit = 0;
    int first, second;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (!visited[i] && !visited[j]) {
                if (max_profit < array[j] - array[i]) {
                    max_profit = array[j] - array[i];
                    first = i;
                    second = j;
                }
            }
        }
    }
    totalprofit += max_profit;
    visited[first] = 1;  // Mark the first day as visited
    visited[second] = 1; // Mark the second day as visited
    maxprofit(array);
}

int main() {
    int array[10] = {5,10,3,8,12,6,15,7,9,11};
    for (int i = 0; i < 10; i++) {
        visited[i] = 0;
    }
    maxprofit(array);
    printf("%d", totalprofit);

    return 0;
}