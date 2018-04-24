#ifndef Person_h
#define Person_h

#include <iostream>

using namespace std;

class Person
{
protected:
    int userID;
    string name;

public:
    void setUserID(int ID);
    void setName(string n);
    int getUserID();
    string getName();
};

#endif // Person_h
