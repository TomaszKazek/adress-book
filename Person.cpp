#include <iostream>
#include "Person.h"

using namespace std;

void Person::setUserID(int ID)
{
    userID=ID;
}

void Person::setName(string n)
{
    name=n;
}

int Person::getUserID()
{
    return userID;
}

string Person::getName()
{
    return name;
}
