#include<stdio.h>
/**
 * Function adds to vectors a and b
 * and returns c as an array using parameter.
 * http://codeforwin.org/2017/12/pass-return-array-function-c.html#pass-array-1d
 */ 

// define globals
#define VEC_LEN 3

// init function declarations
void fill_vec(double vec[], double scalar);
void add_2vec(double c[],double a[],double b[]);
void print_vec(double p[]);

// init main
int main(int argc, char** argv)
{
  int i;  
  double a[VEC_LEN]; // input a
  double b[VEC_LEN]; // input b
  double c[VEC_LEN]; // output c

  //data preparing (fill vec a and b with numbers)
  fill_vec(a, 2.0);
  print_vec(a);
  fill_vec(b, 3.0);
  print_vec(b);
  // add two vectors c = a + b
  add_2vec(c,a,b);
  print_vec(c);
  return 0;
}

// init functions
void fill_vec( double vec[], double scalar)
{
    int i;
    for( i=0; i<VEC_LEN; i++)
    {
        vec[i]=scalar + i;
    }
}

void add_2vec(double c[],double a[],double b[])
{   
    int i;
    for (i = 0; i < VEC_LEN; ++i)
    {
        c[i] = a[i] + b[i];
    }
}

void print_vec(double vec[])
{   
    int i;
    printf("vector elements :\n");
    for (i = 0; i < VEC_LEN; ++i)
    { 
        printf(" %3.2lf\n", vec[i]);
    }
}
