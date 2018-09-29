/***************************************** 

* File Name : map_uptr.C

* Creation Date : 06-06-2016

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/

#include <memory>
#include <unordered_map>
#include <string.h>
#include <iostream>

using namespace std;

class Container
{
    public:
        Container():
            tmp() {};

        unordered_map<int, unique_ptr<char>> charMap;
        unique_ptr<char> tmp;
};


int main(int argc, char** argv)
{

    Container container;

    unique_ptr<char> s(new char(10));
    //container.charMap.insert(make_pair<int, unique_ptr<char>>(0, std::unique_ptr<char>(new char(10))));
    //
    //
    container.charMap[0] = move(s);

    char *ct_ptr_ch = new char(10);
    memcpy(ct_ptr_ch, "Test String", 8);
    {
        unique_ptr<char> s2(ct_ptr_ch);
        cout << ct_ptr_ch << endl;

    }

    if (ct_ptr_ch == NULL) cout << "s is null" << endl;
    else cout << ct_ptr_ch << endl;

    char *is_this_null = new char(10);
    memcpy(is_this_null, "Del Null", 8);
    delete is_this_null;
    if (is_this_null == NULL) cout << "is_this_null is nULL" << endl;


}
