#include <stdio.h>  
  
void insert_Sort(int a[], int n)  
{  
    int i, j, temp;  
    for (i = 1; i < n; i++) {  
        temp = a[i];  
        j = i - 1;  
  
        while(j>=0 && temp <= a[j])   
        {    
            a[j+1] = a[j];     
            j = j-1;    
        }    
        a[j+1] = temp;    
    }  
}  
  

 
int main()  
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
    insert_Sort(arr, n);  
    printf("\nAfter sorting array elements are - \n");
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d ", arr[i]);
    }
  
    return 0;  
} 
