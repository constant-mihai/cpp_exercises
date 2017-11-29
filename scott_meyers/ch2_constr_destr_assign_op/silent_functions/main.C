/***************************************** 

* File Name : main.C

* Creation Date : 24-11-2014 

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/


/*
 *  Purpose : describes the behaviour of an object on creation.
 *  What functions get created and called.
 */


// standard C++
#include <string>
#include <iostream>

using namespace std;

// This
class Empty {};

// Is essentially the same as this
class Not_Really_Empty
{
    public:
        // The following functions are generated only if they are needed
        Not_Really_Empty() {};
        Not_Really_Empty(const Not_Really_Empty& rhs) { /*Copy whatever from rhs*/ }
        ~Not_Really_Empty() {};

        Not_Really_Empty& operator=(const Not_Really_Empty& rhs) 
        {
            if (&rhs != this) 
                ; // Copy whatever here.
           return *this; 
        };
};

class Virtual_Destructor_Class
{
    public:
        virtual ~Virtual_Destructor_Class() {};
};

class Virtual_Destructor_Class_Inheritance : Virtual_Destructor_Class
{
    // Will inherit a virtual destructor
};


// Template
template<typename T>
class Named_Object
{
    public:
        // This means a default constructor will not be generated
        Named_Object(const char *name, const T& value)
        {
            cout << "This is the char constructor" << endl;
            name_value = string(name);
            object_value = value;
        };

        // Another type of constructor
        Named_Object(const string& name, const T& value)
        {
            cout << "This is the string constructor" << endl;
            name_value = name;
            object_value = value;
        };

        // However copy constructor and assignment operator will be generated
        // As well as a destructor.

    private:
        // This will be used in the copy constructor in the first example.
        string name_value;
        T object_value;
};


template<typename T>
class Second_Named_Object
{
    public:
        // This ctor no longer takes a const name, because name_value
        // is now a reference-to-non-const string.
        // The char* constructor is gone, because we must have a string to refer to. 
        Second_Named_Object(string& name, const T& value)
            : name_value(name)
        {
            cout << "This is the string constructor" << endl;
            object_value = value;
        };

        // However copy constructor and assignment operator will be generated
        // As well as a destructor.

    private:
        string& name_value;
        T object_value;
};


class Private_Copy_Constructor
{
    public:
        Private_Copy_Constructor() {};
    private:
        Private_Copy_Constructor(Private_Copy_Constructor& pcc);
};

class Derived_Copy_Constructor : Private_Copy_Constructor
{
    // Nothing here, just inherits the private copy constructor
};

int main(int argc, char** argv)
{
    // This will print something
    Named_Object<int> no1("Smallest Prime Numer", 2); 
    // This will not. It's a default copy costructor.
    // - First calls copy constructor for name_value (string)
    // - Second it copies the bits for the int value
    Named_Object<int> no2(no1);

    string new_dog("Persephone");
    string old_dog("Satch");
    // The two objects 
    Second_Named_Object<int> p(new_dog, 2); 
    Second_Named_Object<int> s(old_dog, 36);
    // Here it gets weird.
    /* *** p=s; *** */ // <------ This will NOT compile

    /* This is basically the compiler telling you that you are about to do something really dumb.
     * Or at least his default copy constructor doesn't know how to handle it.
     * IF indeed you want to go ahead with it, you'll have to write your own copy constructor.
     * - First problem is you are reassigning a reference to a different object.
     * - Second problem is you are trying to overwrite a const value.
     * - Third, if you choose to just modify the string being referenced
     *   what happens to objects not directly involved in the exchange, 
     *   which still have pointers/references to the overwritten name_value?
     */

    Private_Copy_Constructor pcc;
    Derived_Copy_Constructor dcc1;
    /* *** Derived_Copy_Constructor dcc2(dcc1); *** */ // <------ This will NOT compile

    /* In case you go for a private copy constructor, 
     * the derived classes will NOT have a default copy constructor*/

    return 0;
}
