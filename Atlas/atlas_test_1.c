#include <stdio.h>
#include <cblas.h>
/*
check path of atlas lib (from apt-get): dpkg -L libatlas-base-dev
/usr/lib/atlas-base/libf77blas.a //for from c fortran complilation
/usr/lib/atlas-base/atlas/libblas.a //for c compilation


*/
 
// init main
int main(int argc, char** argv)
{
  int i;
  double x[] = { 1, 1, 1 };
  //call cblas
  cblas_dscal(3, 4.323, x, 1);
 
  for (i = 0; i < 3; ++i)
    printf ("%f\n", x[i]);
 
  return 0;
}