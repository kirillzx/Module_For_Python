#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double a[3][5]={
    {4.4, 2.3, 3.2, 2.5, -5.0},
    {4.1, 2.3, 3.3, 6.5, -2.3},
    {4.4, 5.1, 3.2, 4.2, -1.2}
};

double b[4][4]={
    {4.2, 2.3, 3.2, 6.6},
    {3.4, 2.3, 3.2, 3.2},
    {4.4, 4.1, 1.2, 6.3},
    {4.1, 2.3, 3.2, 5.5}
};

double NormEuclidean(void *f, int n){
  double *x;
  double res = 0;
  int length;
  x = f;
  for(int i=0; i<n; i++){
    res +=  x[i]*x[i];
  }
  return sqrt(res);
}

double NormManhattan(void *f, int n){
  double *x;
  double res = 0;
  int length;
  x = f;
  for(int i=0; i<n; i++){
    res +=  fabs(x[i]);
  }
  return res;
}

double NormLp(void *f, int n, int p){
  double *x;
  double res = 0;
  int length;
  x = f;
  for(int i=0; i<n; i++){
    res +=  pow(fabs(x[i]), p);
  }
  return pow(res, 1/p);
}

double NormInfifnity(void *f, int n){
  double *x, k;
  double res = 0;
  int length;
  x = f;
  k = x[0];

  for(int i=0; i<n; i++){
    if(fabs(x[i]) > fabs(k)){
      k = x[i];
    }
  }

  return k;
}

// double matrixNormOne(void *f, int n, int l)
// {
//     double *a;
//     double sum, k;
//     int i, j, m;
//     double new[5] = {0};
//     a = f;
//
//     for(j=0; j<l; j++){
//         sum = 0;
//         for(i=0; i<n; i++){
//             sum += fabs(a[i][j]);
//         }
//         new[j] = sum;
//     }
//     k = new[0];
//     for(m=0; m<l; m++){
//       if(new[m] > k){
//         k = new[m];
//       }
//     }
//
//     return k;
// }

double matrixNormInfinity(void *f, int n, int l)
{
    double *a;
    double sum, k;
    int i, j, m;
    double new[3] = {0};
    a = f;

    double c[3][5]={
        {4.4, 2.3, 3.2, 2.5, -5.0},
        {4.1, 2.3, 3.3, 6.5, -2.3},
        {4.4, 5.1, 3.2, 4.2, -1.2}
    };
    for(i=0; j<n; i++){
        sum = 0;
        for(j=0; j<l; j++){
            sum += fabs(c[i][j]);
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

int main()
{
    int n = 3;
    int p = 4;
    double x1[3] = {1, 2, -2};

    // printf("Euclidean norm: %3.3lf\n", NormEuclidean(x1, n));
    // printf("Manhattan distance: %3.3lf\n", NormManhattan(x1, n));
    // printf("Infinity norm: %3.3lf\n", NormInfifnity(x1, n));
    // printf("The Norm of the space Lp: %3.3lf\n", NormLp(x1, n, p));

    // printf("%f\n", matrixNormOne(a, 3, 5));
    printf("%f\n", matrixNormInfinity(a, 3, 5));
    return 0;
}
