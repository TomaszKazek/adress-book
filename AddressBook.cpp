#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <conio.h>
#include "AddressBook.h"

using namespace std;

AddressBook::AddressBook(int userID)
{
    recordsList.clear();
    fstream contacts;
    string buffer;
    lastID = 0;
    contacts.open("Data.txt",ios::in);
    if (contacts)
    {
        if(ifstream("Data.txt", ios::ate).tellg()!=0)
        {
            while (!(contacts.eof()))
            {
                Record *p_Record=new Record;
                getline(contacts,buffer);
                stringstream ss(buffer);
                getline(ss,buffer,'|');
                p_Record->setID(atoi(buffer.c_str()));
                getline(ss,buffer,'|');
                p_Record->setUserID(atoi(buffer.c_str()));
                getline(ss,buffer,'|');
                p_Record->setName(buffer);
                getline(ss,buffer,'|');
                p_Record->setLastName(buffer);
                getline(ss,buffer,'|');
                p_Record->setAddress(buffer);
                getline(ss,buffer,'|');
                p_Record->setEmail(buffer);
                getline(ss,buffer,'|');
                p_Record->setPhone(buffer);

                lastID = p_Record->getID();
                if (p_Record->getUserID()==userID)
                recordsList.push_back(*p_Record);
                delete p_Record;
            }
        }
        contacts.close();
    }
}

int AddressBook::getLastID()
{
    return lastID;
}

string AddressBook::addRecord(int userID)
{
    string newRecord, buffer;
    stringstream ss;
    vector<Record>::iterator index=recordsList.end();
    Record *p_record=new Record;

    p_record->setID(lastID+1);
    lastID+=1;
    ss<<p_record->getID();
    newRecord=ss.str();
    newRecord+="|";
    cout<<"ID: "<<p_record->getID()<<endl;

    p_record->setUserID(userID);
    ss.str("");
    ss<<p_record->getUserID();
    newRecord+=ss.str();
    newRecord+="|";

    cout<<"Podaj imie: ";
    cin.sync();
    getline(cin, buffer);
    p_record->setName(buffer);
    newRecord+=p_record->getName()+"|";

    cout<<"Podaj nazwisko: ";
    cin.sync();
    getline(cin, buffer);
    p_record->setLastName(buffer);
    newRecord+=p_record->getLastName()+"|";

    cout<<"Podaj adres: ";
    cin.sync();
    getline(cin, buffer);
    p_record->setAddress(buffer);
    newRecord+=p_record->getAddress()+"|";

    cout<<"Podaj email: ";
    cin.sync();
    getline(cin, buffer);
    p_record->setEmail(buffer);
    newRecord+=p_record->getEmail()+"|";

    cout<<"Podaj nr telefonu: ";
    cin.sync();
    getline(cin, buffer);
    p_record->setPhone(buffer);
    newRecord+=p_record->getPhone();

    recordsList.push_back(*p_record);
    delete p_record;
    system("pause");
    return newRecord;
}

void AddressBook::showAllRecords()
{
    system("cls");
    if (recordsList.empty())
    {
        cout<<"Ksiazka jest pusta\n\n";
    }
    else
    {
        vector<Record>::iterator index=recordsList.begin();

        while (index!=recordsList.end())
        {
            cout<<index->getID()<<endl;
            cout<<index->getName()<<endl;
            cout<<index->getLastName()<<endl;
            cout<<index->getAddress()<<endl;
            cout<<index->getEmail()<<endl;
            cout<<index->getPhone()<<endl;
            index++;
        }
    }
    system("pause");
}

void AddressBook::findByName()
{
    system("cls");
    string name;
    bool ifFound=false;

    cin.sync();
    cout<<"Podaj imie: ";
    getline(cin,name);
    vector<Record>::iterator index=recordsList.begin();
    system("cls");

    while (index!=recordsList.end())
    {
        if (index->getName()==name)
        {
            cout<<index->getID()<<endl;
            cout<<index->getName()<<endl;
            cout<<index->getLastName()<<endl;
            cout<<index->getAddress()<<endl;
            cout<<index->getEmail()<<endl;
            cout<<index->getPhone()<<endl<<endl;
            ifFound=true;
        }
        index++;
    }
    if (ifFound==false) cout<<"Nie znaleziono osoby o takim imieniu\n\n";
    system("pause");
}

void AddressBook::findByLastName()
{
    system("cls");
    string lastName;
    bool ifFound=false;

    cin.sync();
    cout<<"Podaj nazwisko: ";
    getline(cin,lastName);
    vector<Record>::iterator index=recordsList.begin();
    system("cls");

    while (index!=recordsList.end())
    {
        if (index->getLastName()==lastName)
        {
            cout<<index->getID()<<endl;
            cout<<index->getName()<<endl;
            cout<<index->getLastName()<<endl;
            cout<<index->getAddress()<<endl;
            cout<<index->getEmail()<<endl;
            cout<<index->getPhone()<<endl<<endl;
            ifFound=true;
        }
        index++;
    }
    if (ifFound==false) cout<<"Nie znaleziono osoby o takim nazwisku\n\n";
    system("pause");
}

int AddressBook::deleteRecord()
{
    vector<Record>::iterator index=recordsList.begin();
    int IDtoDelete;
    char confirmation='2';

    cin.sync();
    cout<<"Podaj ID: ";
    cin>>IDtoDelete;

    while (index!=recordsList.end())
    {
        if (index->getID()==IDtoDelete)
        {
            cout<<index->getID()<<endl;
            cout<<index->getName()<<endl;
            cout<<index->getLastName()<<endl;
            cout<<index->getAddress()<<endl;
            cout<<index->getEmail()<<endl;
            cout<<index->getPhone()<<endl<<endl;
            cout<<"Usunac kontakt?\n1. Usun\n2. Cofnij\n";
            confirmation=getch();
        }
        if (confirmation=='1')
        {
            recordsList.erase(index);
            //usunRekordZPliku(IDdoUsuniecia,ostatnieID);
            break;
        }
        index++;
    }
    if (IDtoDelete==lastID)
        lastID-=1;

    return IDtoDelete;
}

string AddressBook::editRecord(int userID)
{
    vector<Record>::iterator index=recordsList.begin();
    int IDtoChange;
    char option;
    string newRecord, buffer;

    cin.sync();
    cout<<"Podaj ID: ";
    cin>>IDtoChange;

    while (index!=recordsList.end())
    {
        if (index->getID()==IDtoChange)
        {
            cout<<index->getID()<<endl;
            cout<<index->getName()<<endl;
            cout<<index->getLastName()<<endl;
            cout<<index->getAddress()<<endl;
            cout<<index->getEmail()<<endl;
            cout<<index->getPhone()<<endl<<endl;
            cout<<"1. Zmiana imienia\n2. Zmiana nazwiska\n3. Zmiana adresu\n4. Zmiana email'a\n5. Zmiana nr telefonu\n";
            option=getch();
            switch (option)
            {
            case '1':
                cout<<"Podaj nowe imie: ";
                cin>>buffer;
                index->setName(buffer);
                break;
            case '2':
                cout<<"Podaj nowe nazwisko: ";
                cin>>buffer;
                index->setLastName(buffer);
                break;
            case '3':
                cout<<"Podaj nowy adres: ";
                cin>>buffer;
                index->setAddress(buffer);
                break;
            case '4':
                cout<<"Podaj nowy email: ";
                cin>>buffer;
                index->setEmail(buffer);
                break;
            case '5':
                cout<<"Podaj nowy nr telefonu: ";
                cin>>buffer;
                index->setPhone(buffer);
                break;
            default:
                cout<<"Nie ma takiej opcji\n";
                system("pause");
                break;
            }
        stringstream ID;
        ID<<index->getID();
        newRecord=ID.str();
        ID.str("");
        ID<<userID;
        newRecord=newRecord+"|"+ID.str()+"|"+index->getName()+"|"+index->getLastName()+"|"+index->getAddress()+"|"+index->getEmail()+"|"+index->getPhone();
        //edycjaRekorduWPliku(IDdoZmiany, nowyRekord);
        }
        index++;
    }
    return newRecord;
}
