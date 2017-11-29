/***************************************** 

* File Name : main.C

* Creation Date : 03-12-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/



/*
 * Purpose: Is to emphasize that on should store the new'ed obeject in a smart pointer 
 * in a standalone statement. This way you avoid "subtle resource leaks"
 * Sounds complicated, isn't really. E.g. below.
 */

int main(int argc, char** argv)
{
    // Correct
    shared_ptr<string> sp(new string);

    process(sp);

    // Incorrect since it might throw exception and leak reasources.
    // There might also be some reordering in here due to the compiler
    // optimization
    process(shared<string>(new string));

    return 0;
}
