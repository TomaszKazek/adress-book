#include <iostream>
#include <fstream>

using namespace std;

class FileData
{
    fstream contacts;

public:
    void addRecord(string RecordToAdd);
    void editRecord(string RecordToEdit);
    void deleteRecord(int IDtoDelete);
};

