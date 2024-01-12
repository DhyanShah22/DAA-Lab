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
    int a[] = { 6,23,73,34,76,28,97 };  
    int n = sizeof(a) / sizeof(a[0]);  
    insert_Sort(a, n);  
    printf("\nAfter sorting array elements are - \n");
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d ", a[i]);
    }
  
    return 0;  
} 
