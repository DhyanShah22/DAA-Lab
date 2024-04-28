#include<stdio.h>
#include<stdbool.h>

#define N 8

bool isSafe(int board[N][N], int row, int col){
    int i,j;

    for(i=0; i<col; i++){
        if(board[row][i]){
            return false;
        }
    }

    for(i=row, j=col; i>=0 && j>=0; i--,j--){
        if(board[i][j]){
            return false;
        }
    }

    for(i=row, j=col; i <N && j>=0; i++,j--){
        if(board[i][j]){
            return false;
        }
    }
    return true;
}

bool SolveNQUtil(int board[N][N], int col){
    if(col >= N) {
        return true;
    }

    for(int i=0; i<N; i++){
        if(isSafe(board, i, col)){
            board[i][col] = 1;

                if(SolveNQUtil(board, col+1)){
                    return true;
                }
                board[i][col]=0;
        }
    }
    return false;
}

bool SolveNQ(){
    int board[N][N] = { {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}, };

    if(SolveNQUtil(board, 0) == false){
        printf("No solution possible");
        return false;
    }

    for(int i=0; i<N; i++){
        for(int j=0;j<N;j++){
            printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    SolveNQ();
    return 0;
}