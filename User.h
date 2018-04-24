#ifndef User_h
#define User_h

#include <iostream>
#include "Person.h"

using namespace std;

class User:public Person
{
    string password;

public:
    string getPassword();
    void setPassword(string p);
};

#endif
