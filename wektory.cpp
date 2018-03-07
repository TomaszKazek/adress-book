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
    int IDuzytkownika;
    string imie;
    string nazwisko;
    string adres;
    string email;
    string nrTelefonu;
};

struct Uzytkownik
{
    int ID;
    string nazwa;
    string haslo;
};

void wczytajUzytkownikow(vector<Uzytkownik> &uzytkownicy);
int zaloguj(vector<Uzytkownik> uzytkownicy);
void dodajUzytkownika(vector<Uzytkownik> &uzytkownicy);
void zapiszUzytkownikaDoPliku(vector<Uzytkownik> uzytkownicy);

void uruchomProgram(int IDuzytkownika);

int wczytajDane(vector<Wpis> &dane, int IDuzytkownika);
void dodajRekord(vector<Wpis> &dane, int IDuzytkownika, int ostatnieID);
void pokazCalaKsiazke(vector<Wpis> dane);
void wypiszRekordyPoImieniu(vector<Wpis> dane);
void wypiszRekordyPoNazwisku(vector<Wpis> dane);
void zapiszDaneDoPliku(vector<Wpis> dane);
void usunRekord (vector<Wpis> &dane);
void edycjaRekordu (vector<Wpis> &dane, int IDuzytkownika);
void usunRekordZPliku(int IDdoUsuniecia);
void edycjaRekorduWPliku(int IDdoZmiany, string nowyRekord);

int main()
{
    vector<Uzytkownik> uzytkownicy;
    wczytajUzytkownikow(uzytkownicy);

    char opcja='0';
    int IDuzytkownika=0;

    while(opcja!='3')
    {
        system("cls");
        cout<<"Ksiazka adresowa - menu glowne\n1. Logowanie\n2. Rejestracja\n3. Zamknij program\n";
        opcja=getch();
        switch (opcja)
        {
        case '1':
            IDuzytkownika=zaloguj(uzytkownicy);
            if (IDuzytkownika!=0)
                uruchomProgram(IDuzytkownika);
            break;
        case '2':
            dodajUzytkownika(uzytkownicy);
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

void wczytajUzytkownikow(vector<Uzytkownik> &uzytkownicy)
{
    uzytkownicy.clear();
    fstream zarejestrowaniUzytkownicy;
    string bufor;
    zarejestrowaniUzytkownicy.open("Uzytkownicy.txt",ios::in);
    if (zarejestrowaniUzytkownicy)
    {
        if(ifstream("Uzytkownicy.txt", ios::ate).tellg()!=0)
        {
            while (!(zarejestrowaniUzytkownicy.eof()))
            {
                Uzytkownik *w_uzytkownik=new Uzytkownik;
                getline(zarejestrowaniUzytkownicy,bufor);
                stringstream ss(bufor);
                getline(ss,w_uzytkownik->nazwa,'|');//tymczasowo do konwersji na liczbêe
                w_uzytkownik->ID=atoi(w_uzytkownik->nazwa.c_str());
                getline(ss,w_uzytkownik->nazwa,'|');
                getline(ss,w_uzytkownik->haslo,'|');
                uzytkownicy.push_back(*w_uzytkownik);
                delete w_uzytkownik;
            }
        }
        zarejestrowaniUzytkownicy.close();
    }
}

int zaloguj(vector<Uzytkownik> uzytkownicy)
{
    string nazwa, haslo;
    cout<<"Podaj nazwe uzytkownika: ";
    cin.sync();
    getline(cin, nazwa);

    vector<Uzytkownik>::iterator indeks=uzytkownicy.begin();

    while (indeks!=uzytkownicy.end())
    {
        if (nazwa==indeks->nazwa)
        {
            for(int i=0;i<3;i++)
            {
                cout<<"Podaj haslo: ";
                cin.sync();
                getline(cin,haslo);
            if (haslo==indeks->haslo)
            {
                system("cls");
                cout<<"Witaj "<<indeks->nazwa<<endl;
                system("pause");
                return indeks->ID;
            }
            else
                cout<<"Haslo niepoprawne\n";
            }
        }
        indeks++;
    }
    system("cls");
    cout<<"Proba logowania zakonczyla sie niepowodzeniem\n";
    system("pause");
    return 0;
}

void dodajUzytkownika(vector<Uzytkownik> &uzytkownicy)
{
    string tekstTymczasowy;
    vector<Uzytkownik>::iterator indeks=uzytkownicy.end();
    Uzytkownik *w_uzytkownik=new Uzytkownik;

    if (uzytkownicy.empty())
    {
        w_uzytkownik->ID=1;
        cout<<"ID: "<<1<<endl;
    }
    if (!uzytkownicy.empty())
    {
        indeks--;
        w_uzytkownik->ID=indeks->ID+1;
        cout<<"ID: "<<w_uzytkownik->ID<<endl;
    }
    cout<<"Podaj nazwe: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_uzytkownik->nazwa=tekstTymczasowy;
    cout<<"Podaj haslo: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_uzytkownik->haslo=tekstTymczasowy;

    uzytkownicy.push_back(*w_uzytkownik);
    delete w_uzytkownik;
    system("pause");
    zapiszUzytkownikaDoPliku(uzytkownicy);
}

void zapiszUzytkownikaDoPliku(vector<Uzytkownik> uzytkownicy)
{
    if (!uzytkownicy.empty())
    {
        vector<Uzytkownik>::iterator indeks=uzytkownicy.begin();
        fstream zarejestrowaniUzytkownicy;
        zarejestrowaniUzytkownicy.open("Uzytkownicy.txt",ios::out);
        //ponizsze nie jest w petli, zeby nie zaczynac od endl
        zarejestrowaniUzytkownicy<<indeks->ID<<"|"<<indeks->nazwa<<"|"<<indeks->haslo;
        indeks++;
        while (indeks!=uzytkownicy.end())
        {
            zarejestrowaniUzytkownicy<<endl<<indeks->ID<<"|"<<indeks->nazwa<<"|"<<indeks->haslo;
            indeks++;
        }
        zarejestrowaniUzytkownicy.close();
    }
    else remove("Uzytkownicy.txt");
}

void uruchomProgram(int IDuzytkownika)
{
    char opcja='0';
    vector<Wpis> dane;
    int ostatnieID=wczytajDane(dane, IDuzytkownika);

    while(opcja!='7')
    {
        system("cls");
        cout<<"Ksiazka adresowa - menu glowne\n1. Dodaj adresata\n2. Wyszukaj po imieniu\n3. Wyszukaj po nazwisku\n4. Pokaz wszystkich adresatow\n5. Usun adresata\n6. Edytuj adresata\n7. Wyloguj sie\n";
        opcja=getch();
        switch (opcja)
        {
        case '1':
            dodajRekord(dane, IDuzytkownika, ostatnieID);
            break;
        case '2':
            wypiszRekordyPoImieniu(dane);
            break;
        case '3':
            wypiszRekordyPoNazwisku(dane);
            break;
        case '4':
            pokazCalaKsiazke (dane);
            break;
        case '5':
            usunRekord (dane);
            break;
        case '6':
            edycjaRekordu(dane, IDuzytkownika);
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

int wczytajDane(vector<Wpis> &dane, int IDuzytkownika)
{
    dane.clear();
    fstream kontakty;
    string linia;
    int ostatnieID=0;
    kontakty.open("Adresaci.txt",ios::in);
    if (kontakty)
    {
        if(ifstream("Adresaci.txt", ios::ate).tellg()!=0)
        {
            while (!(kontakty.eof()))
            {
                Wpis *w_rekord=new Wpis;
                getline(kontakty,linia);
                stringstream ss(linia);
                getline(ss,w_rekord->imie,'|');//tymczasowo do konwersji na liczbêe
                w_rekord->ID=atoi(w_rekord->imie.c_str());
                getline(ss,w_rekord->imie,'|');//tymczasowo do konwersji na liczbêe
                w_rekord->IDuzytkownika=atoi(w_rekord->imie.c_str());
                getline(ss,w_rekord->imie,'|');
                getline(ss,w_rekord->nazwisko,'|');
                getline(ss,w_rekord->adres,'|');
                getline(ss,w_rekord->email,'|');
                getline(ss,w_rekord->nrTelefonu,'|');
                ostatnieID=w_rekord->ID;
                if (w_rekord->IDuzytkownika==IDuzytkownika)
                dane.push_back(*w_rekord);
                delete w_rekord;
            }
        }
        kontakty.close();
    }
    return ostatnieID;
}

void dodajRekord(vector<Wpis> &dane, int IDuzytkownika, int ostatnieID)
{
    string tekstTymczasowy;
    fstream kontakty;
    kontakty.open("Adresaci.txt",ios::out|ios::app);
    vector<Wpis>::iterator indeks=dane.end();
    Wpis *w_rekord=new Wpis;

    if(ifstream("Adresaci.txt", ios::ate).tellg()!=0)
        kontakty<<endl;

    w_rekord->ID=ostatnieID+1;
    kontakty<<w_rekord->ID<<"|";
    cout<<"ID: "<<w_rekord->ID<<endl;

    w_rekord->IDuzytkownika=IDuzytkownika;
    kontakty<<w_rekord->IDuzytkownika<<"|";

    cout<<"Podaj imie: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->imie=tekstTymczasowy;
    kontakty<<w_rekord->imie<<"|";

    cout<<"Podaj nazwisko: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->nazwisko=tekstTymczasowy;
    kontakty<<w_rekord->nazwisko<<"|";

    cout<<"Podaj adres: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->adres=tekstTymczasowy;
    kontakty<<w_rekord->adres<<"|";

    cout<<"Podaj email: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->email=tekstTymczasowy;
    kontakty<<w_rekord->email<<"|";

    cout<<"Podaj nr telefonu: ";
    cin.sync();
    getline(cin, tekstTymczasowy);
    w_rekord->nrTelefonu=tekstTymczasowy;
    kontakty<<w_rekord->nrTelefonu;

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
    usunRekordZPliku(IDdoUsuniecia);
}

void usunRekordZPliku(int IDdoUsuniecia)
{
    string tekstTymczasowy,IDzPliku;
    fstream kontakty, noweKontakty;
    kontakty.open("Adresaci.txt",ios::in);
    noweKontakty.open("NowiAdresaci.txt",ios::out);

    if (kontakty)
    {
    while (!(kontakty.eof()))
    {
    getline(kontakty,tekstTymczasowy);
    stringstream ss(tekstTymczasowy);
    getline(ss,IDzPliku,'|');
    if (atoi(IDzPliku.c_str())!=IDdoUsuniecia)
    {
        noweKontakty<<tekstTymczasowy<<endl;
    }
    }
    kontakty.close();
    noweKontakty.close();
    remove("Adresaci.txt");
    rename("NowiAdresaci.txt","Adresaci.txt");
    }
}

void edycjaRekordu (vector<Wpis> &dane, int IDuzytkownika)
{
    vector<Wpis>::iterator indeks=dane.begin();
    int IDdoZmiany;
    char opcja;
    string nowyRekord;

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
        stringstream ID;
        ID<<indeks->ID;
        nowyRekord=ID.str();
        ID.str("");
        ID<<IDuzytkownika;
        nowyRekord=nowyRekord+"|"+ID.str()+"|"+indeks->imie+"|"+indeks->nazwisko+"|"+indeks->adres+"|"+indeks->email+"|"+indeks->nrTelefonu;
        edycjaRekorduWPliku(IDdoZmiany, nowyRekord);
        }
        indeks++;
    }
}


void edycjaRekorduWPliku(int IDdoZmiany, string nowyRekord)
{
    string tekstTymczasowy,IDzPliku;
    fstream kontakty, noweKontakty;
    kontakty.open("Adresaci.txt",ios::in);
    noweKontakty.open("NowiAdresaci.txt",ios::out);

    if (kontakty)
    {
    while (!(kontakty.eof()))
    {
    getline(kontakty,tekstTymczasowy);
    stringstream ss(tekstTymczasowy);
    getline(ss,IDzPliku,'|');
    if (atoi(IDzPliku.c_str())==IDdoZmiany)
    {
        noweKontakty<<nowyRekord<<endl;
    }
    else
    {
        noweKontakty<<tekstTymczasowy<<endl;
    }
    }
    kontakty.close();
    noweKontakty.close();
    remove("Adresaci.txt");
    rename("NowiAdresaci.txt","Adresaci.txt");
    }
}
