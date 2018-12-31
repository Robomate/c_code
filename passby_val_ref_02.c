#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* Purpose: pass by value, pass by reference example
 * Exec: gcc -o test passby_val_ref_02.c && ./test
 * Links: https://www.codesdope.com/c-structure/
 * for malloc and linked lists:
 * https://www.cs.swarthmore.edu/~newhall/cs31/resources/C-structs_pointers.php
 * 20 pointer mistakes
 * https://www.acodersjourney.com/top-20-c-pointer-mistakes/
 * pass by value mit return
 * https://stackoverflow.com/questions/9653072/return-a-struct-from-a-function-in-c
 */ 
typedef struct ST_Employee {
    int id;
	char name[12];
    float income;
    int pos_keys[6];
} Employee;

int add_employee(Employee emp) {
    /*
    *  Pass by value
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
    *  Pass by value
    * (use local copy of struct)
    */
    Employee emp_ret; // for return

    strcpy(emp.name,"Will"); // assign string to pointer to struct instance
    emp.id = 20;    // assign int value to pointer to struct instance
    printf("\n\nPass by value:\n");
    printf("name: %s\n",emp.name);
    printf("id: %d\n",emp.id);

    emp_ret = emp; // return copy
    return emp_ret;
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

int main() {
    Employee first_emp; // create instance of struct
    // stores the memory address of an struct
    Employee *first_ptr; // create pointer to struct
    first_ptr = NULL; // init ptr with NULL
    if(first_ptr != NULL) {
        printf("Error, ptr not NULL");
    }
    first_ptr = &first_emp; // assign structure to pointer

    // size check ??
    // https://stackoverflow.com/questions/30980759/when-should-i-pass-or-return-a-struct-by-value
    int size1 = sizeof(first_emp);
    int size2 = 2 * sizeof(first_ptr);
    printf("\n\nSize check:\n");
    printf("size struct: %d\n",size1);
    printf("size struct pointer: %d\n",size2);
    ////////////////////////////////////////////////////
    // Start 
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

    return 0;

}