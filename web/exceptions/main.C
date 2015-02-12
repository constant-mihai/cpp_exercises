/***************************************** 

* File Name : main.C

* Creation Date : 28-11-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/

#include <iostream>
#include <exception>

using namespace std;

/*
 * Purpose :
 *
 */

// Abstract exception
class Abstract_Exception {
    public:
        virtual ~Abstract_Exception() {};

        virtual void print_exception_string()=0;
};

// Default Exception
class Default_Exception : public Abstract_Exception {
    public:
        ~Default_Exception() {};
        
        void print_exception_string() { cout << "Nothing to be printed" << endl; }
};


// An undefined Exception
class Undefined_Exception : public Abstract_Exception{
    public:
        //Constructor
        Undefined_Exception(const string& s)
            : s(s) {};
        //Copy constructor
        Undefined_Exception(Undefined_Exception& ue) { s = ue.s; };
        // Copy operator
        Undefined_Exception operator=(Undefined_Exception& ue)
        {
            if (&ue != this)
            {
                s = ue.s;
            }

            return *this;
        }

        // Destructor
        ~Undefined_Exception() {};

        void print_exception_string() { cout << s << endl; };
    private:
        string s;

};

class My_Exception : exception 
{
    public:
        const char* what ()
        {
            return "My exception happened";  
        }

        void test_function()
        { cout << "this is a test function" << endl; } 

} myex;

class My_Other_Exception : public My_Exception {
    public:
        const char* what () 
        {
           return "My other exception happened";
        }

        void test_function()
        { cout << "this is another test function" << endl; }
    
} myotherex;

//If this function throws an exception of some type other than int, 
//the function calls std::unexpected instead of looking for a handler 
//or calling std::terminate.
void throw_function(int param) 
{
    throw param;
    //throw "String";       // This will crash.
}


int main(int argc, char** argv)
{
    try
    {
        //throw myex;
        throw_function(1);
        //throw "String";
        try 
        {
            throw 20;
        }
        catch(int n)
        {
            throw;
        }

        Default_Exception de;
        throw de;
        string s("Undefined_exception string");
        Undefined_Exception ue(s);
        throw ue;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    catch (int e)
    {
        cout << "Exception " << e << endl;
    }
    catch (string& s)
    {
    }
    catch (Undefined_Exception ue)
    {
        ue.print_exception_string();
    }
    catch (...)
    {
        cout << "Default exception" << endl;
    }

    return 0;
}
