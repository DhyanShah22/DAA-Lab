#include<stdio.h>
#include<stdlib.h>


void minheapify(int arr[], int n, int i){
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    if (left < n && arr[smallest] > arr[left]){
        smallest=left;
    }
    
    if (right < n && arr[right] < arr[smallest]){
        smallest=right;
    }

    if (smallest!=i)
    {
        int  temp = arr[i];
        arr[i]=arr[smallest];
        arr[smallest]=temp;
        minheapify(arr,n,smallest);
    }
}
void buildMinHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        minheapify(arr, n, i);
    }
} 
void heapSort(int arr[], int n) {
    buildMinHeap(arr, n);
    for (int i = n-1; i >=0; i--)
    {
       int temp = arr[0];
       arr[0] = arr[i];
       arr[i] = temp;
       minheapify(arr,i,0);
    }
    
}

int main(){
    int n;
    printf("Name: Dhyan Shah\nRoll No: 22BCP269\n");
    printf("Enter the size of array:");
    scanf("%d",&n);
    int arr[n]; 
    printf("Enter the integers:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        }
    
    heapSort(arr ,n);
    printf("\nThe sorted array is :\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}