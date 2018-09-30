/***************************************** 

* File Name : main.C

* Creation Date : 24-11-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/



/*
 * Purpose : Shows how to disallow the use of compiler generated
 * functions, that you do not want. In short: how to prevent copying.
 *
 */

class Home_For_Sale
{
    friend class Construction_Company;
    friend class Caban;

    public:
        Home_For_Sale() {};
    private:
        /* DECLARE, DON'T DEFINE. Will stop pretty much anyone from copying. Inlcuding friends and inheretance */
        Home_For_Sale(const Home_For_Sale&);
        Home_For_Sale& operator=(const Home_For_Sale&);
};



class Construction_Company
{
    private:
        Home_For_Sale hfs;
    public:
        /* We are trying to prevent this. As per the example given in main. */
        Construction_Company(const Home_For_Sale& hfs)
            : hfs(hfs) {};

};


class Caban : Home_For_Sale
{
    private:
        // Dunno. Can't think of anything else.
        Home_For_Sale hfs;
    public:
        // The constructor, calling the copy constructor of Home_For_Sale;
        // Simply writing these so will not compile.
        // Trying really hard to go through by befrending Caban in Home_For_Sale will not link.
        Caban(Home_For_Sale& hfs, int tmp) { this->hfs = hfs; (void)tmp; }
        Caban(Home_For_Sale& hfs)
           : hfs(hfs) {};

};

// Another way to do it would be by declaring...
class Uncopyable
{
    // And then by allowing construction and destruction...
    protected:
        Uncopyable() {};
        ~Uncopyable() {};

    // But not copying.
    private:
        Uncopyable(const Uncopyable&);
        Uncopyable& operator=(const Uncopyable&);

};

// And in the end you just need to create a class which inherits Uncopyable.
// Just like your colegues hand writing, when you try to cheat off him in Optimisation Theories. 
// Quick catch-up on public/protected/private inheratance. First, three links regarding this:
// http://stackoverflow.com/questions/860339/difference-between-private-public-and-protected-inheritance
// http://www.cplusplus.com/forum/beginner/12899/
// http://www.parashift.com/c++-faq-lite/priv-inherit-like-compos.html
// - Public inheratance, everyone knows about it. AKA "is a" relationship.
// - Protected in this type, only the derived class and it's childern know about the inheritance.
// - Private, this is a "has a" relantionship. Which will get it's own directory.
class Condo_For_Sale : private Uncopyable
{
    // When trying to copy a Condo, the base class constructors will also have to be called.
    // And it will fail.
};

int main(int argc, char** argv)
{
    Home_For_Sale hfs;
    /* *** Home_For_Sale hfs2(hfs); *** */ // <--- Will NOT compile. Which is nice ... in this case


    Home_For_Sale hfs3;
    /* *** hfs3 = hfs; *** */ // <---------------- Will NOT compile. Again, this is what we are trying to acheive.
    /* *** Construction_Company cc(hfs); *** */ // Fails to link. Really nice stuff, much clear, so readable:

//    main.o: In function `Construction_Company::Construction_Company(Home_For_Sale const&)':
//    main.C:(.text._ZN20Construction_CompanyC2ERK13Home_For_Sale[_ZN20Construction_CompanyC5ERK13Home_For_Sale]+0x1f): undefined reference to `Home_For_Sale::Home_For_Sale(Home_For_Sale const&)'
//    collect2: error: ld returned 1 exit status
//    make: *** [main] Error 1

    /* *** Caban caban(hfs); *** */ // Fails to link. Will spit out something similar to whats above.

 
    Condo_For_Sale condo;
    Condo_For_Sale copy_condo;
    /* *** copy_condo = condo; *** */ // Fails to compile.


}
