#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix of size n x n
int **allocateMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free memory allocated for a matrix
void freeMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to add two matrices
void addMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtractMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Function to perform Strassen multiplication recursively
void strassenMultiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int **A11, **A12, **A21, **A22;
    int **B11, **B12, **B21, **B22;
    int **C11, **C12, **C21, **C22;
    int **P1, **P2, **P3, **P4, **P5, **P6, **P7;
    int **temp1, **temp2;

    int newSize = n / 2;

    // Allocate memory for submatrices
    A11 = allocateMatrix(newSize);
    A12 = allocateMatrix(newSize);
    A21 = allocateMatrix(newSize);
    A22 = allocateMatrix(newSize);
    B11 = allocateMatrix(newSize);
    B12 = allocateMatrix(newSize);
    B21 = allocateMatrix(newSize);
    B22 = allocateMatrix(newSize);
    C11 = allocateMatrix(newSize);
    C12 = allocateMatrix(newSize);
    C21 = allocateMatrix(newSize);
    C22 = allocateMatrix(newSize);
    P1 = allocateMatrix(newSize);
    P2 = allocateMatrix(newSize);
    P3 = allocateMatrix(newSize);
    P4 = allocateMatrix(newSize);
    P5 = allocateMatrix(newSize);
    P6 = allocateMatrix(newSize);
    P7 = allocateMatrix(newSize);
    temp1 = allocateMatrix(newSize);
    temp2 = allocateMatrix(newSize);

    // Divide matrices A and B into submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculate intermediate matrices P1 to P7
    addMatrix(A11, A22, temp1, newSize);
    addMatrix(B11, B22, temp2, newSize);
    strassenMultiply(temp1, temp2, P1, newSize);

    addMatrix(A21, A22, temp1, newSize);
    strassenMultiply(temp1, B11, P2, newSize);

    subtractMatrix(B12, B22, temp1, newSize);
    strassenMultiply(A11, temp1, P3, newSize);

    subtractMatrix(B21, B11, temp1, newSize);
    strassenMultiply(A22, temp1, P4, newSize);

    addMatrix(A11, A12, temp1, newSize);
    strassenMultiply(temp1, B22, P5, newSize);

    subtractMatrix(A21, A11, temp1, newSize);
    addMatrix(B11, B12, temp2, newSize);
    strassenMultiply(temp1, temp2, P6, newSize);

    subtractMatrix(A12, A22, temp1, newSize);
    addMatrix(B21, B22, temp2, newSize);
    strassenMultiply(temp1, temp2, P7, newSize);

    // Calculate submatrices C11 to C22
    addMatrix(P1, P4, temp1, newSize);
    subtractMatrix(temp1, P5, temp2, newSize);
    addMatrix(temp2, P7, C11, newSize);

    addMatrix(P3, P5, C12, newSize);

    addMatrix(P2, P4, C21, newSize);

    addMatrix(P1, P3, temp1, newSize);
    subtractMatrix(temp1, P2, temp2, newSize);
    addMatrix(temp2, P6, C22, newSize);

    // Combine submatrices into the result matrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free memory
    freeMatrix(A11, newSize);
    freeMatrix(A12, newSize);
    freeMatrix(A21, newSize);
    freeMatrix(A22, newSize);
    freeMatrix(B11, newSize);
    freeMatrix(B12, newSize);
    freeMatrix(B21, newSize);
    freeMatrix(B22, newSize);
    freeMatrix(C11, newSize);
    freeMatrix(C12, newSize);
    freeMatrix(C21, newSize);
    freeMatrix(C22, newSize);
    freeMatrix(P1, newSize);
    freeMatrix(P2, newSize);
    freeMatrix(P3, newSize);
    freeMatrix(P4, newSize);
    freeMatrix(P5, newSize);
    freeMatrix(P6, newSize);
    freeMatrix(P7, newSize);
    freeMatrix(temp1, newSize);
    freeMatrix(temp2, newSize);
}

// Function to print a matrix
void printMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the size of the matrices (n x n): ");
    scanf("%d", &n);

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

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

    strassenMultiply(A, B, C, n);

    printf("Result matrix C:\n");
    printMatrix(C, n);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}
