/***************************************** 

* File Name : main.C

* Creation Date : 28-11-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/

#include <vector>
#include <stdio.h>
#include <cstdlib>

using namespace std;

/*
 * Purpose : Destructors should not throw exceptions
 *
 */

class Failed_widget {
    public:
       ~Failed_widget() { throw 20; }        // Exception here.
};

class Better_widget {
    public:
        ~Better_widget() 
        {
            try 
            { 
                this->throw_something(); 
            } 
            catch (...) 
            { 
                printf("Caught exception in widget\n");
            } 
        } // One way to handle it

        void throw_something() { throw 20; } 
};

class Widget 
{
    public:
        void throw_something() {throw 20;}
};



class Widget_manager {
    public:
        Widget_manager()
            : closed(false) {};

        ~Widget_manager()
        { 
            try
            { 
                vector<Widget>::iterator it;
                for (it=widgets.begin(); it != widgets.end(); ++it)
                    it->throw_something();
            } 
            catch (...)
            { 
                printf("Caught exception in manager \n"); 
                abort(); // Abort is the ideal solution any way.
                         // Not aborting here could lead to memory leaks or even undefined beheaviour.
                         // Another option to this would be to just swallow the exception and log it somewhere.
            } 
        }; // Another way to deal with it. 

        void close() 
        {
             vector<Widget>::iterator it;
             for (it=widgets.begin(); it != widgets.end(); ++it)
                 it->throw_something();
        }

        void close_wrapper ()
        {
            // TODO close whatever here.

        }   // This could be implemented as well.
            // Provides one more layer in which to catch the exception.
            // This has to be called by the user before destructing.
        //// The call flow will then look like this: call close_wrapper; call ~Widget_manager;
        //// The destructor will then look like this:
        //~Widget_manager() 
        //{ 
        //  if (!closed)
        //  {
        //      try
        //      {
        //          // TODO close whatever here
        //      }
        //      catch(...)
        //      {
        //          printf("Caught exception in manager \n");
        //      }
        //  }
        //}

        void append(Widget& w) { widgets.push_back(w); }
    private:
        vector<Widget> widgets;
        bool closed;
};

// Function to exemplify what happens on propagation of two exceptions.
void create_vector_widget()
{
    try 
    {
        {
            vector<Failed_widget> v;
            Failed_widget w0, w1;

            v[0] = w0;
            v[0] = w1;    
        }
    
    }
    catch (...)
    {
        printf("Caught exception \n");  // This will not be printed. The program doesn't reach this.
    }


    // Widgets will be destroyed on exit. Widget destructor will throw two exceptions one after the other.
}

int main(int argc, char** argv)
{
    // create_vector_widget();  // This will just crash. 
                                // Two exceptions will be raised in the same block
                                // without being treated.
    Widget_manager big_boss;
    Widget w0, w1;

    big_boss.append(w0);
    big_boss.append(w1);

    return 0;
}
