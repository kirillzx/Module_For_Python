typedef struct Matrix{
    int rows;
    int columns;
    double **values;
} Matrix;

Matrix *matrix_allocate(int rows, int columns);
void matrix_deallocate(Matrix *matrix);
Matrix *matrixNormFrobenius(Matrix *matrix);
Matrix *matrixNormInfinity(Matrix *matrix);
Matrix *matrixNormOne(Matrix *matrix);
