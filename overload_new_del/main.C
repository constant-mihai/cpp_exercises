/***************************************** 

* File Name : main.C

* Creation Date : 27-10-2016

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

* License :

******************************************/

/**
 *  Purpose:
 *
 */

// Standard C++
#include <iostream>
#include <memory>

using namespace std;

class Test_class {
    public:
        Test_class()
            : tmp(1) {};
        ~Test_class() { cout << "Destructed "<< endl ; }

        int get_tmp() { return tmp; }
        void print_tmp() {cout << tmp << endl; }
        void operator delete(void *ptr)             // Overwriting delete so we can print these logs.
        {
            if (!ptr) 
            {
                cout << "Missing pointer " << endl;
                return;
            }

            cout << "freeing memory " << endl; 
            free(ptr);
            Test_class* p = (Test_class*)ptr;
            p->print_tmp();
        }

        void operator delete[](void *ptr, size_t size) {
            if (!ptr) 
            {
                cout << "Missing pointer " << endl;
                return;
            }

            cout << "freeing array memory " << endl; 
            ::operator delete(ptr);

        }


    private:
        int tmp;
};


int main (int argc, char **argv) {
    //Test_class *tc = new Test_class();
    Test_class *tc = new Test_class[5];
    tc[1].print_tmp();
    delete[] tc;
    tc[1].print_tmp();

    return 1;

}
