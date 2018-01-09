#include <stdio.h>

/*
check path of atlas lib (from apt-get): dpkg -L libatlas-base-dev
/usr/lib/atlas-base/libf77blas.a -lf77blas //for from c to fortran77 compilation
/usr/lib/atlas-base/atlas/libcblas.a -lcblas //for ansi C compilation

compile with:
gcc atlas_test_fortran.c -o atlas_test_fortran -L /usr/lib/atlas-base -lf77blas

https://michaellindon.github.io/lindonslog/programming/atlas-blas-lapack-linear-algebra-libraries/index.html
http://math-atlas.sourceforge.net/errata.html#LINK
*/

// init function protos
//dscal_(n, coefficient, x, one);
 
// init main
int main(int argc, char** argv)
{
  int i, j, n, one;
  double coefficient;
  double x[] = { 1, 1, 1 };
 
  coefficient = 4.323;
  one = 1;
  n = 3;
  // call fortran from C
  dscal_(&n, &coefficient, &x[0], &one);
 
  for (i = 0; i < 3; ++i)
    printf ("%f\n", x[i]);

  return 0;
}