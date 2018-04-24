#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "AddressBook.h"
#include "FileData.h"
#include "FileUsers.h"
#include "Person.h"
#include "Record.h"
#include "User.h"
#include "Users.h"

using namespace std;

void mainMenu(AddressBook &listR, int userID);

int main()
{
    Users listU;

    char option='0';

    while(option!='3')
    {
        system("cls");
        cout<<"Ksiazka adresowa - menu glowne\n1. Logowanie\n2. Rejestracja\n3. Zamknij program\n";
        option=getch();
        switch (option)
        {
        case '1':
            {
            listU.setUserID(listU.logging());
            if(listU.getUserID()!=0)
            {
            AddressBook *p_listR=new AddressBook (listU.getUserID());
            mainMenu(*p_listR, listU.getUserID());
            delete p_listR;
            }
            }
            break;
        case '2':
            {
            FileUsers *p_user = new FileUsers;
            p_user->addUser(listU.addUser());
            delete p_user;
            }
            break;
        case '3':
            break;
        default:
            cout<<"Nie ma takiej opcji\n";
            system("pause");
            break;
        }
    }
}

void mainMenu(AddressBook &listR, int UserID)
{
    char opcja='0';

    while(opcja!='7')
    {
        system("cls");
        cout<<"Ksiazka adresowa - menu glowne\n1. Dodaj adresata\n2. Wyszukaj po imieniu\n3. Wyszukaj po nazwisku\n4. Pokaz wszystkich adresatow\n5. Usun adresata\n6. Edytuj adresata\n7. Wyloguj sie\n";
        opcja=getch();
        switch (opcja)
        {
        case '1':
            {
            FileData *p_data = new FileData;
            p_data->addRecord(listR.addRecord(UserID));
            delete p_data;
            }
            break;
        case '2':
            listR.findByName();
            break;
        case '3':
            listR.findByLastName();
            break;
        case '4':
            listR.showAllRecords();
            break;
        case '5':
            {
            FileData *p_data = new FileData;
            p_data->deleteRecord(listR.deleteRecord());
            delete p_data;
            }
            break;
        case '6':
            {
            FileData *p_data = new FileData;
            p_data->editRecord(listR.editRecord(UserID));
            delete p_data;
            }
            break;
        case '7':
            break;

        default:
            cout<<"Nie ma takiej opcji\n";
            system("pause");
            break;
        }
    }
}
