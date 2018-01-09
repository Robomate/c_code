#include <stdio.h>
#include <cblas.h>
#include <time.h>
/*
This code multiplies a vector with a scalar coefficient
Comparison: cblas vs. fortran code.

atlas is an good alternative BLAS implementation,
if Intel MKL is not available.
/
check path of atlas lib (from apt-get): dpkg -L libatlas-base-dev
/usr/lib/atlas-base/libf77blas -lf77blas //for from c fortran complilation
/usr/lib/atlas-base/atlas/libcblas -lcblas //for c compilation

// compile with atlas:
gcc time_test_atlas_1.c -o time_test_atlas_1 -L /usr/lib/atlas-base -lcblas -lf77blas
// alternatively compile with openblas:
gcc time_test_atlas_1.c -o time_test_atlas_1 -I /usr/include/openblas/include/ -L /usr/lib -lopenblas -lpthread -lgfortran

run with ./time_test_atlas_1
https://michaellindon.github.io/lindonslog/programming/atlas-blas-lapack-linear-algebra-libraries/index.html
https://hunseblog.wordpress.com/2014/09/15/installing-numpy-and-openblas/
*/

// init function protos
extern void dscal_(int*, double*, double*, int*); // external fortran routine
 
// init main
int main(int argc, char** argv)
{
  double time_spent;
  int i, j;
  double x_c[] = { 1, 2, 3 };
  double x_f[] = { 1, 2, 3 };
  double coefficient = 4.323;
  int one = 1;
  int n = 3;
  //***************************************
  //call cblas with:  -lcblas
  //***************************************
  clock_t tic = clock();
  cblas_dscal(n, coefficient, x_c, one);
  clock_t toc = clock();

  // print calculations
  for (i = 0; i < n; ++i)
    printf ("%f\n", x_c[i]);
  // print elapsed time
  time_spent = (double)(toc - tic) / CLOCKS_PER_SEC;
  printf("CBlas Time Elapsed: %f seconds\n", time_spent);

   //***************************************
   // call fortran from C -lf77blas
   //***************************************&one
  tic = clock();
  dscal_(&n, &coefficient, &x_f[0], &one);
  toc = clock();

  // print calculations
  for (i = 0; i < n; ++i)
    printf ("%f\n", x_f[i]);
  // print elapsed time
  time_spent = (double)(toc - tic) / CLOCKS_PER_SEC;
  printf("Fortran Time Elapsed: %f seconds\n", time_spent);
 
  return 0;
}