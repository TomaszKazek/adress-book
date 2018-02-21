#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Wpis
{
    int ID;
    string imie;
    string nazwisko;
    string adres;
    string email;
    string nrTelefonu; //jakby ktos koniecznie chcial "+" na poczatku np. +48
    Wpis *w_kolejnyWpis;
};

Wpis * wczytajDane(Wpis *wskaznikPierwszegoWpisu);
Wpis * wczytajKolejnyRekordZPliku (Wpis *wskaznikPierwszegoWpisu, fstream &kontakty);
Wpis * dodajRekordDoPliku(Wpis *wskaznikPierwszegoWpisu);
void pokazCalaKsiazke(Wpis *w_rekord);
void wypiszRekordyPoImieniu(Wpis *w_rekord);
void wypiszRekordyPoNazwisku(Wpis *w_rekord);

int main()
{
    Wpis *wskaznikPierwszegoWpisu=NULL;
    char opcja;

    while(opcja!='5')
    {
    wskaznikPierwszegoWpisu=NULL;
    wskaznikPierwszegoWpisu=wczytajDane(wskaznikPierwszegoWpisu);
    system("cls");
    cout<<"Ksiazka adresowa - menu glowne\n1. Wyszukaj po imieniu\n2. Wyszukaj po nazwisku\n3. Dodaj do kontaktow\n4. Wyswietl wszystkie kontakty\n5. Zakoncz program\n";
    cin>>opcja;
    switch (opcja)
    {
        case '1':
            wypiszRekordyPoImieniu(wskaznikPierwszegoWpisu);
            break;
        case '2':
            wypiszRekordyPoNazwisku(wskaznikPierwszegoWpisu);
            break;
        case '3':
            dodajRekordDoPliku(wskaznikPierwszegoWpisu);
            break;
        case '4':
            pokazCalaKsiazke (wskaznikPierwszegoWpisu);
            break;
        case '5':
            break;
        default:
            cout<<"Nie ma takiej opcji\n";
            break;
    }
    }
    return 0;
}

Wpis * wczytajDane(Wpis *wskaznikPierwszegoWpisu)
{
    fstream kontakty;
    string bufor;
    kontakty.open("kontakty.txt",ios::in);
    getline(kontakty,bufor);
    while (!(kontakty.eof()))
    {
        wskaznikPierwszegoWpisu=wczytajKolejnyRekordZPliku (wskaznikPierwszegoWpisu, kontakty);
    }
    kontakty.close();
    return wskaznikPierwszegoWpisu;
}

void pokazCalaKsiazke(Wpis *w_rekord)
{
    bool czyCosWypisano = false;
    system("cls");
    while (w_rekord!=NULL)
    {
    cout<<w_rekord->ID<<endl;
    cout<<w_rekord->imie<<endl;
    cout<<w_rekord->nazwisko<<endl;void wypiszRekordyPoImieniu(Wpis *w_rekord);
    cout<<w_rekord->adres<<endl;
    cout<<w_rekord->email<<endl;
    cout<<w_rekord->nrTelefonu<<endl;
    w_rekord=w_rekord->w_kolejnyWpis;
    czyCosWypisano = true;
    }
    if (czyCosWypisano == false) cout<<"Ksiazka jest pusta\n\n";
    system("pause");
}

Wpis * wczytajKolejnyRekordZPliku (Wpis *wskaznikPierwszegoWpisu, fstream &kontakty)
{
        Wpis *w_rekord=new Wpis;
        getline(kontakty,w_rekord->imie);//tymczasowo do konwersji na liczbêe
        w_rekord->ID=atoi(w_rekord->imie.c_str());
        getline(kontakty,w_rekord->imie);
        getline(kontakty,w_rekord->nazwisko);
        getline(kontakty,w_rekord->adres);
        getline(kontakty,w_rekord->email);
        getline(kontakty,w_rekord->nrTelefonu);
        w_rekord->w_kolejnyWpis=wskaznikPierwszegoWpisu;
        return w_rekord;
}

Wpis * dodajRekordDoPliku(Wpis *wskaznikPierwszegoWpisu)
{
    fstream kontakty;
    string bufor;
    kontakty.open("kontakty.txt",ios::out|ios::app);
    if (wskaznikPierwszegoWpisu==NULL)
    {
    kontakty<<endl<<1<<endl;
    cout<<"ID: "<<1<<endl;
    }
    if (wskaznikPierwszegoWpisu!=NULL)
    {
    kontakty<<endl<<wskaznikPierwszegoWpisu->ID+1<<endl;
    cout<<"ID: "<<wskaznikPierwszegoWpisu->ID+1<<endl;
    }
    cout<<"Podaj imie: ";
    cin.sync();
    getline(cin, bufor);
    kontakty<<bufor<<endl;
    cout<<"Podaj nazwisko: ";
    cin.sync();
    getline(cin, bufor);
    kontakty<<bufor<<endl;
    cout<<"Podaj adres: ";
    cin.sync();
    getline(cin, bufor);
    kontakty<<bufor<<endl;
    cout<<"Podaj email: ";
    cin.sync();
    getline(cin, bufor);
    kontakty<<bufor<<endl;
    cout<<"Podaj nr telefonu: ";
    cin.sync();
    getline(cin, bufor);
    kontakty<<bufor;
    kontakty.close();
    return wskaznikPierwszegoWpisu;
}

void wypiszRekordyPoImieniu(Wpis *w_rekord)
{
    system("cls");
    string szukaneImie;
    bool czyZnaleziono=false;
    cin.sync();
    cout<<"Podaj imie: ";
    getline(cin,szukaneImie);
    system("cls");
    while (w_rekord!=NULL)
    {
    if (w_rekord->imie==szukaneImie)
    {
    cout<<w_rekord->ID<<endl;
    cout<<w_rekord->imie<<endl;
    cout<<w_rekord->nazwisko<<endl;
    cout<<w_rekord->adres<<endl;
    cout<<w_rekord->email<<endl;
    cout<<w_rekord->nrTelefonu<<endl<<endl;
    czyZnaleziono=true;
    }
    w_rekord=w_rekord->w_kolejnyWpis;
    }
    if (czyZnaleziono==false) cout<<"Nie znaleziono osoby o takim imieniu\n\n";
    system("pause");
}

void wypiszRekordyPoNazwisku(Wpis *w_rekord)
{
    system("cls");
    string szukaneNazwisko;
    bool czyZnaleziono=false;
    cin.sync();
    cout<<"Podaj nazwisko: ";
    getline(cin,szukaneNazwisko);
    system("cls");
    while (w_rekord!=NULL)
    {
    if (w_rekord->nazwisko==szukaneNazwisko)
    {
    cout<<w_rekord->ID<<endl;
    cout<<w_rekord->imie<<endl;
    cout<<w_rekord->nazwisko<<endl;
    cout<<w_rekord->adres<<endl;
    cout<<w_rekord->email<<endl;
    cout<<w_rekord->nrTelefonu<<endl<<endl;
    czyZnaleziono=true;
    }
    w_rekord=w_rekord->w_kolejnyWpis;
    }
    if (czyZnaleziono==false) cout<<"Nie znaleziono osoby o takim imieniu\n\n";
    system("pause");
}
