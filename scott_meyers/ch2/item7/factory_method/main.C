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
 * Purpose : Using a factory method to create an object and illustrating how dangerous it could be.
 * This is the simpler example. The next one will incorporate a more complex factory OBJECT.
 *
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

};

class Atomic_Clock: public Time_Keeper {
    public:
        void whats_the_time() { printf("Atomic Clock says: %s \n", asctime(timeinfo)); }
};


class Water_Clock: public Time_Keeper {
    public:
        void whats_the_time() { printf("Water_Clock says: %s \n", asctime(timeinfo)); }
};

class Wrist_Watch: public Time_Keeper {
    public:
        void whats_the_time() { printf("Wrist_Watch says: %s \n", asctime(timeinfo)); }
};



typedef enum 
{
    UNDEFINED,
    ATOMIC_CLOCK,
    WATER_CLOCK,
    WRIST_WATCH,
} time_keeper_type;

Time_Keeper *create_time_keeper(time_keeper_type e) 
{
    switch(e) {
    case ATOMIC_CLOCK:
        return new Atomic_Clock;
        break;
    case WATER_CLOCK:
        return new Water_Clock;
        break;
    case WRIST_WATCH:
        return new Wrist_Watch;
        break;
    case UNDEFINED:
    default:
        printf("Type %d Ain't no Time Keeper \n", e);
        return 0;
        break;
    }

    return 0;
} 

int main(int argc, char** argv) {

    Time_Keeper *atomic_clock = create_time_keeper(ATOMIC_CLOCK);
    Time_Keeper *water_clock = create_time_keeper(WATER_CLOCK);
    Time_Keeper *wrist_watch = create_time_keeper(WRIST_WATCH);
    atomic_clock->whats_the_time();
    water_clock->whats_the_time();
    wrist_watch->whats_the_time();

    //warning: deleting object of polymorphic class type ‘Time_Keeper’ which has non-virtual destructor might cause undefined behaviour 
    delete atomic_clock;
    delete water_clock;
    delete wrist_watch;
    
    return 0;
}
