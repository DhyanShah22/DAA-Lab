#include<stdio.h>
#include<stdlib.h>

void merge(int arr[], int beg, int mid, int end)
{
    int i, j, k;
    int n1 = mid - beg+1;
    int n2 = end - mid;

    int LeftArray[n1], RightArray[n2];   

    for (int i = 0; i < n1; i++)    
        LeftArray[i] = arr[beg + i];    
        for (int j = 0; j < n2; j++)    
        RightArray[j] = arr[mid + 1 + j];    
          
        i = 0;  
        j = 0;   
        k = beg; 

        while(i<n1 && j<n2){
            if(LeftArray[i] <= RightArray[j]){
                arr[k] = LeftArray[i];
                i++;
            }
            else {
                arr[k] = RightArray[j];
                j++;
            }
            k++;
        }

         while (i<n1)    
        {    
            arr[k] = LeftArray[i];    
            i++;    
            k++;    
        }    
          
        while (j<n2)    
        {    
            arr[k] = RightArray[j];    
            j++;    
            k++;    
        }
        
}

void mergeSort(int arr[], int l, int r) {  
    if (l < r) {         
        int m = l+(r-l)/2;  
        mergeSort(arr, l, m);
        mergeSort(arr,m+1,r);
        merge(arr, l, m, r); 
    }
}

void main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *arr  = (int*)malloc(sizeof(int)*n); 

    printf("Enter the array elements: \n");
    for(int i = 0; i<n; i++){
        scanf( "%d", &arr[i]);
    }

    mergeSort(arr, 0, n-1);
    printf("\n\nThe sorted array is : \n");
    for(int i=0; i<n; i++){
        printf("%d\n", arr[i]);
    }
}