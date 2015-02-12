/***************************************** 

* File Name : main.C

* Creation Date : 12-01-2015

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/



/*
 * Purpose :
 *
 */


#include <iostream>
#include <cmath>

using namespace std;

typedef enum
{
    I = 0,    // 000
    V = 1,    // 100 
    X = 2,    // 010 
    L = 3,    // 110 
    C = 4,    // 001 
    D = 5,    // 101 
    M = 6,    // 011 
    mz = 7,   // 111

}symbol;

class Convert
{
    public:

       void zeros(int a, int i)
       {
          int n = a/pow(10,i);
          char c;
          switch (i) 
          {
              case 3:
                  c = 'M';
                  break;
              case 2:
                  c = 'C';
                  break;
              case 1:
                  c = 'X';
                  break;
              case 0:
                  c= 'I';
                  break;
              default:
                  cout << "error";
                  break;
          }
          while (n) { cout << c; n--;};
       }; 

       void atr(int a)
       {
           int v[4] = {0, 0, 0, 0};
           break_number(a, v);

           zeros(v[3], 3);

           if (v[2] < 500)
           {
               if (!(v[2]%400))
               {
                   cout << "CD";
               }
               else
               {
                   zeros(v[2], 2);
               }
           }
           else
           {
               if (!(v[2]%900))
               {
                   cout << "CM";
               }
               else
               {
                   cout << "D";
               }
           }

           if (v[1] < 50)
           {
               if (!v[1]%40)
               {
                   cout << "XL";
               }
               else
               {
                   zeros(v[2], 2);
               }
           }
           else
           {
               if (!(v[1]%90))
               {
                   cout << "XC";
               }
               else
               {
                   cout << "L";
               }
           }

           if (v[0] < 5)
           {
               if (!v[0]%4)
               {
                   cout << "IV";
               }
               else
               {
                   zeros(v[0], 0);
               }
           }
           else
           {
               if (!(v[0]%9))
               {
                   cout << "IX";
               }
               else 
               {
                   cout << "V";
               }
           }

           cout << endl;

       };

       void break_number(int a, int* v) 
       {
           int r = a;
           for (int i=3;i>=0;i--)
           {
               int c=r/(pow(10,i));
               v[i] = c*pow(10,i);
               r=r-v[i];
               cout << " v[i]= " << v[i] << endl;
               cout << " r = " << r << endl;
           }

       };

       void rta();
};

int main(int argc, char** argv)
{

    Convert c;

    c.atr(2495);

    return 0;
}
