    #include <stdio.h>  
      
    int getMax(int a[], int n) {  
       int max = a[0];  
       for(int i = 1; i<n; i++) {  
          if(a[i] > max)  
             max = a[i];  
       }  
       return max;  
    }  
      
    void countingSort(int a[], int n, int place)   
    {  
      int output[n + 1];  
      int count[10] = {0};    
      
      for (int i = 0; i < n; i++)  
        count[(a[i] / place) % 10]++;  
          
      for (int i = 1; i < 10; i++)  
        count[i] += count[i - 1];  
      
      for (int i = n - 1; i >= 0; i--) {  
        output[count[(a[i] / place) % 10] - 1] = a[i];  
        count[(a[i] / place) % 10]--;  
      }  
      
      for (int i = 0; i < n; i++)  
        a[i] = output[i];  
    }  
      
    void radixsort(int a[], int n) {  
       
      int max = getMax(a, n);  
      
      for (int place = 1; max / place > 0; place *= 10)  
        countingSort(a, n, place);  
    }  
      
    void printArray(int a[], int n) {  
      for (int i = 0; i < n; ++i) {  
        printf("%d  ", a[i]);  
      }  
      printf("\n");  
    }  
      
  int main() {  
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
      radixsort(arr, n);  
      printf("After applying Radix sort, the array elements are - \n");  
      printArray(arr, n);  
    }  