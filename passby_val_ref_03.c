#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
/* Purpose: pass by value, pass by reference example
 * Exec: gcc -o test passby_val_ref_03.c && ./test
 * Links: https://www.codesdope.com/c-structure/
 * for malloc and linked lists:
 * https://www.cs.swarthmore.edu/~newhall/cs31/resources/C-structs_pointers.php
 * 20 pointer mistakes
 * https://www.acodersjourney.com/top-20-c-pointer-mistakes/
 * pass by value mit return
 * https://stackoverflow.com/questions/9653072/return-a-struct-from-a-function-in-c
 * https://stackoverflow.com/questions/2838038/c-programming-malloc-inside-another-function
 * 
 * array of structs (fixed length arrays)
 * https://stackoverflow.com/questions/13003275/malloc-struct-in-a-function-free-before-ending-program/13003512#13003512
 */ 

#define MAX_LEN 4 // max length of struct array

// define a struct
typedef struct ST_Employee {
    int id;
	char name[12];
    float income;
    int pos_keys[6];
} Employee;

typedef struct ST_Test {
    int id;
    float income;
} Test;


int add_employee(Employee emp) {
    /*
    *  Pass by value, no return
    * (use local copy of struct)
    */
    strcpy(emp.name,"Alice"); // assign string to pointer to struct instance
    emp.id = 10;    // assign int value to pointer to struct instance
    printf("\n\nPass by value:\n");
    printf("name: %s\n",emp.name);
    printf("id: %d\n",emp.id);

    return 0;
}

Employee add_employee2(Employee emp) {
    /*
    *  Pass by value, and direct return
    * (use local copy of struct)
    */
    strcpy(emp.name,"Will"); // assign string to struct 
    emp.id = 20;    // assign int value to struct
    printf("\n\nPass by value:\n");
    printf("name: %s\n",emp.name);
    printf("id: %d\n",emp.id);

    return emp; // return direct copy, pass by value
}

int add_employee3(Employee *emp) {
    /*
    *  Pass by reference 
    * (use original calling struct)
    * personPtr->age is equivalent to (*personPtr).age
    */
    strcpy(emp->name,"Bobby"); // assign string to pointer to struct instance
    emp->id = 30;    // assign int value to pointer to struct instance
    printf("\n\nPass by reference:\n");
    printf("name: %s\n",emp->name);
    printf("id: %d\n",emp->id);

    return 0;
}

int add_employee4(Employee *emp) {
    /*
    *  Pass by reference (pointer to pointer), Dynamic Memory Allocation (Heap) in Main
    * (use original calling struct)
    * personPtr->age is equivalent to (*personPtr).age
    */
   
    strcpy(emp->name,"Lori"); // assign string to pointer to struct instance
     emp->id = 70;    // assign int value to pointer to struct instance
    printf("\n\nDynamicMemory, malloc in main, Pass by reference:\n");
    printf("name: %s\n",emp->name);
    printf("id: %d\n",emp->id);

    return 0;
}

int add_employee5(Employee **emp) {
    /*
    *  Pass by reference (pointer to pointer), Dynamic Memory Allocation (Heap) in Function
    * (use original calling struct)
    * personPtr->age is equivalent to (*personPtr).age
    */
    Employee *emp2; // create new struct pointer
    emp2 = malloc(sizeof(Employee)); // reserve dynamic memory onto heap
    // check pointer is not NULL
    //     if(emp2 == NULL) {
    //         exit(1);   // should print out nice error msg first
    //     }
    assert(emp2 != NULL); // check pointer is not NULL
  
    strcpy(emp2->name,"John"); // assign string to pointer to struct instance
    emp2->id = 66;    // assign int value to pointer to struct instance
    printf("\n\nPass by reference (pointer to pointer), Dynamic Memory Allocation (Heap) in Function\n");
    printf("name: %s\n",emp2->name);
    printf("id: %d\n",emp2->id);

    *emp = emp2; // return by reference, assign heap value of pointer to pointer
    return 0;
}


Employee *add_employee6(Employee emp) {
    /*
    *  Pass by value, Dynamic Memory Allocation (Heap) in Function
    * (use original calling struct)
    * personPtr->age is equivalent to (*personPtr).age
    */
    Employee *emp2; // create new struct pointer
    emp2 = malloc(sizeof(Employee)); // reserve dynamic memory onto heap
    assert(emp2 != NULL); // check pointer is not NULL
    strcpy(emp2->name,"Sandy"); // assign string to pointer to struct instance
    emp2->id = 77;    // assign int value to pointer to struct instance

    printf("\n\nDynamicMemory, malloc in function, Pass by value\n");
    printf("name: %s\n",emp2->name);
    printf("id: %d\n",emp2->id);

    return emp2; // return directly by pointer type 
}

int main() {
    Employee first_emp; // create instance of struct
    // stores the memory address of an struct
    Employee *first_ptr; // create pointer to struct
    first_ptr = NULL; // init ptr with NULL
    if(first_ptr != NULL) {
        printf("Error, ptr not NULL");
    }
    first_ptr = &first_emp; // assign structure to pointer

    // size check, sizeof(mystruct_t) <= 2*sizeof(mystruct_t*)
    // size check, 44 > 16, use pass by refernce
    // https://stackoverflow.com/questions/30980759/when-should-i-pass-or-return-a-struct-by-value
    int size1 = sizeof(first_emp);
    int size2 = 2 * sizeof(first_ptr);
    printf("\n\nSize check:\n");
    printf("size struct: %d\n",size1);
    printf("2 x size struct pointer: %d\n",size2);


    // size check, 8 > 16, ok for pass by value
    Test test01;
    Test *testptr;
    int size3 = sizeof(test01);
    int size4 = 2 * sizeof(*testptr);
    printf("\n\nSize check:\n");
    printf("size struct: %d\n",size3);
    printf("2 x size struct pointer: %d\n",size4);

    ////////////////////////////////////////////////////
    // Start with function calls
    ////////////////////////////////////////////////////
    printf("\n\nEmployee Data init:\n");
    printf("name: %s\n",first_emp.name);
    printf("id: %d\n",first_emp.id);

    add_employee(first_emp);

    printf("\n\nPass by value, after original:\n");
    printf("name: %s\n",first_emp.name);
    printf("id: %d\n",first_emp.id);

    first_emp = add_employee2(first_emp);

    printf("\n\nPass by value, after original:\n");
    printf("name: %s\n",first_emp.name);
    printf("id: %d\n",first_emp.id);

    add_employee3(&first_emp);

    printf("\n\nPass by reference, after original:\n");
    printf("name: %s\n",first_emp.name);
    printf("id: %d\n",first_emp.id);

    // Pointer
    // Dynamic Memory Allocation

    Employee *first_emp2;
    first_emp2 = malloc(sizeof(Employee)); // reserve dynamic memory onto heap
    if(first_emp2 == NULL) {
        exit(1);   // should print out nice error msg first
    }
    add_employee4(first_emp2);
    
    printf("\n\nDynamicMemory, malloc in main, Pass by reference, after original:\n");
    printf("name: %s\n",first_emp2->name);
    printf("id: %d\n",first_emp2->id);
    free(first_emp2); // release memory
    first_emp2 = NULL; // make it a pointer to NULL

    // Dynamic Memory Allocation 2
    Employee *first_emp3;
    add_employee5(&first_emp3);

    printf("\n\nDynamicMemory, malloc in function, Pass by reference, after original:\n");
    printf("name: %s\n",first_emp3->name);
    printf("id: %d\n",first_emp3->id);

    free(first_emp3); // clean up heap memory
    first_emp3 = NULL; // make it a pointer to NULL

    // Dynamic Memory Allocation 3
    first_ptr = add_employee6(first_emp);

    printf("\n\nDynamicMemory, malloc in function, Pass by value, after original:\n");
    printf("name: %s\n",first_ptr->name);
    printf("id: %d\n",first_ptr->id);

    ///////////////////////////////////////////////////////
    // define a array of structs (fixed length array)
    ///////////////////////////////////////////////////////
    int i;
    int index;

    // Array of Structs, pass by reference
    Employee emp5[MAX_LEN]; // create new struct pointer
    i = 0;
    index = 0;
    add_employee3(&emp5[index++]);
    add_employee3(&emp5[index++]);
    add_employee3(&emp5[index++]);

    for (i = 0; i < index; i++) {
        printf("\n\nPass by reference after function\n");
        printf("idx: %d\n",i);
        printf("name: %s\n",emp5[i].name);
        printf("id: %d\n",emp5[i].id);
    }

    // Struct of Arrays with Dynamic Memory Allocation, pass by reference 
    Employee *emp4[MAX_LEN]; // create new struct pointer
    i = 0;
    index = 0;
    add_employee5(&emp4[index++]);
    add_employee5(&emp4[index++]);
    add_employee5(&emp4[index++]);

    for (i = 0; i < index; i++) {
        printf("\n\nPass by reference after function\n");
        printf("idx: %d\n",i);
        printf("name: %s\n",emp4[i]->name);
        printf("id: %d\n",emp4[i]->id);
        free(emp4[i]);
        printf("name: %s\n",emp4[i]->name);
        printf("id: %d\n",emp4[i]->id);
    }

    return 0;

}