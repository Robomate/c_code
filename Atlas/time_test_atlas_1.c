#include <stdio.h>
#include <cblas.h>
#include <time.h>
/*
atlas is an good alternative BLAS implementation,
if Intel MKL is not available.
/
check path of atlas lib (from apt-get): dpkg -L libatlas-base-dev
/usr/lib/atlas-base/libf77blas -lf77blas //for from c fortran complilation
/usr/lib/atlas-base/atlas/libcblas -lcblas //for c compilation

gcc time_test_atlas_1.c -o time_test_atlas_1 -L /usr/lib/atlas-base -lcblas -lf77blas

https://michaellindon.github.io/lindonslog/programming/atlas-blas-lapack-linear-algebra-libraries/index.html
*/
 
// init main
int main(int argc, char** argv)
{
  double time_spent;
  double x_c[] = { 1, 1, 1 };

  int i, j, n, one;
  double coefficient;
  double x_f[] = { 1, 1, 1 };

  coefficient = 4.323;
  one = 1;
  n = 3;
  //***************************************
  //call cblas with:  -lcblas
  //***************************************
  clock_t tic = clock();
  cblas_dscal(3, 4.323, x_c, 1);
  clock_t toc = clock();

  // print calculations
  for (i = 0; i < 3; ++i)
    printf ("%f\n", x_c[i]);
  // print elapsed time
  time_spent = (double)(toc - tic) / CLOCKS_PER_SEC;
  printf("CBlas Elapsed: %f seconds\n", time_spent);

   //***************************************
   // call fortran from C -lf77blas
   //***************************************
  tic = clock();
  dscal_(&n, &coefficient, &x_f[0], &one);
  toc = clock();

  // print calculations
  for (i = 0; i < 3; ++i)
    printf ("%f\n", x_f[i]);
  // print elapsed time
  time_spent = (double)(toc - tic) / CLOCKS_PER_SEC;
  printf("Fortran Elapsed: %f seconds\n", time_spent);
 
  return 0;
}