/***************************************** 

* File Name : main.C

* Creation Date : 01-12-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/



/*
 * Purpose : Illustrates what happens on calling virtual functions on constructon/deconstruction
 *
 */

// Standard C++
#include <string>
#include <iostream>

using namespace std;

class Failed_transaction {
    public:
        Failed_transaction() 
        { 
//            log_transaction();  // Warning + Linker fail
        };

        virtual ~Failed_transaction() {};
        virtual void log_transaction() const = 0;
};


class Failed_buy_transaction : public Failed_transaction {
    public:
        virtual void log_transaction() const {};
};


class Failed_sell_transaction : public Failed_transaction {
    public:
        virtual void log_transaction() const;
};

class Insidious_transaction {
    public:
        Insidious_transaction()
        {
            init();     // This hides a call to a virtual function ...
        }

        virtual void log_transaction() const = 0;

    private:
        // A perfectly valid way of shooting yourself in the foot.
        void init ()
        {
            log_transaction();
        }
};

class Insidious_buy_transaction : public Insidious_transaction {
    public:
        virtual void log_transaction() const {};
};


// Valid example starts here
class Transaction {
    public:
        explicit Transaction(const string& log_info)
        {
            log_transaction(log_info);
        };
        void log_transaction(const string& log_info) { cout << log_info << endl; };
};


class Buy_transaction : public Transaction {
    public:
        Buy_transaction(string& log_info)
            : Transaction(log_info) {};
};



// INVALID Helper functions 
void failed_transactions_example() {
    Failed_buy_transaction fb;  // The base class constructor gets called first.
                                // The virtual function is not even implemented at this point.
                                // MOREOVER: Members have not been initialized yet.
                                // That's why C++ forces you to treat them like they don't exist
                                // by not giving you any way to access them.
                                // This same logic applies for the destructor.
                                // Once the destructor was called, members were destroyed. Puff, Gone!
                                // They don't exist anymore.

}

void insidious_transactions_example() {
    Insidious_buy_transaction it;
}

// VALID helper functions
void transaction_example() {
    string s("buy");
    Buy_transaction bt(s);
}

int main (int argc, char** argv) {
    //failed_transactions_example();
    //insidious_transactions_example(); // This will abort: "pure virtual method called".
    transaction_example();

    return 0;
}
