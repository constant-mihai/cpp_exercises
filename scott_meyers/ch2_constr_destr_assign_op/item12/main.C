/***************************************** 

* File Name : main.C

* Creation Date : 02-12-2014

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/

#include <string>
#include <iostream>

using namespace std;


/*
 * Purpose : Copy all parts of an object
 *
 */


class Customer {
    public:
        Customer()
            : name() {};
        Customer(const Customer& rhs)
            : name(rhs.name)
        {
            cout << "Customer copy constructor"  << endl;
        }

        Customer& operator=(const Customer& rhs)
        {
            cout << "Customer copy assignment operator"  << endl;
            name = rhs.name;
            return *this;
        }

    private:
        string name;
};

class PriorityCustomer : public Customer {
    public:
        PriorityCustomer(const PriorityCustomer& rhs)
        {
            cout << "PriorityCustomer copy constructor " << endl;
        }

        PriorityCustomer& operator=(const PriorityCustomer& rhs)
        {
            cout << "PriorityCustomer copy operator " << endl;
            priority = rhs.priority;    // Class is derived. All other inherited members are not copied.
            return *this;
        }

    private:
        int priority;
};

class PriorityCustomerGoodCopy: public Customer {
    public:
        PriorityCustomerGoodCopy(const PriorityCustomerGoodCopy& rhs)
            : Customer(rhs),            // Base class constructor.
                priority(rhs.priority)
        {
            cout << "PriorityCustomerGoodCopy copy constructor " << endl;
        }

        PriorityCustomerGoodCopy& operator=(const PriorityCustomerGoodCopy& rhs)
        {
            cout << "PriorityCustomerGoodCopy copy operator " << endl;
            Customer::operator=(rhs);
            priority = rhs.priority;
            return *this;
        }

    private:
        int priority;
};

int main(int argc, char** argv)
{
}

