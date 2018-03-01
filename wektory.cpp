#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <conio.h>

using namespace std;

struct Wpis
{
    int ID;
    string imie;
    string nazwisko;
    string adres;
    string email;
    string nrTelefonu;
};

void wczytajDane(vector<Wpis> &dane);
void dodajRekord(vector<Wpis> &dane);
void pokazCalaKsiazke(vector<Wpis> dane);
void wypiszRekordyPoImieniu(vector<Wpis> dane);
void wypiszRekordyPoNazwisku(vector<Wpis> dane);
void zapiszDaneDoPliku(vector<Wpis> dane);
void usunRekord (vector<Wpis> &dane);
void edycjaRekordu (vector<Wpis> &dane);

int main()
{
    char opcja;
    vector<Wpis> dane;
    wczytajDane(dane);

    while(opcja!='7')
    {
        system("cls");
        cout<<"Ksiazka adresowa - menu glowne\n1. Wyszukaj po imieniu\n2. Wyszukaj po nazwisku\n3. Dodaj do kontaktow\n4. Edytuj kontakt\n5. Wyswietl wszystkie kontakty\n6. Usun kontakt\n7. Zakoncz program\n";
        opcja=getch();
        switch (opcja)
        {
        case '1':
            wypiszRekordyPoImieniu(dane);
            break;
        case '2':
            wypiszRekordyPoNazwisku(dane);
            break;
        case '3':
            dodajRekord(dane);
            break;
        case '4':
            edycjaRekordu(dane);
            break;
        case '5':
            pokazCalaKsiazke (dane);
            break;
        case '6':
            usunRekord (dane);
            break;
        case '7':
            zapiszDaneDoPliku(dane);
            break;
        default:
            cout<<"Nie ma takiej opcji\n";
            break;
        }
    }
    return 0;
}

void wczytajDane(vector<Wpis> &dane)
{
    dane.clear();
    fstream kontakty;
    string linia;
    kontakty.open("kontakty.txt",ios::in);
    if (kontakty)
    {
        if(ifstream("kontakty.txt", ios::ate).tellg()!=0)
        {
            while (!(kontakty.eof()))
            {
                Wpis *w_rekord=new Wpis;
                getline(kontakty,linia);
                stringstream ss(linia);
                getline(ss,w_rekord->imie,'|');//tymczasowo do konwersji na liczbêe
                w_rekord->ID=atoi(w_rekord->imie.c_str());
                getline(ss,w_rekord->imie,'|');
                getline(ss,w_rekord->nazwisko,'|');
                getline(ss,w_rekord->adres,'|');
                getline(ss,w_rekord->email,'|');
                getline(ss,w_rekord->nrTelefonu,'|');
                dane.push_back(*w_rekord);
                delete w_rekord;
            }
        }
        kontakty.close();
    }
}

void pokazCalaKsiazke(vector<Wpis> dane)
{
    system("cls");
    if (dane.empty())
    {
        cout<<"Ksiazka jest pusta\n\n";
    }
    else
    {
        vector<Wpis>::iterator indeks=dane.begin();

        while (indeks!=dane.end())
        {
            cout<<indeks->ID<<endl;
            cout<<indeks->imie<<endl;
            cout<<indeks->nazwisko<<endl;
            cout<<indeks->adres<<endl;
            cout<<indeks->email<<endl;
            cout<<indeks->nrTelefonu<<endl;
            indeks++;
        }
    }
    system("pause");
}

void dodajRekord(vector<Wpis> &dane)
{
    string tekstTymczasowy;
    vector<Wpis>::iterator indeks=dane.end();
    Wpis *w_rekord=new Wpis;

    if (dane.empty())
    {
        w_rekord->ID=1;
        cout<<"ID: "<<1<<endl;
    }
    if (!dane.empty())
    {
        indeks--;
        w_rekord->ID=indeks->ID+1;
        cout<<"ID: "<<w_rekord->ID<<endl;
    }
    cout<<"Podaj imie: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->imie=tekstTymczasowy;
    cout<<"Podaj nazwisko: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->nazwisko=tekstTymczasowy;
    cout<<"Podaj adres: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->adres=tekstTymczasowy;
    cout<<"Podaj email: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->email=tekstTymczasowy;
    cout<<"Podaj nr telefonu: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->nrTelefonu=tekstTymczasowy;

    dane.push_back(*w_rekord);
    delete w_rekord;
    system("pause");
}

void wypiszRekordyPoImieniu(vector<Wpis> dane)
{
    system("cls");
    string szukaneImie;
    bool czyZnaleziono=false;

    cin.sync();
    cout<<"Podaj imie: ";
    getline(cin,szukaneImie);
    vector<Wpis>::iterator indeks=dane.begin();
    system("cls");

    while (indeks!=dane.end())
    {
        if (indeks->imie==szukaneImie)
        {
            cout<<indeks->ID<<endl;
            cout<<indeks->imie<<endl;
            cout<<indeks->nazwisko<<endl;
            cout<<indeks->adres<<endl;
            cout<<indeks->email<<endl;
            cout<<indeks->nrTelefonu<<endl<<endl;
            czyZnaleziono=true;
        }
        indeks++;
    }
    if (czyZnaleziono==false) cout<<"Nie znaleziono osoby o takim imieniu\n\n";
    system("pause");
}

void wypiszRekordyPoNazwisku(vector<Wpis> dane)
{
    system("cls");
    string szukaneNazwisko;
    bool czyZnaleziono=false;

    cin.sync();
    cout<<"Podaj nazwisko: ";
    getline(cin,szukaneNazwisko);
    vector<Wpis>::iterator indeks=dane.begin();
    system("cls");

    while (indeks!=dane.end())
    {
        if (indeks->nazwisko==szukaneNazwisko)
        {
            cout<<indeks->ID<<endl;
            cout<<indeks->imie<<endl;
            cout<<indeks->nazwisko<<endl;
            cout<<indeks->adres<<endl;
            cout<<indeks->email<<endl;
            cout<<indeks->nrTelefonu<<endl<<endl;
            czyZnaleziono=true;
        }
        indeks++;
    }
    if (czyZnaleziono==false) cout<<"Nie znaleziono osoby o takim imieniu\n\n";
    system("pause");
}

void zapiszDaneDoPliku(vector<Wpis> dane)
{
    if (!dane.empty())
    {
        vector<Wpis>::iterator indeks=dane.begin();
        fstream kontakty;
        kontakty.open("kontakty.txt",ios::out);
        //ponizsze nie jest w petli, zeby nie zaczynac od endl
        kontakty<<indeks->ID<<"|"<<indeks->imie<<"|"<<indeks->nazwisko<<"|"<<indeks->adres<<"|"<<indeks->email<<"|"<<indeks->nrTelefonu;
        indeks++;
        while (indeks!=dane.end())
        {
            kontakty<<endl<<indeks->ID<<"|"<<indeks->imie<<"|"<<indeks->nazwisko<<"|"<<indeks->adres<<"|"<<indeks->email<<"|"<<indeks->nrTelefonu;
            indeks++;
        }
        kontakty.close();
    }
    else remove("kontakty.txt");
}

void usunRekord (vector<Wpis> &dane)
{
    vector<Wpis>::iterator indeks=dane.begin();
    int IDdoUsuniecia;
    char potwierdzenie='2';

    cin.sync();
    cout<<"Podaj ID: ";
    cin>>IDdoUsuniecia;

    while (indeks!=dane.end())
    {
        if (indeks->ID==IDdoUsuniecia)
        {
            cout<<indeks->ID<<endl;
            cout<<indeks->imie<<endl;
            cout<<indeks->nazwisko<<endl;
            cout<<indeks->adres<<endl;
            cout<<indeks->email<<endl;
            cout<<indeks->nrTelefonu<<endl<<endl;
            cout<<"Usunac kontakt?\n1. Usun\n2. Cofnij\n";
            potwierdzenie=getch();
        }
        if (potwierdzenie=='1')
        {
            dane.erase(indeks);
            break;
        }
        indeks++;
    }
}

void edycjaRekordu (vector<Wpis> &dane)
{
    vector<Wpis>::iterator indeks=dane.begin();
    int IDdoZmiany;
    char opcja;

    cin.sync();
    cout<<"Podaj ID: ";
    cin>>IDdoZmiany;

    while (indeks!=dane.end())
    {
        if (indeks->ID==IDdoZmiany)
        {
            cout<<indeks->ID<<endl;
            cout<<indeks->imie<<endl;
            cout<<indeks->nazwisko<<endl;
            cout<<indeks->adres<<endl;
            cout<<indeks->email<<endl;
            cout<<indeks->nrTelefonu<<endl<<endl;
            cout<<"1. Zmiana imienia\n2. Zmiana nazwiska\n3. Zmiana adresu\n4. Zmiana email'a\n5. Zmiana nr telefonu\n";
            opcja=getch();
            switch (opcja)
            {
            case '1':
                cout<<"Podaj nowe imie: ";
                cin>>indeks->imie;
                break;
            case '2':
                cout<<"Podaj nowe nazwisko: ";
                cin>>indeks->nazwisko;
                break;
            case '3':
                cout<<"Podaj nowy adres: ";
                cin>>indeks->adres;
                break;
            case '4':
                cout<<"Podaj nowy email: ";
                cin>>indeks->email;
                break;
            case '5':
                cout<<"Podaj nowy nr telefonu: ";
                cin>>indeks->nrTelefonu;
                break;
            default:
                cout<<"Nie ma takiej opcji\n";
                system("pause");
                break;
            }
        }
        indeks++;
    }
}
