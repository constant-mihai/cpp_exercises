/***************************************** 

* File Name : main.C

* Creation Date : 24-11-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/



/*
 * Purpose : Different things you can do with inheritance.
 * ...
 *
 *  Fun stuff!
 *  http://www.learncpp.com/cpp-tutorial/115-inheritance-and-access-specifiers/
 * +--------------------------+--------+-----------+---------+
 * | Access                   | Public | Protected | Private |
 * +--------------------------+--------+-----------+---------+
 * | members of the same class|   yes  |    yes    |    yes  |
 * +--------------------------+--------+-----------+---------+
 * | members of derived class |   yes  |    yes    |    no   |
 * +--------------------------+--------+-----------+---------+
 * | Not members              |   yes  |    no     |    no   |
 * +--------------------------+--------+-----------+---------+
 */

// Standard C++
#include <iostream>

using namespace std;


// Normal Inheritance
class Polygon 
{
    protected:
        int width, height;
    public:
        int test;

        Polygon()
            : test(5) {};

        Polygon(int a, int b)
            : width(a),
            height(b) {};

        void set_values(int a, int b)
        { width=a; height=b; }
    private:
};

class Rectangle: public Polygon {
    public:
        int area()
        { return width * height; };
};

class Triangle: public Polygon {
    public:
        int area ()
        { return width * height / 2; }
};

class Output {
    public:
        void print(int i) { cout << i << endl; };
};


// Multiple Inheritance
// Derived classes are marked as public.
// Doing otherwise will not allow access to their members.
class Multiple_Rectangle : public Output, public Polygon {
        public:
            Multiple_Rectangle(int a, int b)
            : Polygon(a, b) {};
        int area () { return width*height; };
};


// Protected Inheritance
class Protected_Rectangle : protected Polygon {
    public:
        int area ()
        { return width * height; };

        void print_test()
        { cout << test << endl; };
};

// Private Inheritance
// http://stackoverflow.com/questions/374399/why-do-we-actually-need-private-or-protected-inheritance-in-c?lq=1
// However, this way of doing has several disadvantages:
//
//     your intent is much less clear
//         it can lead to abusive multiple inheritance
//             it breaks the encapsulation of the Engine class since you can access its protected members
//                 you're allowed to override Engine virtual methods, which is something you don't want if your aim is a simple composition
//
class Private_Rectangle : private Polygon {
    public:
        int area ()
        { return width * height; };

        void print_test()
        { cout << test << endl; };

};

int main(int argc, char** argv)
{
    Rectangle rect;
    Triangle tri;
    rect.set_values(4,5);
    tri.set_values(4,5);

    cout << rect.area() << endl;
    cout << tri.area() << endl;
    cout << tri.test << endl;

    Protected_Rectangle protected_rectangle;
//    cout << protected_rectangle.test << endl; // <---------- Will Not compile! Protected Inheritance means this will be protected.
    protected_rectangle.print_test();           // Completely fine. The derived class has access to protected base class members.

    Private_Rectangle private_rectangle;
//    cout << private_rectangle.test << endl; // <---------- Will Not compile! Private Inheritance means this will be private.
    private_rectangle.print_test();           // Completely fine. The derived class has access to private base class members.

    Multiple_Rectangle multiple_rectangle(4,5);
    multiple_rectangle.print(multiple_rectangle.area());    

    return 0;
}
