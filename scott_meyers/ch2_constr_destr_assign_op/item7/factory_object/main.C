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
 * Purpose : Using a factory object to create another object and illustrating how dangerous it could be.
 *
 * Link:
 * http://www.codeproject.com/Articles/363338/Factory-Pattern-in-Cplusplus
 */

using namespace std;


class Time_Keeper {
    public:
        Time_Keeper()
        {
           time (&raw_time); 
           timeinfo = localtime(&raw_time);
        };

        virtual ~Time_Keeper() {};  // This gets declared virtual. Scott Mayers: "Any class with virtual functions should almost certainly have a virtual destructor." 

        virtual void whats_the_time() {};

        time_t raw_time;
        struct tm * timeinfo;

        //virtual Time_Keeper *create_time_keeper();    // This proved to be a little more code than anticipated.
};

class Atomic_Clock: public Time_Keeper {
    public:
        struct tm* get_time() { return timeinfo; };
        static Time_Keeper* create_time_keeper() { return new Atomic_Clock; };
        void whats_the_time() { printf("Atomic Clock says: %s \n", asctime(timeinfo)); }
};


class Water_Clock: public Time_Keeper {
    public:
        static Time_Keeper* create_time_keeper() { return new Water_Clock; };
        void whats_the_time() { printf("Water_Clock says: %s \n", asctime(timeinfo)); }
};

class Wrist_Watch: public Time_Keeper {
    public:
        static Time_Keeper* create_time_keeper() { return new Wrist_Watch; };
        void whats_the_time() { printf("Wrist_Watch says: %s \n", asctime(timeinfo)); }
};



// Define callback function type
typedef Time_Keeper* (*create_time_keeper_cb)();

class Time_Factory {
    private:
        // Constructor. It registers all the Time_Keeper types
        Time_Factory()
        {
            register_clocks("Atomic_Clock", Atomic_Clock::create_time_keeper);
            register_clocks("Water_Clock", Water_Clock::create_time_keeper);
            register_clocks("Wrist_Watch", Wrist_Watch::create_time_keeper);
        };

        // Copy constructor
        Time_Factory(const Time_Factory &) 
        { /* Copy here */ };

        // Copy operator
        Time_Factory &operator=(const Time_Factory &time_factory) 
        {   
            if (&time_factory != this)
                ; // Copy whatever here.
            return *this;
        };
        

        // The map for registering all Time_Keeper Types
        typedef unordered_map<string, create_time_keeper_cb> Factory_map;
        Factory_map time_factory_map;

    public:
        ~Time_Factory() { time_factory_map.clear(); }

        // TODO  build singleton
        static Time_Factory *instance()
        {
            static Time_Factory instance;
            return &instance;
        };

        
        // Registers callbacks, items are then looked up and created
        bool register_clocks(const string &name, create_time_keeper_cb gtk)
        {
            auto p = time_factory_map.emplace(name, gtk);
            return p.second;
        };
        
        // The look up function for the searched constructor
        Time_Keeper* get_time_keeper(const string &name)
        {
            Factory_map::iterator it = time_factory_map.find(name) ;
            if (it != time_factory_map.end())
                // It will get the creator function for the secified name, and then call it.
                return it->second();
            else 
                return NULL;
        }
};

int main(int argc, char** argv) {

    Time_Keeper *atomic_clock = Time_Factory::instance()->get_time_keeper("Atomic_Clock"); 
    Time_Keeper *water_clock = Time_Factory::instance()->get_time_keeper("Water_Clock"); 
    Time_Keeper *wrist_watch = Time_Factory::instance()->get_time_keeper("Wrist_Watch"); 
    atomic_clock->whats_the_time();
    water_clock->whats_the_time();
    wrist_watch->whats_the_time();

    //warning: deleting object of polymorphic class type ‘Time_Keeper’ which has non-virtual destructor might cause undefined behaviour 
    delete atomic_clock;
    delete water_clock;
    delete wrist_watch;
    
    return 0;
}
