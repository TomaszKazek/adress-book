#include <iostream>
#include <fstream>
#include "FileUsers.h"

using namespace std;

void FileUsers::addUser(string newUser)
{
    users.open("Users.txt",ios::out|ios::app);
    if(ifstream("Users.txt", ios::ate).tellg()!=0)
        users<<endl;

        users<<newUser;

    users.close();
}


