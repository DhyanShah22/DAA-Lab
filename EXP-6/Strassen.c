#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int **allocate_matrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for(int i =0; i< n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

void deallocate_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

void standard_matrix_multiply(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void add_matrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract_matrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen_matrix_multiply(int **A, int **B, int **C, int n, int threshold) {
    if (n <= threshold) { 
        standard_matrix_multiply(A, B, C, n);
        return;
    }

    int newSize = n / 2;
    int **a11 = allocate_matrix(newSize);
    int **a12 = allocate_matrix(newSize);
    int **a21 = allocate_matrix(newSize);
    int **a22 = allocate_matrix(newSize);

    int **b11 = allocate_matrix(newSize);
    int **b12 = allocate_matrix(newSize);
    int **b21 = allocate_matrix(newSize);
    int **b22 = allocate_matrix(newSize);

    int **c11 = allocate_matrix(newSize);
    int **c12 = allocate_matrix(newSize);
    int **c21 = allocate_matrix(newSize);
    int **c22 = allocate_matrix(newSize);

    int **p1 = allocate_matrix(newSize);
    int **p2 = allocate_matrix(newSize);
    int **p3 = allocate_matrix(newSize);
    int **p4 = allocate_matrix(newSize);
    int **p5 = allocate_matrix(newSize);
    int **p6 = allocate_matrix(newSize);
    int **p7 = allocate_matrix(newSize);

    // Partitioning input matrices into quadrants
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newSize];
            a21[i][j] = A[i + newSize][j];
            a22[i][j] = A[i + newSize][j + newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newSize];
            b21[i][j] = B[i + newSize][j];
            b22[i][j] = B[i + newSize][j + newSize];
        }
    }

    subtract_matrices(b12, b22, p1, newSize); 
    strassen_matrix_multiply(a11, p1, c11, newSize, threshold); 

    add_matrices(a11, a12, p1, newSize); 
    strassen_matrix_multiply(p1, b22, c12, newSize, threshold); 

    add_matrices(a21, a22, p1, newSize); 
    strassen_matrix_multiply(p1, b11, c21, newSize, threshold); 

    subtract_matrices(b21, b11, p1, newSize); 
    strassen_matrix_multiply(a22, p1, c22, newSize, threshold); 

    add_matrices(a11, a22, p1, newSize); 
    add_matrices(b11, b22, p2, newSize); 
    strassen_matrix_multiply(p1, p2, c11, newSize, threshold); 

    subtract_matrices(a12, a22, p1, newSize); 
    add_matrices(b21, b22, p2, newSize); 
    strassen_matrix_multiply(p1, p2, c12, newSize, threshold); 

    subtract_matrices(a21, a11, p1, newSize); 
    add_matrices(b11, b12, p2, newSize); 
    strassen_matrix_multiply(p1, p2, c21, newSize, threshold); 

    add_matrices(a11, a12, p1, newSize); 
    add_matrices(b11, b12, p2, newSize); 
    add_matrices(a21, a22, p3, newSize); 
    strassen_matrix_multiply(p3, p2, c22, newSize, threshold); 

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }
    }

    deallocate_matrix(a11, newSize);
    deallocate_matrix(a12, newSize);
    deallocate_matrix(a21, newSize);
    deallocate_matrix(a22, newSize);
    deallocate_matrix(b11, newSize);
    deallocate_matrix(b12, newSize);
    deallocate_matrix(b21, newSize);
    deallocate_matrix(b22, newSize);
    deallocate_matrix(c11, newSize);
    deallocate_matrix(c12, newSize);
    deallocate_matrix(c21, newSize);
    deallocate_matrix(c22, newSize);
    deallocate_matrix(p1, newSize);
    deallocate_matrix(p2, newSize);
    deallocate_matrix(p3, newSize);
    deallocate_matrix(p4, newSize);
    deallocate_matrix(p5, newSize);
    deallocate_matrix(p6, newSize);
    deallocate_matrix(p7, newSize);
}

void fill_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100; 
        }
    }
}

void print_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int n; 
    int threshold; 
    clock_t start, end;
    double cpu_time_used;

    printf("Enter the size of matrices (n): ");
    scanf("%d", &n);

    printf("Enter the threshold value for Strassen's algorithm: ");
    scanf("%d", &threshold);

    int **A = allocate_matrix(n);
    int **B = allocate_matrix(n);
    int **C1 = allocate_matrix(n); 
    int **C2 = allocate_matrix(n); 

    fill_matrix(A, n);
    fill_matrix(B, n);

    start = clock();
    standard_matrix_multiply(A, B, C1, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for standard multiplication: %f seconds\n", cpu_time_used);

    start = clock();
    strassen_matrix_multiply(A, B, C2, n, threshold);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for Strassen's multiplication: %f seconds\n", cpu_time_used);

    deallocate_matrix(A, n);
    deallocate_matrix(B, n);
    deallocate_matrix(C1, n);
    deallocate_matrix(C2, n);

    return 0;
}