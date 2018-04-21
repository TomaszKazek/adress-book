#include <iostream>
#include <vector>
#include <fstream>

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

class User:public Person
{
    string password;

public:
    string getPassword();
    void setPassword(string p);
};

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

class ListOfUsers
{

vector<User> usersList;
int userID, lastUserID;

public:
    ListOfUsers();
    int getUserID();
    void setUserID(int u);
    int logging();
    string addUser();
    vector<User> getUsersList();
};

class ListOfRecords
{
    vector<Record> recordsList;
    int lastID;

public:
    ListOfRecords(int userID);

    int getLastID();
    string addRecord(int userID);
    void showAllRecords();
    void findByName();
    void findByLastName();
    int deleteRecord();
    string editRecord(int userID);
};

class FileData
{
    fstream contacts;

public:
    void addRecord(string RecordToAdd);
    void editRecord(string RecordToEdit);
    void deleteRecord(int IDtoDelete);
};

class FileUsers
{
    fstream users;

public:
    void addUser(string newUser);
};
