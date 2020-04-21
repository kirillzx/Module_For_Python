#include "MatrixNorm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Matrix *allocate(int rows, int columns){
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->values = malloc(sizeof(double *)*rows);
    size_t i;

    matrix->rows = rows;
    matrix->columns = columns;

    for (i = 0; i < rows; i++){
        matrix->values[i] = malloc(sizeof(double)*columns);
    }

    return matrix;
}

void deallocate(Matrix *matrix){
    size_t i;

    for (i = 0; i < matrix->rows; i++){
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);

}

Matrix *matrixNormFrobenius(Matrix *matrix){
    int i, j;
    int n = matrix->rows;
    int l = matrix->columns;
    double sum;

    for(i=0; i<n; i++){
        for(j=0; j<l; j++){
            sum += matrix->values[i][j] * matrix->values[i][j];
        }
    }

    return sqrt(sum);
}

Matrix *matrixNormInfinity(Matrix *matrix){
    int i, j, m;
    int n = matrix->rows;
    int l = matrix->columns;
    double new[3] = {0};
    double sum, k;

    for(i=0; i<n; i++){
        sum = 0;
        for(j=0; j<l; j++){
            sum += fabs(matrix->values[i][j]);
        }
        new[i] = sum;
    }
    k = new[0];
    for(m=0; m<n; m++){
      if(new[m] > k){
        k = new[m];
      }
    }

    return k;
}

Matrix *matrixNormOne(Matrix *matrix){
    int i, j, m;
    int n = matrix->rows;
    int l = matrix->columns;
    double new[5] = {0};
    double sum, k;

    for(j=0; j<l; j++){
        sum = 0;
        for(i=0; i<n; i++){
            sum += fabs(matrix->values[i][j]);
        }
        new[j] = sum;
    }
    k = new[0];
    for(m=0; m<l; m++){
      if(new[m] > k){
        k = new[m];
      }
    }

    return k;
}

int main(){
    int n, l;
    Matrix *a;

    n = 3; // rows
    m = 5; // columns
    a = allocate(n, m);

    a->values[0][0] = 4.4; a->values[0][1] = 2.3; a->values[0][2] = 3.2; a->values[0][3] = 2.5; a->values[0][4] = -5.0;
    a->values[1][0] = 4.1; a->values[1][1] = 2.3; a->values[1][2] = 3.3; a->values[1][3] = 6.5; a->values[1][4] = -2.3;
    a->values[2][0] = 4.4; a->values[2][1] = 5.1; a->values[2][2] = 3.2; a->values[2][3] = 4.2; a->values[2][4] = -1.2;

    // printf("Euclidean norm: %3.3lf\n", NormEuclidean(x1, n));
    // printf("Manhattan distance: %3.3lf\n", NormManhattan(x1, n));
    // printf("Infinity norm: %3.3lf\n", NormInfifnity(x1, n));
    // printf("The Norm of the space Lp: %3.3lf\n", NormLp(x1, n, p));

    printf("The matrix norm one: %3.3lf\n", matrixNormOne(n, m, a));
    printf("The matrix norm infinity: %3.3lf\n", matrixNormInfinity(n, m, a));
    // printf("The matrix norm infinity: %3.3lf\n", matrixNormInfinity(4, 4, b));
    printf("The Frobenius matrix norm: %3.3lf\n", matrixNormFrobenius(n, m, a));
    deallocate(a);

    return 0;
}
