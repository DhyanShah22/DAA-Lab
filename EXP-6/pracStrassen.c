#include<stdio.h>
#include<stdlib.h>

int **allocateMemory(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for(int i =0;i<n;i++){
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int n){
    for (int i =0; i<n; i++){
        free(matrix[i]);
    }
    free(matrix);
}

void addMatrix(int **A, int **B, int **C, int n){
    for(int i =0; i<n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrix(int **A, int **B, int **C, int n){
    for(int i =0; i<n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassenMultiply(int **A, int **B, int **C, int n){
    if(n==1){
        C[0][0] = A[0][0] * B[0][0];
        return ;
    }

    int **A11, **A12, **A21, **A22;
    int **B11, **B12, **B21, **B22;
    int **C11, **C12, **C21, **C22;
    int **P1, **P2, **P3, **P4, **P5, **P6, **P7;
    int **temp1, **temp2;

    int newSize = n/2;

    A11=allocateMemory(newSize);
    A12=allocateMemory(newSize);
    A21= allocateMemory(newSize);
    A22=allocateMemory(newSize);
    B11=allocateMemory(newSize);
    B12= allocateMemory(newSize);
    B21= allocateMemory(newSize);
    B22=allocateMemory(newSize);
    C11= allocateMemory(newSize);
    C12= allocateMemory(newSize);
    C21= allocateMemory(newSize);
    C22=allocateMemory(newSize);
    P1= allocateMemory(newSize);
    P2=allocateMemory(newSize);
    P3= allocateMemory(newSize);
    P4= allocateMemory(newSize);
    P5=allocateMemory(newSize);
    P6= allocateMemory(newSize);
    P7=allocateMemory(newSize);
    temp1= allocateMemory(newSize);
    temp2=allocateMemory(newSize);

    for(int i = 0; i<newSize; i++){
        for(int j=0; j<newSize; j++){
            A11[i][j] = B[i][j];
            A12[i][j] = B[i][j + newSize];
            A21[i][j] = B[i+newSize][j];
            A22[i][j] = B[i+newSize][j+newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i+newSize][j];
            B22[i][j] = B[i+newSize][j+newSize];

        }
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

    addMatrix(P1, P4, temp1, newSize);
    subtractMatrix(temp1, P5, temp2, newSize);
    addMatrix(temp2, P7, C11, newSize);

    addMatrix(P3, P5, C12, newSize);

    addMatrix(P2, P4, C21, newSize);

    addMatrix(P1, P3, temp1, newSize);
    subtractMatrix(temp1, P2, temp2, newSize);
    addMatrix(temp2, P6, C22, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

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
}

void printMatrix(int **Matrix, int n){
    for (int i =0; i<n; i++){
        for (int j=0;j<n;j++){
            printf("%d", Matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int n;
    printf("Enter the size of the matrix(n * n)\n");
    scanf("%d", &n);

    int **A = allocateMemory(n);
    int **B = allocateMemory(n);
    int **C = allocateMemory(n);

    printf("Enter the elements of A: \n");
    for(int i =0; i<n; i++){
        for (int j=0;j<n;j++){
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter the elements of B: \n");
    for(int i =0; i<n; i++){
        for (int j=0;j<n;j++){
            scanf("%d", &B[i][j]);
        }
    }

    strassenMultiply(A,B,C,n);

    printf("Result Matrix\n");
    printMatrix(C,n);

    freeMatrix(A,n);
    freeMatrix(B,n);
    freeMatrix(C,n);
    
    return 0;


}