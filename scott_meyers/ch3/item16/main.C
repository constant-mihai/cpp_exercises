/***************************************** 

* File Name : main.C

* Creation Date : 03-12-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/



/*
 * Purpose : To show difference between new/new [] and delete/delete []
 *
 */

// C++ standard
#include <iostream>

using namespace std;

typedef string Address_lines[4]; // don't do this.

int main(int argc, char** argv)
{
    string *s1 = new string;
    string *s2 = new string[100];

    string *pal = new Address_lines; // Actually a pointer to an array.

    delete s1;
    delete s2;  // wrong, delete [] needed.
    delete pal; // wrong, delete [] needed
}
