#include<stdio.h>

void selection(int arr[], int n)  
{  
    int i, j, small;  
      
    for (i = 0; i < n-1; i++)     
    {  
        small = i;   
          
        for (j = i+1; j < n; j++)  
        if (arr[j] < arr[small])  
            small = j;  
 
    int temp = arr[small];  
    arr[small] = arr[i];  
    arr[i] = temp;  
    }  
} 

void main() 
{
    int arr[] = {1,35,78,23,42,12,56};

    int n = sizeof(arr)/sizeof(arr[0]);
    selection(arr, n);

    printf("The sorted array after selection sort is: \n");
    int i;
    for(i=0; i<n;i++)
    {
        printf("%d ", arr[i]);
    }
}