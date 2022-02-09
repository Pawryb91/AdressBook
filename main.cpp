#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

void WyswietlMenuLogowania () {
    system("cls");
    cout << "1.Logowanie" << endl;
    cout << "2.Rejestracja" << endl;
    cout << "3.Zamknij program" << endl;
}

struct Uzytkownik {
    int NumerIdUzytkownika;
    string NazwaUzytkownika;
    string HasloUzytkownika;
};


void zmianaHasla (vector <Uzytkownik> &Uzytkownicy) {

    string stareHaslo;
    string noweHaslo;
    Uzytkownik modyfikowanyUzytkownik;

    cout << "Podaj stare haslo:" << endl;
    cin >> stareHaslo;

    for(int i = 0; i <= Uzytkownicy.size(); i++) {

        if(Uzytkownicy[i].HasloUzytkownika == stareHaslo) {
            cout << "Podaj nowe haslo: " << endl;
            cin >> noweHaslo;
            Uzytkownicy[i].HasloUzytkownika = noweHaslo;
            break;
        } else
            cout << "Bledne haslo" << endl;
        system("pause");
        break;
    }

    fstream UzytkownicyPlik;

    UzytkownicyPlik.open("Uzytkownicy.txt", ios::out);

    for(int i = 0; i < Uzytkownicy.size(); i++) {

        UzytkownicyPlik << Uzytkownicy[i].NumerIdUzytkownika << "|";
        UzytkownicyPlik << Uzytkownicy[i].NazwaUzytkownika << "|";
        UzytkownicyPlik << Uzytkownicy[i].HasloUzytkownika << "|" << endl;
    }

    UzytkownicyPlik.close();
}

bool SprawdzCzyNazwaUzytkownikaJestZajeta (string NazwaUzytkownika, vector <Uzytkownik> &Uzytkownicy) {

    bool WynikTestu;
    for(int i = 0; i <= Uzytkownicy.size() - 1 ; i++) {
        if (NazwaUzytkownika == Uzytkownicy[i].NazwaUzytkownika) {
            cout << "Nazwa uzytkownika jest zajeta" << endl;
            system("pause");
            WynikTestu = true;
            break;
        }
        else
            WynikTestu = false;
    }
    return WynikTestu;
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
        cin >> DodawanyUzytkownik.NazwaUzytkownika;
        CzyNazwaUzytkownikaJestZajeta = SprawdzCzyNazwaUzytkownikaJestZajeta (DodawanyUzytkownik.NazwaUzytkownika,Uzytkownicy);
    } while(CzyNazwaUzytkownikaJestZajeta == true);



    cout << "Podaj haslo" << endl;
    cin >> DodawanyUzytkownik.HasloUzytkownika;

    cout << DodawanyUzytkownik.NumerIdUzytkownika << " " << DodawanyUzytkownik.NazwaUzytkownika << " " << DodawanyUzytkownik.HasloUzytkownika << endl;

    fstream UzytkownicyPlik;

    UzytkownicyPlik.open("Uzytkownicy.txt", ios::out | ios::app);

    UzytkownicyPlik << DodawanyUzytkownik.NumerIdUzytkownika << "|";
    UzytkownicyPlik << DodawanyUzytkownik.NazwaUzytkownika << "|";
    UzytkownicyPlik << DodawanyUzytkownik.HasloUzytkownika << "|" << endl;

    UzytkownicyPlik.close();

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
    cin >> NazwaLogowanie ;

    cout << "Podaj haslo" << endl;
    cin >> HasloLogowanie ;

    if(Uzytkownicy.size() == 0) {
        cout << "Brak uzytkownikow w bazie, przejdz do rejestracji." << endl;
        cout << endl;
        return 0;
    }

    for (int i = 0; i <= Uzytkownicy.size() + 1; i++) {
        if(NazwaLogowanie == Uzytkownicy[i].NazwaUzytkownika) {
            if (HasloLogowanie == Uzytkownicy[i].HasloUzytkownika) {
                cout << "Nazwa i haslo sa poprawne. Udalo sie zalogowac." << endl;
                IdUzytkownika = Uzytkownicy[i].NumerIdUzytkownika;
                cout<<"Id uzytkownika " <<IdUzytkownika<<endl;
                Sleep(1000);
                break;
            } else {
                IdUzytkownika = 0;
            }
            break;
        } else {
            IdUzytkownika = 0;

        }
    }
    if (IdUzytkownika == 0)
        cout << "Bledna nazwa uzytkownika lub haslo" << endl;

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


struct DaneZnajomego {
    int NumerIdZnajomego = 0, IdUzytkownika = 0;
    string ImieZnajomego = "",NazwiskoZnajomego = "",NumerTelefonuZnajomego = "",AdresEmailZnajomego = "",AdresDomowyZnajomego= "";
};


char wczytajZnak() {

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


void DodajZnajomego (vector <DaneZnajomego> & WszyscyZnajomi, int IdUzytkownika, int IdOstatniegoAdresata) {


    DaneZnajomego DodawanyZnajomy;
    string WprowadzoneImieZnajomego;
    string WprowadzoneNazwiskoZnajomego;
    string WprowadzonyNumerTelefonuZnajomego;
    string WprowadzonyAdresEmailZnajomego;
    string WprowadzonyAdresDomowyZnajomego;
    int NadajID;


    system("cls");
    cout << "Wprowadz imie" << endl;
    cin >> WprowadzoneImieZnajomego;


    DodawanyZnajomy.NumerIdZnajomego = IdOstatniegoAdresata + 1;;
    DodawanyZnajomy.IdUzytkownika = IdUzytkownika;

    DodawanyZnajomy.ImieZnajomego = WprowadzoneImieZnajomego;

    cout << "Wprowadz nazwisko" << endl;
    cin >> WprowadzoneNazwiskoZnajomego;
    DodawanyZnajomy.NazwiskoZnajomego = WprowadzoneNazwiskoZnajomego;

    cout << "Wprowadz numer telefonu" << endl;
    cin >> WprowadzonyNumerTelefonuZnajomego;
    DodawanyZnajomy.NumerTelefonuZnajomego = WprowadzonyNumerTelefonuZnajomego;

    cout << "Wprowadz email" << endl;
    cin >> WprowadzonyAdresEmailZnajomego;
    DodawanyZnajomy.AdresEmailZnajomego = WprowadzonyAdresEmailZnajomego;

    cout << "Wprowadz adres" << endl;
    cin.sync();

    getline(cin,WprowadzonyAdresDomowyZnajomego);
    cout << endl;

    DodawanyZnajomy.AdresDomowyZnajomego = WprowadzonyAdresDomowyZnajomego;

    WszyscyZnajomi.push_back(DodawanyZnajomy);

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

int wczytajOstatnieIdZPliku() {

    //DaneZnajomego WczytywanyZnajomy;
    //vector <DaneZnajomego> WszyscyZnajomi;
    string LiniaPlikuDoWczytania;
    size_t znalezionaPozycja = 0;
    string numerIDosoby;
    //string numerIDUzytkownika;
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
    }
    else
        OstatnieId = 0;

    adressBook.close();

    return OstatnieId;
}

void wypiszZnajomego (vector <DaneZnajomego> & WszyscyZnajomi) {
    int iloscOsob = 1;
    for ( DaneZnajomego &e : WszyscyZnajomi ) {
        cout << iloscOsob << endl;
        iloscOsob++;
        cout <<"ID: "<< e.NumerIdZnajomego << endl;
        cout <<"ID uzytkownika " <<e.IdUzytkownika << endl;
        cout << e.ImieZnajomego <<" "<< e.NazwiskoZnajomego << endl;
        cout <<"Numer telefonu: "<< e.NumerTelefonuZnajomego << endl;
        cout <<"E-mail: "<< e.AdresEmailZnajomego << endl;
        cout <<"Adres: "<< e.AdresDomowyZnajomego << endl;
        cout << endl;
    }
    system("pause");
}

void WyszukajPoImieniu (vector <DaneZnajomego> & WszyscyZnajomi) {

    string imieDoWyszukania;
    int liczbaOsobOPodanymImieniu = 0;

    cout << "Wyszukiwanie osobu po imieniu" << endl;
    cout << endl;
    cout << "Wpisz imie do wyszukania: " << endl;

    cin >> imieDoWyszukania;

    system("cls");

    for (int i = 0; i < WszyscyZnajomi.size(); i++) {

        if(imieDoWyszukania == WszyscyZnajomi[i].ImieZnajomego) {
            liczbaOsobOPodanymImieniu ++;
            cout << liczbaOsobOPodanymImieniu << endl;

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

    system("pause");

}

void WyszukajPoNazwisku (vector <DaneZnajomego> & WszyscyZnajomi) {

    string nazwiskoDoWyszukania;
    int liczbaOsobOPodanymNazwisku = 0;


    cout << "Wyszukiwanie osobu po nazwisku" << endl;
    cout << endl;
    cout << "Wpisz nazwisko do wyszukania: " << endl;

    cin >> nazwiskoDoWyszukania;

    system("cls");

    for (int i = 0; i < WszyscyZnajomi.size(); i++) {

        if(nazwiskoDoWyszukania == WszyscyZnajomi[i].NazwiskoZnajomego) {
            liczbaOsobOPodanymNazwisku++;
            cout << liczbaOsobOPodanymNazwisku << endl;

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

    system("pause");
}

int usunWpis (vector <DaneZnajomego> & WszyscyZnajomi) {

    int numerOsobyDoUsuniecia;
    char potwierdzenie;
    int IdUsunietegoWpisu;

    for (int i = 0; i < WszyscyZnajomi.size(); i++) {
        cout << i + 1 << " " << WszyscyZnajomi[i].ImieZnajomego << " " << WszyscyZnajomi[i].NazwiskoZnajomego << endl;
    }

    cout << endl;
    cout << "Ktory wpis usunac (wpisz odpowiedni numer) ?" << endl;

    do {
        cin >> numerOsobyDoUsuniecia;

        if(numerOsobyDoUsuniecia < 1 || numerOsobyDoUsuniecia > WszyscyZnajomi.size()+1)
            cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;

    }

    while (numerOsobyDoUsuniecia < 1 || numerOsobyDoUsuniecia > WszyscyZnajomi.size()+1);

    cout << endl;
    cout << "Jestes pewien, ze chcesz usunac wpis "<< numerOsobyDoUsuniecia <<", jesli tak wcisnij: t " <<  endl;

    cin >> potwierdzenie;

    vector <DaneZnajomego>::iterator it;

    it = WszyscyZnajomi.begin() + numerOsobyDoUsuniecia - 1;

    IdUsunietegoWpisu = it->IdUzytkownika;

    if (potwierdzenie == 't') {
        WszyscyZnajomi.erase (it);
        cout << "Wpis zostal usuniety";
        cout << endl;
    } else {
        cout << "Wpis nie zostal usuniety";
        cout << endl;
    }
    system("pause");
    return IdUsunietegoWpisu;
}

int edytujWpis (vector <DaneZnajomego> & WszyscyZnajomi) {

    int numerOsobyDoEdycji;
    int zmiana;
    string NowaDana;

    cout << "Kogo dane chcesz edytowac (wybierz odpowiedni numer?" << endl;
    cout << endl;

    for (int i = 0; i < WszyscyZnajomi.size(); i++) {
        cout << i + 1 << " " << WszyscyZnajomi[i].ImieZnajomego << " " << WszyscyZnajomi[i].NazwiskoZnajomego << endl;
    }

    do {
        cin >> numerOsobyDoEdycji;

        if(numerOsobyDoEdycji < 1 || numerOsobyDoEdycji > WszyscyZnajomi.size()+1)
            cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;

    } while (numerOsobyDoEdycji < 1 || numerOsobyDoEdycji > WszyscyZnajomi.size()+1);

    system("cls");

    cout << "Ktora dana chcesz zmienic?" << endl;
    cout <<"1 - Imie: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].ImieZnajomego << endl;
    cout <<"2 - Nazwisko: "<< WszyscyZnajomi[numerOsobyDoEdycji- 1].NazwiskoZnajomego << endl;
    cout <<"3 - Numer telefonu: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerTelefonuZnajomego << endl;
    cout <<"4 - Adres e-mial: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresEmailZnajomego << endl;
    cout <<"5 - Adres domowy: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresDomowyZnajomego << endl;
    cout <<"6 - powrot do menu" << endl;
    cout << endl;

    do {
        cin >> zmiana;
        if (zmiana < 1 || zmiana > 6) {
            cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie.";
            cout << endl;
        }

    } while (zmiana < 1 || zmiana > 6);


    if (zmiana == 1) {
        cout << "Wprowadz nowe imie" << endl;
        cin >> NowaDana;
        WszyscyZnajomi[numerOsobyDoEdycji - 1].ImieZnajomego = NowaDana;
    } else if (zmiana == 2) {
        cout << "Wprowadz nowe nazwisko" << endl;
        cin >> NowaDana;
        WszyscyZnajomi[numerOsobyDoEdycji - 1].NazwiskoZnajomego = NowaDana;
    } else if (zmiana == 3) {
        cout << "Wprowadz nowy numer telefonu" << endl;
        cin >> NowaDana;
        WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerTelefonuZnajomego = NowaDana;
    } else if (zmiana == 4) {
        cout << "Wprowadz nowy adres email" << endl;
        cin >> NowaDana;
        WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresEmailZnajomego = NowaDana;
    } else if (zmiana == 5) {
        cout << "Wprowadz nowy adres domowy" << endl;
        cin.sync();
        getline (cin,NowaDana);
        WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresDomowyZnajomego = NowaDana;
    } else if (zmiana == 6)
        cin.sync();

    cout << endl;
    if (zmiana >= 1 && zmiana <= 6) {
        cout << "Wpis zostal zmieniony" << endl;
        cout << endl;
        cout <<"1 - Imie: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].ImieZnajomego << endl;
        cout <<"2 - Nazwisko: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].NazwiskoZnajomego << endl;
        cout <<"3 - Numer telefonu: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerTelefonuZnajomego << endl;
        cout <<"4 - Adres e-mial: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresEmailZnajomego << endl;
        cout <<"5 - Adres domowy: "<< WszyscyZnajomi[numerOsobyDoEdycji - 1].AdresDomowyZnajomego << endl;
        cout << endl;

    }


    system("pause");
    return WszyscyZnajomi[numerOsobyDoEdycji - 1].NumerIdZnajomego;
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

void aktualizujPlikTekstowy (vector <DaneZnajomego> & WszyscyZnajomi) {

    DaneZnajomego ZapisywanyZnajomy;
    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt", ios::out );

    for (int i = 0; i < WszyscyZnajomi.size(); i++) {

        ZapisywanyZnajomy.NumerIdZnajomego = WszyscyZnajomi[i].NumerIdZnajomego;
        ZapisywanyZnajomy.IdUzytkownika = WszyscyZnajomi[i].IdUzytkownika;
        ZapisywanyZnajomy.ImieZnajomego = WszyscyZnajomi[i].ImieZnajomego;
        ZapisywanyZnajomy.NazwiskoZnajomego = WszyscyZnajomi[i].NazwiskoZnajomego;
        ZapisywanyZnajomy.NumerTelefonuZnajomego = WszyscyZnajomi[i].NumerTelefonuZnajomego;
        ZapisywanyZnajomy.AdresEmailZnajomego = WszyscyZnajomi[i].AdresEmailZnajomego;
        ZapisywanyZnajomy.AdresDomowyZnajomego = WszyscyZnajomi[i].AdresDomowyZnajomego;


        adressBook << ZapisywanyZnajomy.NumerIdZnajomego << "|";
        adressBook << ZapisywanyZnajomy.IdUzytkownika << "|";
        adressBook << ZapisywanyZnajomy.ImieZnajomego << "|";
        adressBook << ZapisywanyZnajomy.NazwiskoZnajomego << "|";
        adressBook << ZapisywanyZnajomy.NumerTelefonuZnajomego << "|";
        adressBook << ZapisywanyZnajomy.AdresEmailZnajomego << "|";
        adressBook << ZapisywanyZnajomy.AdresDomowyZnajomego << "|" << endl;


    }

    adressBook.close();


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

void aktualizujPlikTekstowyPoEdycjiWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int IdEdytowanegoWpisu) {

    fstream AdressBook;
    fstream AdressBookTemp;
    string LiniaPlikuDoWczytania;
    size_t znalezionaPozycja;
    string numerIDosoby;
    DaneZnajomego WczytywanyZnajomy;

    AdressBook.open("ksiazkaAdresowa.txt", ios::in);
    AdressBookTemp.open("ksiazkaAdresowaTemp.txt", ios::out | ios::app);

    cout << "ksiazkaAdresowaTemp" << endl;


    while (getline(AdressBook,LiniaPlikuDoWczytania)) {
        znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

        if (znalezionaPozycja != std::string::npos) {
            numerIDosoby = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            WczytywanyZnajomy.NumerIdZnajomego = atoi(numerIDosoby.c_str());
        }
        if (WczytywanyZnajomy.NumerIdZnajomego == IdEdytowanegoWpisu) {

            AdressBookTemp << WszyscyZnajomi[IdEdytowanegoWpisu - 1].NumerIdZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[IdEdytowanegoWpisu - 1].IdUzytkownika << "|";
            AdressBookTemp << WszyscyZnajomi[IdEdytowanegoWpisu - 1].ImieZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[IdEdytowanegoWpisu - 1].NazwiskoZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[IdEdytowanegoWpisu - 1].NumerTelefonuZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[IdEdytowanegoWpisu - 1].AdresEmailZnajomego << "|";
            AdressBookTemp << WszyscyZnajomi[IdEdytowanegoWpisu - 1].AdresDomowyZnajomego << "|" << endl;
        } else
            AdressBookTemp << LiniaPlikuDoWczytania << endl;
    }
    AdressBook.close();
    AdressBookTemp.close();
    remove ("ksiazkaAdresowa.txt");
    cout << "usunieto ksiazkaAdresowa.txt" << endl;

    system("pause");
    rename ("ksiazkaAdresowaTemp.txt","ksiazkaAdresowa.txt");
    cout << "zmieniono nazwe ksiazkaAdresowaTemp na ksiazkaAdresowa.txt" << endl;
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

    cout << "ksiazkaAdresowaTemp" << endl;


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
    cout << "usunieto ksiazkaAdresowa.txt" << endl;

    system("pause");
    rename ("ksiazkaAdresowaTemp.txt","ksiazkaAdresowa.txt");
    cout << "zmieniono nazwe ksiazkaAdresowaTemp na ksiazkaAdresowa.txt" << endl;
    system("pause");

}


int main() {

    vector <DaneZnajomego> WszyscyZnajomi;
    bool plik;
    char wybor;
    int IdUzytkownika;
    vector <Uzytkownik> Uzytkownicy;
    int NumerIDEdytowanegoAdresata;
    int NumerIDUsunietegoAdresata;
    int IdOstatniegoAdresata;


    while (true) {
        Uzytkownicy = WczytajUzytkownikow();

        WyswietlMenuLogowania ();
        cout << "Twoj wybor: " << endl;
        cin >> wybor;
        //wybor = '2';

        if (wybor == '1') {
            system("cls");
            IdUzytkownika = Logowanie (Uzytkownicy);
            if (IdUzytkownika != 0) {
                plik = CzyPlikIstnieje();

                if (plik == 1 ) {
                    WszyscyZnajomi = wczytajZnajomegoZPliku(IdUzytkownika);
                }

                while(true) {
                    cin.sync();
                    WyswietlMenuGlowne();

                    wybor = wczytajZnak();

                    cout << endl;

                    if(wybor == '1') {
                        IdOstatniegoAdresata = wczytajOstatnieIdZPliku();
                        cout<<"OstatnieID" << IdOstatniegoAdresata << endl;
                        DodajZnajomego (WszyscyZnajomi,IdUzytkownika,IdOstatniegoAdresata);
                    } else if(wybor == '2') {

                        system("cls");

                        if(WszyscyZnajomi.size() == 0) {
                            cout << "Brak wpisow w ksiazce!" << endl;
                            system("pause");
                        }

                        else
                            WyszukajPoImieniu(WszyscyZnajomi);

                    } else if(wybor == '3') {

                        system("cls");

                        if(WszyscyZnajomi.size() == 0) {
                            cout << "Brak wpisow w ksiazce!" << endl;
                            system("pause");
                        } else {
                            WyszukajPoNazwisku(WszyscyZnajomi);

                        }

                    } else if(wybor == '4') {

                        system("cls");

                        if(WszyscyZnajomi.size() == 0) {
                            cout << "Brak wpisow w ksiazce!" << endl;
                            system("pause");
                        } else
                            wypiszZnajomego(WszyscyZnajomi);

                    } else if(wybor == '5') {

                        system("cls");

                        if(WszyscyZnajomi.size() == 0) {
                            cout << "Brak wpisow w ksiazce!" << endl;
                            system("pause");
                        } else
                            NumerIDUsunietegoAdresata = usunWpis(WszyscyZnajomi);
                        aktualizujPlikTekstowyPoUsunieciuWpisu (WszyscyZnajomi,NumerIDUsunietegoAdresata);
                    } else if(wybor == '6') {

                        system("cls");

                        if(WszyscyZnajomi.size() == 0) {
                            cout << "Brak wpisow w ksiazce!" << endl;
                            system("pause");
                        } else {
                            NumerIDEdytowanegoAdresata = edytujWpis(WszyscyZnajomi);
                            aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,NumerIDEdytowanegoAdresata);
                        }
                    } else if(wybor == '7') {
                        zmianaHasla (Uzytkownicy);
                    }


                    else if(wybor == '8') {
                        system ("cls");
                        break;


                    } else {
                        cin.sync();
                        cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;
                        system("pause");
                    }

                }
            }

        }
        if (wybor == '2')
            RejestracjaUzytkownika (Uzytkownicy);

        if (wybor == '3')
            exit(0);
    }



    return 0;
}
