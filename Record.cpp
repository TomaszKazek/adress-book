#include <iostream>
#include "Record.h"

using namespace std;

void Record::setID(int id)
    {
        ID=id;
    }

    void Record::setLastName(string l)
    {
    lastName=l;
    }

    void Record::setAddress(string a)
    {
    address=a;
    }

    void Record::setEmail(string e)
    {
    email=e;
    }

    void Record::setPhone(string p)
    {
    phone=p;
    }

    int Record::getID()
    {
        return ID;
    }

    string Record::getLastName()
    {
        return lastName;
    }

    string Record::getAddress()
    {
        return address;
    }

    string Record::getEmail()
    {
        return email;
    }

    string Record::getPhone()
    {
        return phone;
    }
