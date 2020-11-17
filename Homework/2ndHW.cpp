#include <stdio.h>
#define  MAX_TERMS 100
/*배열의 전체 요소를 표현하는 행렬로 변환하고 
변환된 행렬을 곱해서 출력하는 프로그램을 작성하여 제출하시오.
column= 세로 = 열
row= 가로 = 행*/
void MMatrix(struct SparseMatrix m1, struct SparseMatrix m2, int(*Matrix)[3]);
void printMatrix(int(*Matrix)[3]);
void printwholeMatrix(int(*Matrix1)[3], int(*Matrix2)[3], int(*Matrix3)[3]);

typedef struct {
    int row;
    int col;
    int value;
} element;
typedef struct SparseMatrix {
    element data[MAX_TERMS];
    int rows; // 행의 개수
    int cols; // 열의 개수
    int terms; // 항의 개수
} SparseMatrix;

int Matrix1[3][3] = { 0, };
int Matrix2[3][3] = { 0, };
int MatrixM[3][3] = { 0, };

SparseMatrix x1 = { {{1,1,5},{2,2,9}}, 3, 3, 2 };
SparseMatrix y1 = { {{0,0,5},{2,2,9}}, 3, 3, 2 };

SparseMatrix x2 = { {{0,0,1},{0,1,2},{0,2,3},{1,0,1},{1,1,2},{1,2,3},{2,0,1},{2,1,2},{2,2,3}}, 3, 3, 9 };
SparseMatrix y2 = { {{0,0,1},{0,1,1},{0,2,1},{1,0,1},{1,1,1},{1,2,1},{2,0,1},{2,1,1},{2,2,1}}, 3, 3, 9 };

SparseMatrix x3 = { {{0,0,7},{0,2,2},{1,2,3},{2,0,7}}, 3, 3, 4 };
SparseMatrix y3 = { {{0,1,5},{0,2,8},{1,2,4},{2,0,4},{2,2,1}}, 3, 3, 5 };
int main(void) {
    MMatrix(x1, y1, MatrixM);
    MMatrix(x2, y2, MatrixM);
    MMatrix(x3, y3, MatrixM);
}
void MMatrix(struct SparseMatrix m1, struct SparseMatrix m2, int(*Matrix)[3]){
    int Matrix1[3][3] = { 0, };
    int Matrix2[3][3] = { 0, };
    int MatrixM[3][3] = { 0, };
    for (int j = 0; j < m1.terms; j++) {
        Matrix1[m1.data[j].row][m1.data[j].col] = m1.data[j].value;
    }
    for (int k = 0; k < m2.terms; k++) {
        Matrix2[m2.data[k].row][m2.data[k].col] = m2.data[k].value;
    }//여기까지 전체요소행렬
    for (int x = 0; x < m1.rows; x++) {
        for (int y = 0; y < m1.cols; y++) {
            for (int k = 0; k < m1.cols; k++) {
                MatrixM[x][y] += Matrix1[x][k] * Matrix2[k][y]; //행렬의 곱
            }
        }
    }
    printwholeMatrix(Matrix1, Matrix2, MatrixM);
}
void printMatrix(int(*Matrix)[3]) {
    for (int x = 0 ; x < 3; x++){
        for (int y = 0; y < 3; y++) {
            printf("%2d ", Matrix[x][y]);
        }
        printf("\n");
    }
}
void printwholeMatrix(int(*Matrix1)[3], int(*Matrix2)[3], int(*Matrix3)[3]) {
    printMatrix(Matrix1);
    printf("---------\n");
    printMatrix(Matrix2);
    printf("=========\n");
    printMatrix(Matrix3);
    printf("\n\n");
}  
