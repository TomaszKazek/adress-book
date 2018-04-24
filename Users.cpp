#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "Users.h"

using namespace std;

Users::Users()
{
    usersList.clear();
    fstream existingUsers;
    string buffer;
    existingUsers.open("Users.txt",ios::in);
    lastUserID=0;
    if (existingUsers)
    {
        if(ifstream("Users.txt", ios::ate).tellg()!=0)
        {
            while (!(existingUsers.eof()))
            {
                User *p_User = new User;
                getline(existingUsers,buffer);
                stringstream ss(buffer);
                getline(ss,buffer,'|');
                p_User->setUserID(atoi(buffer.c_str()));
                getline(ss,buffer,'|');
                p_User->setName(buffer);
                getline(ss,buffer,'|');
                p_User->setPassword(buffer);
                usersList.push_back(*p_User);
                lastUserID=p_User->getUserID();
                delete p_User;
            }
        }
        existingUsers.close();
    }
    }

int Users::logging()
{
    string name, password;
    cout<<"Podaj nazwe uzytkownika: ";
    cin.sync();
    getline(cin, name);

    vector<User>::iterator index=usersList.begin();

    while (index!=usersList.end())
    {
        if (name==index->getName())
        {
            for(int i=0;i<3;i++)
            {
                cout<<"Podaj haslo: ";
                cin.sync();
                getline(cin,password);
            if (password==index->getPassword())
            {
                system("cls");
                cout<<"Witaj "<<index->getName()<<endl;
                system("pause");
                return index->getUserID();
            }
            else
                cout<<"Haslo niepoprawne\n";
            }
        }
        index++;
    }
    system("cls");
    cout<<"Proba logowania zakonczyla sie niepowodzeniem\n";
    system("pause");
    return 0;
}

string Users::addUser()
{
    string newUser, buffer;
    stringstream ss;
    vector<User>::iterator index=usersList.end();
    User *p_user=new User;

    p_user->setUserID(lastUserID+1);
    lastUserID+=1;
    ss<<p_user->getUserID();
    newUser=ss.str();
    newUser+="|";
    cout<<"ID: "<<p_user->getUserID()<<endl;

    cout<<"Podaj nazwe: ";
    cin.sync();
    getline(cin, buffer);
    p_user->setName(buffer);
    newUser+=p_user->getName()+"|";

    cout<<"Podaj haslo: ";
    cin.sync();
    getline(cin, buffer);
    p_user->setPassword(buffer);
    newUser+=p_user->getPassword();

    usersList.push_back(*p_user);
    delete p_user;
    system("pause");
    return newUser;
}

vector<User> Users::getUsersList()
{
    return usersList;
}

int Users::getUserID()
{
    return userID;
}
void Users::setUserID(int u)
{
    userID=u;
}
