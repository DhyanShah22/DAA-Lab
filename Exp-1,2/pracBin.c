#include<stdio.h>

int binSearch(int arr[], int low, int high, int key){
    while(low <= high){
        int mid = low + (high - low)/2;

        if(arr[mid] == key){
            return mid;
        }
        else if(arr[mid] < key){
            low = mid + 1;
        }
        else{
            high = mid -1;
        }
    }
    return -1;
}

void main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the number of the array in sorted order: ");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int key;
    printf("Enter the key to be searched: ");
    scanf("%d", &key);

    int result = binSearch(arr, 0, n-1,key);

    if(result == -1) {
        printf("Key not found\n");
    }
    else{
        printf("key find at result, %d \n", result);
    }
}