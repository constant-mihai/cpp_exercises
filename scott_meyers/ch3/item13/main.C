/***************************************** 

* File Name : main.C

* Creation Date : 02-12-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/

// Standard C++
#include <iostream>
#include <memory>

/*
 * Purpose : Use objects to manage resources
 *
 */

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

    private:
        int tmp;
};

Test_class* allocate_mem(Test_class **ptc)
{
    Test_class *tc = new Test_class();
    *ptc = tc;
    return tc;
}

void auto_ptr_function()
{
    Test_class *ptc = 0;
    auto_ptr<Test_class> p(allocate_mem(&ptc)); // auto_ptr will call the destructor and free the memory when the function ends.

    auto_ptr<Test_class> p_copy(p); // this destroys p 

    
    //p->get_tmp();     // This will seg fault. auto_ptr nulls the other pointer on copy.
}

void shared_ptr_function()
{
    Test_class *ptc = 0;
    shared_ptr<Test_class> p(allocate_mem(&ptc));       // auto_count = 1;

    shared_ptr<Test_class> p_copy(p);   // auto_count = 2;

    p_copy = 0;             // First reference is free'd, auto_count = 1;
    ptc->print_tmp();       // This will print 1. Object still exists in memory.

    p.reset();              // auto_count = 0, object destroyed.
    ptc->print_tmp();       // Prints something, not 1 (default tmp). Memory is free'd but pointer is not nulled.
                            // WHEN USING SHARED_PTR DO __NOT__ ACCESS THE OBJECT LIKE THIS!!!
                            // This is just for demonstrative purpose.
}

// This will actually compile
// auto_ptr and shared_ptr use delete and NOT delete []
void bad_idea_function()
{
    auto_ptr<string> aps(new string[10]); // wrong delete will be used
    shared_ptr<int> spi(new int[1024]);     // here as well
                                            // TODO check unique_ptr though, that supports arrays.
}

int main(int argc, char** argv)
{
    // Test_class * test_class = new Test_class(); // One way to do it, then just delete at the end
    shared_ptr_function();

    return 0;
}
