/*
 * Working with Strings
 * Linux: gcc -o string string_01.c && ./string
 * Windows: gcc -o string string_01.c; ./string
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 2048 //
#define NUMBER_OF_STRING 10
#define MAX_STRING_SIZE 2048



typedef struct ST_string { 
    char mystring_01[MAX_STRING_SIZE]; // (1) 1D char array
    char mystring_02[NUMBER_OF_STRING][MAX_STRING_SIZE]; // (2) 2D char array
    char *mystring_03; // (3) char pointer 
} STRING01;


int main(int argc, char* argv[]) {

    STRING01 string01;
    unsigned int i;

    // (1) 1D char array
    strcpy(string01.mystring_01, "This is mystring_01");
    printf("string01.mystring_01: %s.\n", string01.mystring_01);
    // (2) 2D char array
    strcpy(string01.mystring_02[0], "This is mystring_02");
    printf("string01.mystring_02: %s.\n", string01.mystring_02[0]);
    // (3) char pointer 
    string01.mystring_03 = "This is mystring_03";
    printf("string01.mystring_03: %s.\n", string01.mystring_03);

	return 0;
}