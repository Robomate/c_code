# c_code

compile with:

gcc -o test add_2vec.c

execute with:

./test

or all at once: 

Linux: gcc -o test add_2vec.c && ./test

Win: gcc -o test helloworld.c; ./test

### C Bootcamp

https://www.gribblelab.org/CBootCamp/

### Atlas(Blas)

link against libcblas library

gcc time_test_atlas_1.c -o time_test_atlas_1 -L /usr/lib/atlas-base -lcblas -lf77blas

### Openblas

gcc time_test_atlas_1.c -o time_test_atlas_1 -I /usr/include/openblas/include/ -L /usr/lib -lopenblas -lpthread -lgfortran

### References

http://www.icl.utk.edu/~mgates3/docs/blas.pdf

http://tzutalin.blogspot.de/2015/06/blas-atlas-openblas-and-mkl.html

https://stackoverflow.com/questions/36676449/lapack-blas-openblas-proper-installation-from-source-replace-system-libraries
