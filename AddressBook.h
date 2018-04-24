#include <iostream>
#include <vector>
#include "Record.h"

using namespace std;

class AddressBook
{
    vector<Record> recordsList;
    int lastID;

public:
    AddressBook(int userID);

    int getLastID();
    string addRecord(int userID);
    void showAllRecords();
    void findByName();
    void findByLastName();
    int deleteRecord();
    string editRecord(int userID);
};
