/***************************************** 

* File Name : main.C

* Purpose : 

* Creation Date : 23-10-2014 20-12-2008

* Last Modified : Tue 04 Nov 2014 04:02:15 PM CET

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/

/*
*http://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable-in
* Just messing around with references.
*/

#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


using namespace std;

/*
 * A pointer can be reassigned
 */
void pointer_reasignment()
{
    int x = 5;
    int y = 6;
    int *p;
    p =  &x;
    p = &y;
    *p = 10;
    assert(x == 5);
    assert(y == 10);
}

/*
 * A refference cannot be reassigned
 * Must be assigned at init.
 */
void reference_initialization()
{
  int x = 5;
  int &r = x;
  assert(r == 5);
}

/*
 * TODO read standard for qoute here
 */
void memory_addresses()
{
    int x = 0;
    int &r = x;
    int *p = &x;
    int *p2 = &r;
    assert(p == p2);
}

void indirection_level()
{
    int x = 0;
    int y = 0;
    int *p = &x;
    int *q = &y;
    int **pp = &p;
    pp = &q;//*pp = q
    **pp = 4;
    assert(y == 4);
    assert(x == 0);
}

void null_assignment()
{
    int *p = NULL;
//    int &r = NULL; <--- compiling error
    (void)p;
}

void pointer_arithmetic()
{
    int a[3] = {1, 2, 3};
    int &r = *a;

    assert(&r == a);
    assert(r == 1);
    assert(*(a+1) == 2);
    assert((&r)+1 /*Hop 4 bytes further. as in: over the value at a+0*/ == a+1);
}

void dereferencing()
{
    int n = 3;
    int &r = n;
    int *p = &n;

    assert(*p == r);
}

void pointer_array()
{
    int a[3] = {1, 2, 3};
    int *p1 = a+0, *p2 = a+1, *p3 = a+2;
    int &r1 = *(a+0), &r2 = *(a+1), &r3 = *(a+2);
    int *ap[3] = {p1, p2, p3};
    int *ar[3] = {&r1, &r2, &r3};

    for (int i=0;i<3;i++) assert(*(ap[i]) == a[i]);
    for (int i=0;i<3;i++) assert(ar[i] == &(a[i]));
}

void tmp_dereferencing()
{
    const int &x = int(12); //legal C++
//    int *y = &int(12); //illegal to dereference a temporary.
   (void)x;
}

/* Printing a constant string */
void print(const string& s)
{
    cout << s << "\n";
}

int main(int argc, char** argv)
{
    string s("const_string");
    print(s);

    char buf[50];
    sprintf(buf,"%ld", 0);
    printf("buf len %d\n",strlen(buf));


    pointer_reasignment();
    reference_initialization();
    memory_addresses();
    indirection_level();
    null_assignment();
    pointer_arithmetic();
    dereferencing();
    pointer_array();
    tmp_dereferencing();

    return 1;
}
