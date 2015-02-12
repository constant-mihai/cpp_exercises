#include <stdio.h>
int f(char);
int g(char&);
int h(const char&);

int main (int argc, char** argv) {

        char c;
        unsigned char uc;
        signed char sc;
                
        f('a'); g('a'); h('a');
        f(49); g(49); h(49);
        f(300000); g(30000); h(30000);
        f(uc); g(uc); h(uc);
        f(c); g(c); h(c);
        f(sc); g(sc); h(sc);
         
        return 0;
}
