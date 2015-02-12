/***************************************** 

* File Name : main.C

* Purpose : 

* Creation Date : 23-10-2014 20-12-2008

* Last Modified : Tue 04 Nov 2014 04:02:15 PM CET

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/

/*
*
*  Playing around with local static objects.
*  The purpose of these are to replace non-local static objects
*  which can lead to dependecie problems when one object during
*  initiation needs another non-local object to be initiated.
*  This specific file however just points out on how you should
*  take care on how you use these local static objects, and
*  how you should not copy them by calling something like:
*  Some_Class sc = get_local_static_object();
*
*  Corect way of doing it is always calling:
*   get_local_static_object();
* 
*/

#include <cassert>
#include <iostream>

using namespace std;

/**
 * A regular class 
 */
class Some_Class 
{
    public:
        Some_Class();

        int get_value();
        int set_value(int val);

        Some_Class& operator =(const Some_Class& sc)
        {
            value = sc.value;
            cout << " copied value   " << &value 
                << "  value  " << &(sc.value) << "\n" ;
            return *this;
        }

        Some_Class(const Some_Class& sc)
        {
            cout << "Constructor" << "\n";
            value = sc.value;
            cout << "copied value  " << &value 
                << "  value  " << &(sc.value) << "\n" ;
        }

    private:
        int value;
};

Some_Class::Some_Class()
    :value(1)
{}

int Some_Class::get_value()
{
    return value;
}

int Some_Class::set_value(int val)
{
    this->value = val;
}

Some_Class& test_obj()
{
    static Some_Class sc;
    return sc;
}

void print(const string& s)
{
    cout << s << "\n";
}

int main(int argc, char** argv)
{

    string s("const_string");
    print(s);
    Some_Class sc;
    sc = test_obj();

    cout << test_obj().get_value() << "\n";
    test_obj().set_value(4);
    cout << test_obj().get_value() << "\n";
    sc.set_value(5);
    cout << sc.get_value() << "\n";
    cout << test_obj().get_value() << "\n";

    return 1;
}
