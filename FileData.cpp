#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "FileData.h"

using namespace std;

void FileData::addRecord(string RecordToAdd)
{
    contacts.open("Data.txt",ios::out|ios::app);
    if(ifstream("Data.txt", ios::ate).tellg()!=0)
        contacts<<endl;

        contacts<<RecordToAdd;

    contacts.close();
}

void FileData::editRecord(string RecordToEdit)
{
    string buffer,ID,IDtoChange;
    fstream contacts, newContacts;
    contacts.open("Data.txt",ios::in);
    newContacts.open("NewData.txt",ios::out);

    if (contacts)
    {
    while (!(contacts.eof()))
    {
    getline(contacts,buffer);
    stringstream ss(buffer);
    getline(ss,ID,'|');
    ss.str(RecordToEdit);
    getline(ss,IDtoChange,'|');
    if (ID==IDtoChange)
    {
        newContacts<<RecordToEdit<<endl;
    }
    else
    {
        newContacts<<buffer<<endl;
    }
    }
    contacts.close();
    newContacts.close();
    remove("Data.txt");
    rename("NewData.txt","Data.txt");
    }
}

void FileData::deleteRecord(int IDtoDelete)
{
    string buffer,ID;
    fstream contacts, newContacts;
    contacts.open("Data.txt",ios::in);
    newContacts.open("NewData.txt",ios::out);
    bool firstRow=true;

    if (contacts)
    {
    while (!(contacts.eof()))
    {
    getline(contacts,buffer);
    stringstream ss(buffer);
    getline(ss,ID,'|');
    if (atoi(ID.c_str())!=IDtoDelete)
    {
        if (firstRow==true)
        {
        newContacts<<buffer;
        firstRow=false;
        }
        else
            newContacts<<endl<<buffer;
    }
    }
    contacts.close();
    newContacts.close();
    remove("Data.txt");
    rename("NewData.txt","Data.txt");
    }
}

