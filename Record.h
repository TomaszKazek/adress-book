#ifndef Record_h
#define Record_h

#include <iostream>
#include "Person.h"

using namespace std;

class Record:public Person
{
    int ID;
    string lastName, address, email, phone;

public:
    void setID(int id);
    void setLastName(string l);
    void setAddress(string a);
    void setEmail(string e);
    void setPhone(string p);

    int getID();
    string getLastName();
    string getAddress();
    string getEmail();
    string getPhone();
};

#endif // Record_h
