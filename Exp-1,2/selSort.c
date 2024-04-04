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
  printf("Dhyan Shah\n");
  printf("22BCP269\n");
  int n;
  printf("Enter the size of the array: \n");
  scanf("%d", &n);
  int arr[n];
  printf("Enter 5 numbers\n");
  for(int i = 0 ; i<n; i++)
  {
    scanf("%d", &arr[i]);
  }  
  printf("The array before sorting is \n:");
  for(int i = 0; i < n; i++) {  
    printf("%d ", arr[i]);  
  } 
    selection(arr, n);

    printf("The sorted array after selection sort is: \n");
    int i;
    for(i=0; i<n;i++)
    {
        printf("%d ", arr[i]);
    }
}