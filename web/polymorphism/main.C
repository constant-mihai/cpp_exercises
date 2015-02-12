/***************************************** 

* File Name : main.C

* Creation Date : 28-11-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/



/*
 * Purpose : Describes polymorphism
 *
 */


// pointers to base class
#include <iostream>
using namespace std;

class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b; }
    virtual int area ()                // Marks it as being available to implement in different functions
      { return 0; }

    void print_area()
      { cout << this->area() << endl; }

};

// Abstract base class
class Abstract_Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b; }
    virtual int area () = 0;            // Pure virtual method.
    void print_area()                   // Inside the base members can call virtual functions;
      { cout << this->area() << endl; }
};

class Rectangle: public Abstract_Polygon {
  public:
    int area()
      { return width*height; }
};

class Triangle: public Abstract_Polygon {
  public:
    int area()
      { return width*height/2; }
};

int main () {
  Rectangle rect;
  Triangle trgl;;
  Polygon poly;

  Abstract_Polygon * ppoly1 = &rect;
  Abstract_Polygon * ppoly2 = &trgl;
  Polygon * ppoly3 = &poly;
  ppoly1->set_values (4,5);
  ppoly2->set_values (4,5);
  ppoly3->set_values (4,5);

  ppoly1->print_area();
  ppoly2->print_area();
  ppoly3->print_area();

  return 0;
}
