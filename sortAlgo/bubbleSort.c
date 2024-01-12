#include<stdio.h>


int bubble(int arr[], int n)
{
    int i,j;
    for(i =0; i <n-1; i++)
    {
        for(j=0;j < n-i-1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];  
                arr[j] = arr[j + 1];  
                arr[j + 1] = temp;
            }  
        }
    }
}

void main() {  
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
  //int n = sizeof(arr)/sizeof(arr[0]);  
  bubble(arr, n);  
  printf("The Sorted array after bubble sort is: \n");  
  for (int i = 0; i < n; i++) {  
    printf("%d ", arr[i]);  
  }   
  printf("\n");
}  