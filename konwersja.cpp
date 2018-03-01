#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string nazwaPliku,nazwaNowegoPliku, bufor;
    getline(cin,nazwaPliku);
    if (nazwaPliku.substr(nazwaPliku.length()-4,nazwaPliku.length())!=".txt")
        nazwaPliku=nazwaPliku+".txt";
    nazwaNowegoPliku=nazwaPliku.substr(0,nazwaPliku.length()-4)+"_nowy_format.txt";

    fstream kontakty,noweKontakty;
    kontakty.open(nazwaPliku.c_str(),ios::in);
    noweKontakty.open(nazwaNowegoPliku.c_str(),ios::out);

    const int iloscLiniiwKontakcie=6;

    if(kontakty && noweKontakty)
    {
        if(ifstream(nazwaPliku.c_str(), ios::ate).tellg()!=0)
        {
            while (!(kontakty.eof()))
            {
                for (int i=1;i<iloscLiniiwKontakcie;i++)
                {
                    getline(kontakty,bufor);
                    noweKontakty<<bufor<<"|";
                }
                getline(kontakty,bufor);
                noweKontakty<<bufor<<endl;
            }
            cout<<"Utworzono plik "<<nazwaNowegoPliku<<" w nowym formacie\n";
        }
        else
            cout<<"Plik jest pusty";
    }
    else
        cout<<"Nie znaleziono pliku";
    return 0;
}

