/***************************************** 

* File Name : main.C

* Creation Date : 03-12-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/



/*
 * Purpose : Talks about copying behaviour when working with more delicate classes.
 * E.g. Lock classes, Resource Management classes.
 * Options pretty much are:
 * - Prohibit copying.
 * - Reference-count the underlying resource.
 * - Copy the underlying resource.
 * - Transfer ownership of the underlying resource.
 *
 */

// Standard C++

class Mutex {
};

class Lock {
    public:
        explicit Lock(Mutex *pm)
            : mutex_ptr(pm)
        { lock(mutex_ptr); }

        ~Lock() { unlock(mutex_ptr); } // possibly could be omitted since the default destructor for Mutex 
                                       // might unlock, but is bad practice IMO.

        void lock(Mutex *m) {};
        void unlock(Mutex *m) {};
    private:
        Mutex *mutex_ptr;
        // shared_ptr<Mutex> mutex_ptr // optionally, used a shared pointer
};

int main(int argc, char** argv)
{
    Mutex m;

    {
        Lock ml(&m);
        // Critical section operations here
    }   // Automatically unlock mutex at the end of the block
        // Own Commentary: However, WHO does that? I mean, omitting this stuff is not a good practice IMHO.

    return 0;
}
