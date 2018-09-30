/***************************************** 

* File Name : main.C

* Creation Date : 26-11-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/

#include <unordered_map>
#include <stdio.h>
#include <time.h>


/*
 * Purpose :  *
 */

using namespace std;


class Widget {
    public:
        Widget()
        {
        };

        virtual ~Widget() {};  // This gets declared virtual. Scott Mayers: "Any class with virtual functions should almost certainly have a virtual destructor." 

        Widget& operator+=(const Widget& rhs) {
            /*...*/
            return *this;
        }

        Widget& operator=(const Widget& rhs) {
            if (this == &rhs) return *this; // Identity test. Do nothing.
            /*...*/
            return *this;
        }

};

int main(int argc, char** argv) {
    
    return 0;
}
