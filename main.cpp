#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

struct Uzytkownik {
    int NumerIdUzytkownika;
    string NazwaUzytkownika;
    string HasloUzytkownika;
};

struct DaneZnajomego {
    int NumerIdZnajomego = 0, IdUzytkownika = 0;
    string ImieZnajomego = "",NazwiskoZnajomego = "",NumerTelefonuZnajomego = "",AdresEmailZnajomego = "",AdresDomowyZnajomego= "";
};

void WyswietlMenuLogowania ();
string wczytajLinie();
int wczytajLiczbeCalkowita();
void aktualizujPlikTekstowyPoZmianieHaslaUzytkownika (vector <Uzytkownik>& Uzytkownicy);
void zmianaHasla (vector <Uzytkownik> &Uzytkownicy, int IdUzytkownika);
char wczytajPojedynczyZnak();
bool SprawdzCzyNazwaUzytkownikaJestZajeta (string NazwaUzytkownika, vector <Uzytkownik> &Uzytkownicy);
void zapiszUzytkownikaDoPliku (Uzytkownik DodawanyUzytkownik);
void RejestracjaUzytkownika (vector <Uzytkownik> &Uzytkownicy);
vector < Uzytkownik > WczytajUzytkownikow();
int Logowanie (vector <Uzytkownik> &Uzytkownicy);
void WyswietlMenuGlowne ();
char wczytajZnak();
void zapiszZnajomegoDoPliku (DaneZnajomego DodawanyZnajomy);
int wczytajOstatnieIdZPliku();
void DodajZnajomego (vector <DaneZnajomego> & WszyscyZnajomi, int IdUzytkownika);
vector<DaneZnajomego> wczytajZnajomegoZPliku(int IdUzytkownika);
void wypiszZnajomego (vector <DaneZnajomego> & WszyscyZnajomi);
void WyszukajPoImieniu (vector <DaneZnajomego> & WszyscyZnajomi);
void WyszukajPoNazwisku (vector <DaneZnajomego> & WszyscyZnajomi);
void aktualizujPlikTekstowyPoUsunieciuWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int IdUsunietegoWpisu);
void usunWpis (vector <DaneZnajomego> & WszyscyZnajomi);
void WyswietlMenuEdycjiWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int numerOsobyDoEdycji);
void WyswietlUzytkownikaPoEdycji (vector <DaneZnajomego> & WszyscyZnajomi, int numerOsobyDoEdycji);
void edytujWpis (vector <DaneZnajomego> & WszyscyZnajomi);
bool CzyPlikIstnieje ();
void aktualizujPlikTekstowyPoDodaniuAdresata (vector <DaneZnajomego> & WszyscyZnajomi, int IdDodanegoAdresata);
void aktualizujPlikTekstowyPoEdycjiWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int IdEdytowanegoWpisu, int numerEdytowanegoWpisu);

int main() {

    vector <DaneZnajomego> WszyscyZnajomi;
    bool plik;
    char wyborMenuLogowania;
    char wyborMenuGlowne;
    int IdUzytkownika;
    vector <Uzytkownik> Uzytkownicy;
    int NumerIDEdytowanegoAdresata;
    Uzytkownik DodawanyUzytkownik;


    while (true) {
        Uzytkownicy = WczytajUzytkownikow();

        WyswietlMenuLogowania ();
        cout << "Twoj wybor: " << endl;
        wyborMenuLogowania = wczytajPojedynczyZnak();

        switch (wyborMenuLogowania) {
        case '1':
            system("cls");
            IdUzytkownika = Logowanie (Uzytkownicy);
            if (IdUzytkownika != 0) {
                plik = CzyPlikIstnieje();

                if (plik == 1 ) {
                    WszyscyZnajomi = wczytajZnajomegoZPliku(IdUzytkownika);
                }

                while(wyborMenuLogowania == '1') {
                    cin.sync();
                    WyswietlMenuGlowne();

                    wyborMenuGlowne = wczytajZnak();

                    system("cls");

                    switch (wyborMenuGlowne) {
                    case '1':
                        DodajZnajomego (WszyscyZnajomi,IdUzytkownika);
                        break;
                    case '2':
                        WyszukajPoImieniu(WszyscyZnajomi);
                        break;
                    case '3':
                        WyszukajPoNazwisku(WszyscyZnajomi);
                        break;
                    case '4':
                        wypiszZnajomego(WszyscyZnajomi);
                        break;
                    case '5':
                        usunWpis(WszyscyZnajomi);
                        break;
                    case '6':
                        edytujWpis(WszyscyZnajomi);
                        break;
                    case '7':
                        zmianaHasla (Uzytkownicy, IdUzytkownika);
                        break;
                    case '8':
                        wyborMenuLogowania = '0';
                        break;
                    default:
                        cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;
                        break;
                    }
                }
            }
            break;
        case '2':
            RejestracjaUzytkownika (Uzytkownicy);
            break;
        case '3':
            exit(0);
            break;
        default:
            cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;
            system("pause");
        }
    }

    return 0;
}

void WyswietlMenuLogowania () {
    system("cls");
    cout << "1.Logowanie" << endl;
    cout << "2.Rejestracja" << endl;
    cout << "3.Zamknij program" << endl;
}
string wczytajLinie() {
    string Linia;
    cin.sync();
    getline(cin,Linia);
    return Linia;
}
int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;

    while (true) {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return liczba;
}
void aktualizujPlikTekstowyPoZmianieHaslaUzytkownika (vector <Uzytkownik>& Uzytkownicy) {

    fstream UzytkownicyPlik;

    UzytkownicyPlik.open("Uzytkownicy.txt", ios::out);

    for(vector <Uzytkownik> :: iterator itr = Uzytkownicy.begin(); itr != Uzytkownicy.end(); itr++) {

        UzytkownicyPlik << itr -> NumerIdUzytkownika << "|";
        UzytkownicyPlik << itr -> NazwaUzytkownika << "|";
        UzytkownicyPlik << itr -> HasloUzytkownika << "|" << endl;
    }

    UzytkownicyPlik.close();
}
void zmianaHasla (vector <Uzytkownik> &Uzytkownicy, int IdUzytkownika) {

    string stareHaslo;
    string noweHaslo;

    cout << "Podaj stare haslo:" << endl;
    cout << "IdUzytkownika "<< IdUzytkownika << endl;
    stareHaslo = wczytajLinie();

    for (vector<Uzytkownik>::iterator itr = Uzytkownicy.begin(); itr != Uzytkownicy.end(); itr++) {

        if(itr -> NumerIdUzytkownika == IdUzytkownika) {
            if (itr -> HasloUzytkownika == stareHaslo) {
                cout << "Podaj nowe haslo: " << endl;
                noweHaslo = wczytajLinie();
                itr -> HasloUzytkownika = noweHaslo;
                aktualizujPlikTekstowyPoZmianieHaslaUzytkownika(Uzytkownicy);
                cout << "Haslo zostalo zmienione" << endl;
                break;
            }
        else{
            cout << "Bledne haslo" << endl;
        system("pause");
        break;
        }
    }

    }
    system("pause");
}
char wczytajPojedynczyZnak() {

    string wejscie = "";
    char znak  = {0};

    while (true) {
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;

    }
    return znak;
}
bool SprawdzCzyNazwaUzytkownikaJestZajeta (string NazwaUzytkownika, vector <Uzytkownik> &Uzytkownicy) {

    bool WynikTestu;

    if (Uzytkownicy.size() == 0)
        WynikTestu = false;
    else {
        for(int i = 0; i <= Uzytkownicy.size() - 1 ; i++) {
            if (NazwaUzytkownika == Uzytkownicy[i].NazwaUzytkownika) {
                cout << "Nazwa uzytkownika jest zajeta" << endl;
                system("pause");
                WynikTestu = true;
                break;
            } else
                WynikTestu = false;
        }
    }
    return WynikTestu;
}
void zapiszUzytkownikaDoPliku (Uzytkownik DodawanyUzytkownik) {

    fstream UzytkownicyPlik;

    UzytkownicyPlik.open("Uzytkownicy.txt", ios::out | ios::app);

    UzytkownicyPlik << DodawanyUzytkownik.NumerIdUzytkownika << "|";
    UzytkownicyPlik << DodawanyUzytkownik.NazwaUzytkownika << "|";
    UzytkownicyPlik << DodawanyUzytkownik.HasloUzytkownika << "|" << endl;

    UzytkownicyPlik.close();

}
void RejestracjaUzytkownika (vector <Uzytkownik> &Uzytkownicy) {

    Uzytkownik DodawanyUzytkownik;
    bool CzyNazwaUzytkownikaJestZajeta;

    if (Uzytkownicy.size() == 0)
        DodawanyUzytkownik.NumerIdUzytkownika = 1;
    else
        DodawanyUzytkownik.NumerIdUzytkownika = Uzytkownicy.size() + 1;

    do {
        system ("cls");
        cout << "Podaj nazwe uzytkownika" << endl;
        DodawanyUzytkownik.NazwaUzytkownika = wczytajLinie();
        CzyNazwaUzytkownikaJestZajeta = SprawdzCzyNazwaUzytkownikaJestZajeta (DodawanyUzytkownik.NazwaUzytkownika,Uzytkownicy);
    } while(CzyNazwaUzytkownikaJestZajeta == true);


    cout << "Podaj haslo" << endl;
    DodawanyUzytkownik.HasloUzytkownika = wczytajLinie();

    zapiszUzytkownikaDoPliku(DodawanyUzytkownik);

    cout << "Zarejestrowano uzytkownika: " << DodawanyUzytkownik.NazwaUzytkownika << endl;
    system("pause");

}
vector < Uzytkownik > WczytajUzytkownikow () {

    Uzytkownik WczytywanyUzytkownik;
    vector < Uzytkownik > WszyscyUzytkownicy;
    string LiniaPlikuDoWczytania;
    size_t znalezionaPozycja = 0;
    string numerID;

    fstream UzytkownicyPlik;

    UzytkownicyPlik.open ("Uzytkownicy.txt", ios::in);

    while (getline(UzytkownicyPlik,LiniaPlikuDoWczytania)) {
        znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

        if (znalezionaPozycja != std::string::npos) {
            numerID = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            WczytywanyUzytkownik.NumerIdUzytkownika = atoi(numerID.c_str());
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            WczytywanyUzytkownik.NazwaUzytkownika = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            WczytywanyUzytkownik.HasloUzytkownika = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
        }
        WszyscyUzytkownicy.push_back(WczytywanyUzytkownik);
    }
    return WszyscyUzytkownicy;
}
int Logowanie (vector <Uzytkownik> &Uzytkownicy) {

    string NazwaLogowanie;
    string HasloLogowanie;
    int IdUzytkownika;


    cout << "Wpisz nazwe uzytkownika" << endl;
    NazwaLogowanie = wczytajLinie();

    cout << "Podaj haslo" << endl;
    HasloLogowanie = wczytajLinie();

    if(Uzytkownicy.size() == 0) {
        cout << "Brak uzytkownikow w bazie, przejdz do rejestracji." << endl;
        cout << endl;
        system("pause");
        return 0;
    }

    for (int i = 0; i <= Uzytkownicy.size() + 1; i++) {
        if(NazwaLogowanie == Uzytkownicy[i].NazwaUzytkownika) {
            if (HasloLogowanie == Uzytkownicy[i].HasloUzytkownika) {
                cout << "Nazwa i haslo sa poprawne. Udalo sie zalogowac." << endl;
                IdUzytkownika = Uzytkownicy[i].NumerIdUzytkownika;
                break;
            } else {
                IdUzytkownika = 0;
            }
            break;
        } else {
            IdUzytkownika = 0;

        }
    }
    if (IdUzytkownika == 0) {
        cout << "Bledna nazwa uzytkownika lub haslo" << endl;

    }

    system("pause");
    return IdUzytkownika;
}
void WyswietlMenuGlowne () {

    system("cls");

    cout << "KSIAZKA ADRESOWA" << endl;
    cout << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow " << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "8. Wyloguj sie" << endl;
    cout << endl;
    cout << "Twoj wybor: " << endl;
}
char wczytajZnak() {

    string wejscie = "";
    char znak  = {0};

    while (true) {
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        //cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;
    }
    return znak;
}
void zapiszZnajomegoDoPliku (DaneZnajomego DodawanyZnajomy) {

    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt", ios::out | ios::app );

    adressBook << DodawanyZnajomy.NumerIdZnajomego << "|";
    adressBook << DodawanyZnajomy.IdUzytkownika << "|";
    adressBook << DodawanyZnajomy.ImieZnajomego << "|";
    adressBook << DodawanyZnajomy.NazwiskoZnajomego << "|";
    adressBook << DodawanyZnajomy.NumerTelefonuZnajomego << "|";
    adressBook << DodawanyZnajomy.AdresEmailZnajomego << "|";
    adressBook << DodawanyZnajomy.AdresDomowyZnajomego << "|" << endl;

    adressBook.close();

}
int wczytajOstatnieIdZPliku() {


    string LiniaPlikuDoWczytania;
    size_t znalezionaPozycja = 0;
    string numerIDosoby;
    int OstatnieId;
    string OstatniaLinia;

    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt", ios::in);

    while (getline(adressBook,LiniaPlikuDoWczytania)) {
        OstatniaLinia = LiniaPlikuDoWczytania;
    }

    znalezionaPozycja = OstatniaLinia.find("|");

    if( znalezionaPozycja != std::string::npos ) {
        numerIDosoby = OstatniaLinia.substr(0,znalezionaPozycja);
        OstatnieId = atoi(numerIDosoby.c_str());
    } else
        OstatnieId = 0;

    adressBook.close();

    return OstatnieId;
}
void DodajZnajomego (vector <DaneZnajomego> & WszyscyZnajomi, int IdUzytkownika) {

    DaneZnajomego DodawanyZnajomy;

    system("cls");
    cout << "Wprowadz imie" << endl;
    DodawanyZnajomy.ImieZnajomego = wczytajLinie();
    DodawanyZnajomy.NumerIdZnajomego = wczytajOstatnieIdZPliku() + 1;;
    DodawanyZnajomy.IdUzytkownika = IdUzytkownika;

    cout << "Wprowadz nazwisko" << endl;
    DodawanyZnajomy.NazwiskoZnajomego = wczytajLinie();

    cout << "Wprowadz numer telefonu" << endl;
    DodawanyZnajomy.NumerTelefonuZnajomego = wczytajLinie();

    cout << "Wprowadz email" << endl;
    DodawanyZnajomy.AdresEmailZnajomego = wczytajLinie();

    cout << "Wprowadz adres" << endl;
    DodawanyZnajomy.AdresDomowyZnajomego = wczytajLinie();

    cout << endl;
    WszyscyZnajomi.push_back(DodawanyZnajomy);

    zapiszZnajomegoDoPliku(DodawanyZnajomy);

    cout << "Wpis " << DodawanyZnajomy.ImieZnajomego << " " << DodawanyZnajomy.NazwiskoZnajomego << " zostal dodany do Ksiazki Adresowej.";
    cout << endl;

    system("pause");

}
vector<DaneZnajomego> wczytajZnajomegoZPliku(int IdUzytkownika) {

    DaneZnajomego WczytywanyZnajomy;
    vector <DaneZnajomego> WszyscyZnajomi;
    string LiniaPlikuDoWczytania;
    size_t znalezionaPozycja = 0;
    string numerIDosoby;
    string numerIDUzytkownika;


    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt", ios::in);

    while (getline(adressBook,LiniaPlikuDoWczytania)) {
        znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

        if( znalezionaPozycja != std::string::npos ) {
            numerIDosoby = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            WczytywanyZnajomy.NumerIdZnajomego = atoi(numerIDosoby.c_str());
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            numerIDUzytkownika = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            WczytywanyZnajomy.IdUzytkownika = atoi(numerIDUzytkownika.c_str());
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            WczytywanyZnajomy.ImieZnajomego = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            WczytywanyZnajomy.NazwiskoZnajomego = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            WczytywanyZnajomy.NumerTelefonuZnajomego = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            WczytywanyZnajomy.AdresEmailZnajomego = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            WczytywanyZnajomy.AdresDomowyZnajomego = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);

            if (WczytywanyZnajomy.IdUzytkownika == IdUzytkownika)
                WszyscyZnajomi.push_back(WczytywanyZnajomy);
        }


    }
    adressBook.close();
    return WszyscyZnajomi;
}
void wypiszZnajomego (vector <DaneZnajomego> & WszyscyZnajomi) {
    int iloscOsob = 1;

    if(WszyscyZnajomi.size() == 0)
        cout << "Brak wpisow." << endl;
    else {
        for ( DaneZnajomego &e : WszyscyZnajomi ) {
            cout << iloscOsob << endl;
            iloscOsob++;
            cout <<"ID: "<< e.NumerIdZnajomego << endl;
            //cout <<"ID uzytkownika " <<e.IdUzytkownika << endl;
            cout << e.ImieZnajomego <<" "<< e.NazwiskoZnajomego << endl;
            cout <<"Numer telefonu: "<< e.NumerTelefonuZnajomego << endl;
            cout <<"E-mail: "<< e.AdresEmailZnajomego << endl;
            cout <<"Adres: "<< e.AdresDomowyZnajomego << endl;
            cout << endl;
        }
    }
    system("pause");
}
void WyszukajPoImieniu (vector <DaneZnajomego> & WszyscyZnajomi) {

    string imieDoWyszukania;
    int liczbaOsobOPodanymImieniu = 0;

    cout << "Wyszukiwanie osobu po imieniu" << endl;
    cout << endl;
    cout << "Wpisz imie do wyszukania: " << endl;

    imieDoWyszukania = wczytajLinie();

    system("cls");

    if(WszyscyZnajomi.size() == 0)
        cout << "Brak wpisow." << endl;
    else {

        for (int i = 0; i < WszyscyZnajomi.size(); i++) {

            if(imieDoWyszukania == WszyscyZnajomi[i].ImieZnajomego) {
                liczbaOsobOPodanymImieniu ++;

                cout <<"ID: "<< WszyscyZnajomi[i].NumerIdZnajomego << endl;
                cout << WszyscyZnajomi[i].ImieZnajomego << " " << WszyscyZnajomi[i].NazwiskoZnajomego  << endl;
                cout <<"Numer telefonu: "<< WszyscyZnajomi[i].NumerTelefonuZnajomego << endl;
                cout <<"E-mail: "<< WszyscyZnajomi[i].AdresEmailZnajomego << endl;
                cout <<"Adres: "<< WszyscyZnajomi[i].AdresDomowyZnajomego << endl;
                cout << endl;
            }
        }
        if (liczbaOsobOPodanymImieniu < 1)
            cout << "Brak osob o podanym imieniu"<< endl;
    }
    cout << "Liczba osob o podanym imieniu: " << liczbaOsobOPodanymImieniu << endl;
    system("pause");

}
void WyszukajPoNazwisku (vector <DaneZnajomego> & WszyscyZnajomi) {

    string nazwiskoDoWyszukania;
    int liczbaOsobOPodanymNazwisku = 0;


    cout << "Wyszukiwanie osobu po nazwisku" << endl;
    cout << endl;
    cout << "Wpisz nazwisko do wyszukania: " << endl;

    nazwiskoDoWyszukania = wczytajLinie();

    system("cls");

    if(WszyscyZnajomi.size() == 0)
        cout << "Brak wpisow." << endl;
    else {

        for (int i = 0; i < WszyscyZnajomi.size(); i++) {

            if(nazwiskoDoWyszukania == WszyscyZnajomi[i].NazwiskoZnajomego) {
                liczbaOsobOPodanymNazwisku++;
                cout <<"ID: "<< WszyscyZnajomi[i].NumerIdZnajomego << endl;
                cout << WszyscyZnajomi[i].ImieZnajomego << " " << WszyscyZnajomi[i].NazwiskoZnajomego  << endl;
                cout <<"Numer telefonu: "<< WszyscyZnajomi[i].NumerTelefonuZnajomego << endl;
                cout <<"E-mail: "<< WszyscyZnajomi[i].AdresEmailZnajomego << endl;
                cout <<"Adres: "<< WszyscyZnajomi[i].AdresDomowyZnajomego << endl;
                cout << endl;

            }

        }
        if (liczbaOsobOPodanymNazwisku < 1)
            cout << "Brak osob o podanym nazwisku"<< endl;
    }
    cout << "Liczba osob o podanym nazwisku: "<< liczbaOsobOPodanymNazwisku << endl;
    system("pause");
}
void aktualizujPlikTekstowyPoUsunieciuWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int IdUsunietegoWpisu) {

    fstream AdressBook;
    fstream AdressBookTemp;
    string LiniaPlikuDoWczytania;
    size_t znalezionaPozycja;
    string numerIDosoby;
    DaneZnajomego WczytywanyZnajomy;

    AdressBook.open("ksiazkaAdresowa.txt", ios::in);
    AdressBookTemp.open("ksiazkaAdresowaTemp.txt", ios::out | ios::app);


    while (getline(AdressBook,LiniaPlikuDoWczytania)) {
        znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

        if (znalezionaPozycja != std::string::npos) {
            numerIDosoby = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            WczytywanyZnajomy.NumerIdZnajomego = atoi(numerIDosoby.c_str());
        }
        if (WczytywanyZnajomy.NumerIdZnajomego == IdUsunietegoWpisu) {
            continue;
        } else
            AdressBookTemp << LiniaPlikuDoWczytania << endl;
    }
    AdressBook.close();
    AdressBookTemp.close();
    remove ("ksiazkaAdresowa.txt");
    //cout << "usunieto ksiazkaAdresowa.txt" << endl;

    //system("pause");
    rename ("ksiazkaAdresowaTemp.txt","ksiazkaAdresowa.txt");
    //cout << "zmieniono nazwe ksiazkaAdresowaTemp na ksiazkaAdresowa.txt" << endl;
    //system("pause");

}
void usunWpis (vector <DaneZnajomego> & WszyscyZnajomi) {

    int numerOsobyDoUsuniecia;
    char potwierdzenie;
    int IdUsunietegoWpisu;

    if(WszyscyZnajomi.size() == 0)
        cout << "Brak wpisow." << endl;
    else {

        for (int i = 0; i < WszyscyZnajomi.size(); i++) {
            cout << i + 1 << " " << WszyscyZnajomi[i].ImieZnajomego << " " << WszyscyZnajomi[i].NazwiskoZnajomego << endl;
        }

        cout << endl;
        cout << "Ktory wpis usunac (wpisz odpowiedni numer) ?" << endl;

        do {
            numerOsobyDoUsuniecia = wczytajLiczbeCalkowita();

            if(numerOsobyDoUsuniecia < 1 || numerOsobyDoUsuniecia >= WszyscyZnajomi.size()+1)
                cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;

        }while (numerOsobyDoUsuniecia < 1 || numerOsobyDoUsuniecia >= WszyscyZnajomi.size()+1);

        cout << endl;
        cout << "Jestes pewien, ze chcesz usunac wpis "<< numerOsobyDoUsuniecia <<", jesli tak wcisnij: t " <<  endl;

        cin >> potwierdzenie;

        vector <DaneZnajomego>::iterator it;

        it = WszyscyZnajomi.begin() + numerOsobyDoUsuniecia - 1;

        IdUsunietegoWpisu = it-> NumerIdZnajomego;

        if (potwierdzenie == 't') {
            WszyscyZnajomi.erase (it);
            aktualizujPlikTekstowyPoUsunieciuWpisu(WszyscyZnajomi, IdUsunietegoWpisu);
            cout << "Wpis zostal usuniety";
            cout << endl;
        } else {
            cout << "Wpis nie zostal usuniety";
            cout << endl;
        }
    }
    system("pause");
}
void WyswietlMenuEdycjiWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int numerOsobyDoEdycji) {
    system("cls");

    cout << "Ktora dana chcesz zmienic?" << endl;
    cout <<"1 - Imie: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].ImieZnajomego << endl;
    cout <<"2 - Nazwisko: "<< WszyscyZnajomi[numerOsobyDoEdycji- 1].NazwiskoZnajomego << endl;
    cout <<"3 - Numer telefonu: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerTelefonuZnajomego << endl;
    cout <<"4 - Adres e-mial: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresEmailZnajomego << endl;
    cout <<"5 - Adres domowy: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresDomowyZnajomego << endl;
    cout <<"6 - powrot do menu" << endl;
    cout << endl;
}
void WyswietlUzytkownikaPoEdycji (vector <DaneZnajomego> & WszyscyZnajomi, int numerOsobyDoEdycji) {

    cout << "Wpis zostal zmieniony" << endl;
    cout << endl;
    cout <<"1 - Imie: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].ImieZnajomego << endl;
    cout <<"2 - Nazwisko: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].NazwiskoZnajomego << endl;
    cout <<"3 - Numer telefonu: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerTelefonuZnajomego << endl;
    cout <<"4 - Adres e-mial: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresEmailZnajomego << endl;
    cout <<"5 - Adres domowy: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresDomowyZnajomego << endl;
    cout << endl;

}
void edytujWpis (vector <DaneZnajomego> & WszyscyZnajomi) {

    int numerOsobyDoEdycji;
    int zmiana;
    string NowaDana;

    if(WszyscyZnajomi.size() == 0)
        cout << "Brak wpisow." << endl;
    else {

        cout << "Kogo dane chcesz edytowac (wybierz odpowiedni numer?)" << endl;
        cout << endl;

        for (int i = 0; i < WszyscyZnajomi.size(); i++) {
            cout << i + 1 << " " << WszyscyZnajomi[i].ImieZnajomego << " " << WszyscyZnajomi[i].NazwiskoZnajomego << endl;
        }

        do {
            numerOsobyDoEdycji = wczytajLiczbeCalkowita();

            if(numerOsobyDoEdycji < 1 || numerOsobyDoEdycji >= WszyscyZnajomi.size()+1)
                cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;

        } while (numerOsobyDoEdycji < 1 || numerOsobyDoEdycji >= WszyscyZnajomi.size()+1);


        WyswietlMenuEdycjiWpisu(WszyscyZnajomi, numerOsobyDoEdycji);

        do {
            zmiana = wczytajLiczbeCalkowita();

            switch (zmiana) {

            case 1:
                cout << "Wprowadz nowe imie" << endl;
                WszyscyZnajomi[numerOsobyDoEdycji - 1].ImieZnajomego = wczytajLinie();
                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,numerOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerIdZnajomego,numerOsobyDoEdycji);
                break;
            case 2:
                cout << "Wprowadz nowe nazwisko" << endl;
                WszyscyZnajomi[numerOsobyDoEdycji - 1].NazwiskoZnajomego = wczytajLinie();
                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,numerOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerIdZnajomego,numerOsobyDoEdycji);
                break;
            case 3:
                cout << "Wprowadz nowy numer telefonu" << endl;
                WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerTelefonuZnajomego = wczytajLinie();
                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,numerOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerIdZnajomego,numerOsobyDoEdycji);
                break;
            case 4:
                cout << "Wprowadz nowy adres email" << endl;
                WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresEmailZnajomego = wczytajLinie();
                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,numerOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerIdZnajomego,numerOsobyDoEdycji);
                break;
            case 5:
                cout << "Wprowadz nowy adres domowy" << endl;
                WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresDomowyZnajomego = wczytajLinie();
                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,numerOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerIdZnajomego,numerOsobyDoEdycji);
                break;
            case 6:
                break;
            default:
                cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie.";
                cout << endl;
            }

        } while (zmiana < 1 || zmiana > 6);

    }
    system("pause");
}
bool CzyPlikIstnieje () {

    bool plik;
    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt",ios::in);

    if (adressBook.good() == true)
        plik = true;
    else
        plik = false;

    adressBook.close();

    return plik;
}
void aktualizujPlikTekstowyPoDodaniuAdresata (vector <DaneZnajomego> & WszyscyZnajomi, int IdDodanegoAdresata) {

    DaneZnajomego ZapisywanyZnajomy;
    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    ZapisywanyZnajomy.NumerIdZnajomego = WszyscyZnajomi[WszyscyZnajomi.size() - 1].NumerIdZnajomego;
    ZapisywanyZnajomy.IdUzytkownika = WszyscyZnajomi[WszyscyZnajomi.size() - 1].IdUzytkownika;
    ZapisywanyZnajomy.ImieZnajomego = WszyscyZnajomi[WszyscyZnajomi.size() - 1].ImieZnajomego;
    ZapisywanyZnajomy.NazwiskoZnajomego = WszyscyZnajomi[WszyscyZnajomi.size() - 1].NazwiskoZnajomego;
    ZapisywanyZnajomy.NumerTelefonuZnajomego = WszyscyZnajomi[WszyscyZnajomi.size() - 1].NumerTelefonuZnajomego;
    ZapisywanyZnajomy.AdresEmailZnajomego = WszyscyZnajomi[WszyscyZnajomi.size() - 1].AdresEmailZnajomego;
    ZapisywanyZnajomy.AdresDomowyZnajomego = WszyscyZnajomi[WszyscyZnajomi.size() - 1].AdresDomowyZnajomego;


    adressBook << ZapisywanyZnajomy.NumerIdZnajomego << "|";
    adressBook << ZapisywanyZnajomy.IdUzytkownika << "|";
    adressBook << ZapisywanyZnajomy.ImieZnajomego << "|";
    adressBook << ZapisywanyZnajomy.NazwiskoZnajomego << "|";
    adressBook << ZapisywanyZnajomy.NumerTelefonuZnajomego << "|";
    adressBook << ZapisywanyZnajomy.AdresEmailZnajomego << "|";
    adressBook << ZapisywanyZnajomy.AdresDomowyZnajomego << "|" << endl;

    adressBook.close();


}
void aktualizujPlikTekstowyPoEdycjiWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int IdEdytowanegoWpisu, int numerEdytowanegoWpisu) {

    fstream AdressBook;
    fstream AdressBookTemp;
    string LiniaPlikuDoWczytania;
    size_t znalezionaPozycja;
    string numerIDosoby;
    DaneZnajomego WczytywanyZnajomy;

    AdressBook.open("ksiazkaAdresowa.txt", ios::in);
    AdressBookTemp.open("ksiazkaAdresowaTemp.txt", ios::out | ios::app);

    while (getline(AdressBook,LiniaPlikuDoWczytania)) {
        znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

        if (znalezionaPozycja != std::string::npos) {
            numerIDosoby = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            WczytywanyZnajomy.NumerIdZnajomego = atoi(numerIDosoby.c_str());
        }
        if (WczytywanyZnajomy.NumerIdZnajomego == IdEdytowanegoWpisu) {

            AdressBookTemp << WszyscyZnajomi[numerEdytowanegoWpisu - 1].NumerIdZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[numerEdytowanegoWpisu - 1].IdUzytkownika << "|";
            AdressBookTemp << WszyscyZnajomi[numerEdytowanegoWpisu - 1].ImieZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[numerEdytowanegoWpisu - 1].NazwiskoZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[numerEdytowanegoWpisu - 1].NumerTelefonuZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[numerEdytowanegoWpisu - 1].AdresEmailZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[numerEdytowanegoWpisu - 1].AdresDomowyZnajomego << "|" << endl;
        } else
            AdressBookTemp << LiniaPlikuDoWczytania << endl;
    }
    AdressBook.close();
    AdressBookTemp.close();
    remove ("ksiazkaAdresowa.txt");
    //cout << "usunieto ksiazkaAdresowa.txt" << endl;

    //system("pause");
    rename ("ksiazkaAdresowaTemp.txt","ksiazkaAdresowa.txt");
    //cout << "zmieniono nazwe ksiazkaAdresowaTemp na ksiazkaAdresowa.txt" << endl;
    //system("pause");

}
