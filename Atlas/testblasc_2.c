#include <stdio.h>
#include <cblas.h>
/*
atlas is an good alternative BLAS implementation,
if Intel MKL is not available.
/
check path of atlas lib (from apt-get): dpkg -L libatlas-base-dev
/usr/lib/atlas-base/libf77blas -lf77blas //for from c fortran complilation
/usr/lib/atlas-base/atlas/libcblas -lcblas //for c compilation

gcc testblasc.c -o testblas -L/usr/lib -lcblas
or:
gcc testblasc.c -o testblas -L /usr/lib/atlas-base -lcblas

https://michaellindon.github.io/lindonslog/programming/atlas-blas-lapack-linear-algebra-libraries/index.html
*/
 
// init main
int main(int argc, char** argv)
{
  int i;
  double x[] = { 1, 1, 1 };
  //call with:  -lcblas
  cblas_dscal(3, 4.323, x, 1);
 
  for (i = 0; i < 3; ++i)
    printf ("%f\n", x[i]);
 
  return 0;
}