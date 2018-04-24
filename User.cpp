#include <iostream>
#include "User.h"

using namespace std;

void User::setPassword(string p)
    {
password=p;
    }

    string User::getPassword()
    {
        return password;
    }
