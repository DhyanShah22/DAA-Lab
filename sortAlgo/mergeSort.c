    #include <stdio.h>  
      
    void merge(int a[], int beg, int mid, int end)    
    {    
        int i, j, k;  
        int n1 = mid - beg + 1;    
        int n2 = end - mid;    
          
        int LeftArray[n1], RightArray[n2];   
          
        for (int i = 0; i < n1; i++)    
        LeftArray[i] = a[beg + i];    
        for (int j = 0; j < n2; j++)    
        RightArray[j] = a[mid + 1 + j];    
          
        i = 0;  
        j = 0;   
        k = beg;   
          
        while (i < n1 && j < n2)    
        {    
            if(LeftArray[i] <= RightArray[j])    
            {    
                a[k] = LeftArray[i];    
                i++;    
            }    
            else    
            {    
                a[k] = RightArray[j];    
                j++;    
            }    
            k++;    
        }    
        while (i<n1)    
        {    
            a[k] = LeftArray[i];    
            i++;    
            k++;    
        }    
          
        while (j<n2)    
        {    
            a[k] = RightArray[j];    
            j++;    
            k++;    
        }    
    }    
      
    void mergeSort(int a[], int beg, int end)  
    {  
        if (beg < end)   
        {  
            int mid = (beg + end) / 2;  
            mergeSort(a, beg, mid);  
            mergeSort(a, mid + 1, end);  
            merge(a, beg, mid, end);  
        }  
    }  
      
    void printArray(int a[], int n)  
    {  
        int i;  
        for (i = 0; i < n; i++)  
            printf("%d ", a[i]);  
        printf("\n");  
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
        mergeSort(arr, 0, n - 1);  
        printf("After sorting array elements are - \n");  
        printArray(arr, n);  
        return 0;  
    }  