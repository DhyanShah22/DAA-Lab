#include <stdio.h>
#include <stdlib.h>

void matrix_multiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else if (n == 2) {
        C[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
        C[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
        C[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
        C[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
    } else {
        int **A11, **A12, **A21, **A22;
        int **B11, **B12, **B21, **B22;
        int **C11, **C12, **C21, **C22;

        // Allocate memory for submatrices
        A11 = (int **)malloc(n/2 * sizeof(int *));
        A12 = (int **)malloc(n/2 * sizeof(int *));
        A21 = (int **)malloc(n/2 * sizeof(int *));
        A22 = (int **)malloc(n/2 * sizeof(int *));
        B11 = (int **)malloc(n/2 * sizeof(int *));
        B12 = (int **)malloc(n/2 * sizeof(int *));
        B21 = (int **)malloc(n/2 * sizeof(int *));
        B22 = (int **)malloc(n/2 * sizeof(int *));
        C11 = (int **)malloc(n/2 * sizeof(int *));
        C12 = (int **)malloc(n/2 * sizeof(int *));
        C21 = (int **)malloc(n/2 * sizeof(int *));
        C22 = (int **)malloc(n/2 * sizeof(int *));

        for (int i = 0; i < n/2; i++) {
            A11[i] = (int *)malloc(n/2 * sizeof(int));
            A12[i] = (int *)malloc(n/2 * sizeof(int));
            A21[i] = (int *)malloc(n/2 * sizeof(int));
            A22[i] = (int *)malloc(n/2 * sizeof(int));
            B11[i] = (int *)malloc(n/2 * sizeof(int));
            B12[i] = (int *)malloc(n/2 * sizeof(int));
            B21[i] = (int *)malloc(n/2 * sizeof(int));
            B22[i] = (int *)malloc(n/2 * sizeof(int));
            C11[i] = (int *)malloc(n/2 * sizeof(int));
            C12[i] = (int *)malloc(n/2 * sizeof(int));
            C21[i] = (int *)malloc(n/2 * sizeof(int));
            C22[i] = (int *)malloc(n/2 * sizeof(int));
        }

        for (int i = 0; i < n/2; i++) {
            for (int j = 0; j < n/2; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n/2];
                A21[i][j] = A[i + n/2][j];
                A22[i][j] = A[i + n/2][j + n/2];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + n/2];
                B21[i][j] = B[i + n/2][j];
                B22[i][j] = B[i + n/2][j + n/2];
            }
        }

        matrix_multiply(A11, B11, C11, n/2);
        matrix_multiply(A12, B21, C12, n/2);
        matrix_multiply(A11, B12, C21, n/2);
        matrix_multiply(A12, B22, C22, n/2);

        for (int i = 0; i < n/2; i++) {
            for (int j = 0; j < n/2; j++) {
                C[i][j] = C11[i][j];
                C[i][j + n/2] = C12[i][j];
                C[i + n/2][j] = C21[i][j];
                C[i + n/2][j + n/2] = C22[i][j];
            }
        }
        for (int i = 0; i < n/2; i++) {
            free(A11[i]);
            free(A12[i]);
            free(A21[i]);
            free(A22[i]);
            free(B11[i]);
            free(B12[i]);
            free(B21[i]);
            free(B22[i]);
            free(C11[i]);
            free(C12[i]);
            free(C21[i]);
            free(C22[i]);
        }
        free(A11);
        free(A12);
        free(A21);
        free(A22);
        free(B11);
        free(B12);
        free(B21);
        free(B22);
        free(C11);
        free(C12);
        free(C21);
        free(C22);
    }
}

int main() {
    int n;
    printf("Dhyan Shah\n22BCP269\n");
    printf("Enter the size of the matrices (n x n): ");
    scanf("%d", &n);

    int **A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    matrix_multiply(A, B, C, n);

    printf("Result matrix C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
