#include <iostream>
#include <vector>
#include "User.h"

using namespace std;

class Users
{

vector<User> usersList;
int userID, lastUserID;

public:
    Users();
    int getUserID();
    void setUserID(int u);
    int logging();
    string addUser();
    vector<User> getUsersList();
};
