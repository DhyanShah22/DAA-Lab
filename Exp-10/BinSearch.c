#include <stdio.h>

int findPeakEntry(int A[], int n) {
    int low = 0;
    int high = n - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;
        if (A[mid] < A[mid + 1] && A[mid] > A[mid-1]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}

int main() {
    int n;
    printf("Enter the number of entries in the array: ");
    scanf("%d", &n);

    int A[n];
    printf("Enter the array elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    int peak_index = findPeakEntry(A, n);
    printf("Peak entry index: %d\n", peak_index);
    printf("Peak entry value: %d\n", A[peak_index]);

    return 0;
}
