#include "address_book.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <conio.h>

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

void User::setPassword(string p)
    {
password=p;
    }

    string User::getPassword()
    {
        return password;
    }

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

ListOfUsers::ListOfUsers()
{
    usersList.clear();
    fstream existingUsers;
    string buffer;
    existingUsers.open("Users.txt",ios::in);
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

int ListOfUsers::logging()
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

string ListOfUsers::addUser()
{
    string newUser, buffer;
    stringstream ss;
    vector<User>::iterator index=usersList.end();
    User *p_user=new User;

    p_user->setUserID(lastUserID+1);
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

vector<User> ListOfUsers::getUsersList()
{
    return usersList;
}

int ListOfUsers::getUserID()
{
    return userID;
}
void ListOfUsers::setUserID(int u)
{
    userID=u;
}

ListOfRecords::ListOfRecords(int userID)
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

int ListOfRecords::getLastID()
{
    return lastID;
}

string ListOfRecords::addRecord(int userID)
{
    string newRecord, buffer;
    stringstream ss;
    vector<Record>::iterator index=recordsList.end();
    Record *p_record=new Record;

    p_record->setID(lastID+1);
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

void ListOfRecords::showAllRecords()
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

void ListOfRecords::findByName()
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

void ListOfRecords::findByLastName()
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

int ListOfRecords::deleteRecord()
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

string ListOfRecords::editRecord(int userID)
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

void FileUsers::addUser(string newUser)
{
    users.open("Users.txt",ios::out|ios::app);
    if(ifstream("Users.txt", ios::ate).tellg()!=0)
        users<<endl;

        users<<newUser;

    users.close();
}
