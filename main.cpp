#include <iostream>
#include <vector>
#include <fstream>
#include "User.h"
#include <sstream>
#include <cstdio>
#include <windows.h>


using namespace std;

struct DaneZnajomego {
    int NumerIdZnajomego = 0, IdUzytkownika = 0;
    string ImieZnajomego = "",NazwiskoZnajomego = "",NumerTelefonuZnajomego = "",AdresEmailZnajomego = "",AdresDomowyZnajomego= "";
};

void WyswietlMenuLogowania ();
void WyswietlMenuGlowne ();
char wczytajPojedynczyZnak();
bool CzyPlikIstnieje ();
vector<DaneZnajomego> wczytajZnajomegoZPliku(int IdUzytkownika);
char wczytajZnak();
void DodajZnajomego (vector <DaneZnajomego> & WszyscyZnajomi, int IdUzytkownika);
void WyszukajPoImieniu (vector <DaneZnajomego> & WszyscyZnajomi);
void WyszukajPoNazwisku (vector <DaneZnajomego> & WszyscyZnajomi);
void wypiszZnajomego (vector <DaneZnajomego> & WszyscyZnajomi);
void usunWpis (vector <DaneZnajomego> & WszyscyZnajomi);
void edytujWpis (vector <DaneZnajomego> & WszyscyZnajomi);
string wczytajLinie();
int wczytajOstatnieIdZPliku();
void zapiszZnajomegoDoPliku (DaneZnajomego DodawanyZnajomy);
void wypiszZnajomychZWektora (vector <DaneZnajomego> & WszyscyZnajomi);
int wczytajLiczbeCalkowita();
void aktualizujPlikTekstowyPoUsunieciuWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int IdUsunietegoWpisu);
bool WyswietlMenuEdycjiWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int IdOsobyDoEdycji);
void WyswietlUzytkownikaPoEdycji (vector <DaneZnajomego> & WszyscyZnajomi, int IdOsobyDoEdycji);
void aktualizujPlikTekstowyPoEdycjiWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int IdEdytowanegoWpisu);

int main() {

    User obj;
    vector <DaneZnajomego> WszyscyZnajomi;
    bool plik;
    char wyborMenuLogowania;
    char wyborMenuGlowne;
    int IdUzytkownika;


    while (true) {
        obj.AllUsers = obj.WczytajUzytkownikow();
        WyswietlMenuLogowania ();
        cout << "Twoj wybor: " << endl;
        wyborMenuLogowania = wczytajPojedynczyZnak();

        switch (wyborMenuLogowania) {
        case '1':
            system("cls");
            obj.struct1.UserID = obj.Login();
            if (obj.struct1.UserID != 0) {
                plik = CzyPlikIstnieje();

                if (plik == 1 ) {
                    WszyscyZnajomi = wczytajZnajomegoZPliku(obj.struct1.UserID);
                }

                while(wyborMenuLogowania == '1') {
                    cin.sync();
                    WyswietlMenuGlowne();

                    wyborMenuGlowne = wczytajPojedynczyZnak();

                    system("cls");

                    switch (wyborMenuGlowne) {
                    case '1':
                        DodajZnajomego (WszyscyZnajomi,obj.struct1.UserID);
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
                        obj.zmianaHasla ();
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
            obj.RegistrationNewUser();
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


void usunWpis (vector <DaneZnajomego> & WszyscyZnajomi) {

    int IdOsobyDoUsuniecia;
    char potwierdzenie;
    bool czyAdresatIstnieje;

    if(WszyscyZnajomi.size() == 0)
        cout << "Brak wpisow." << endl;
    else {
        czyAdresatIstnieje = false;
        cout << endl;
        cout << "Ktory wpis usunac (wpisz odpowiedni numer) ?" << endl;
        wypiszZnajomychZWektora(WszyscyZnajomi);


        IdOsobyDoUsuniecia = wczytajLiczbeCalkowita();

        for (vector <DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr ++) {
            if (itr -> NumerIdZnajomego == IdOsobyDoUsuniecia) {
                czyAdresatIstnieje = true;

                cout << endl;
                cout << "Jestes pewien, ze chcesz usunac wpis "<< itr -> ImieZnajomego << " " << itr -> NazwiskoZnajomego <<", jesli tak wcisnij: t " <<  endl;

                cin >> potwierdzenie;

                if (potwierdzenie == 't') {
                    WszyscyZnajomi.erase (itr);
                    aktualizujPlikTekstowyPoUsunieciuWpisu(WszyscyZnajomi,IdOsobyDoUsuniecia);
                    cout << "Wpis zostal usuniety";
                    cout << endl;
                    break;
                } else {
                    cout << "Wpis nie zostal usuniety";
                    cout << endl;
                    break;
                }
            }
        }
        if(czyAdresatIstnieje == false)
            cout << "Brak adresata o podanym ID "<< endl;
    }
    system("pause");
}

void edytujWpis (vector <DaneZnajomego> & WszyscyZnajomi) {

    int IdOsobyDoEdycji;
    int zmiana;
    string NowaDana;
    bool czyPoprawneID;

    if(WszyscyZnajomi.size() == 0){
        cout << "Brak wpisow." << endl;
    }
    else {

        cout << "Kogo dane chcesz edytowac (podaj numer ID?)" << endl;
        cout << endl;

        wypiszZnajomychZWektora(WszyscyZnajomi);
        IdOsobyDoEdycji = wczytajLiczbeCalkowita();
        czyPoprawneID = WyswietlMenuEdycjiWpisu(WszyscyZnajomi, IdOsobyDoEdycji);



    if(czyPoprawneID == true){

        do {
            zmiana = wczytajLiczbeCalkowita();

            switch (zmiana) {

            case 1:
                cout << "Wprowadz nowe imie" << endl;
                for (vector <DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr++)
                    if (itr -> NumerIdZnajomego == IdOsobyDoEdycji)
                        itr -> ImieZnajomego = wczytajLinie();

                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,IdOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,IdOsobyDoEdycji);
                break;
            case 2:
                cout << "Wprowadz nowe nazwisko" << endl;
                for (vector <DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr++)
                    if (itr -> NumerIdZnajomego == IdOsobyDoEdycji)
                        itr -> NazwiskoZnajomego = wczytajLinie();

                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,IdOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,IdOsobyDoEdycji);
                break;
            case 3:
                cout << "Wprowadz nowy numer telefonu" << endl;
                for (vector <DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr++)
                    if (itr -> NumerIdZnajomego == IdOsobyDoEdycji)
                        itr -> NumerTelefonuZnajomego = wczytajLinie();

                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,IdOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,IdOsobyDoEdycji);
                break;
            case 4:
                cout << "Wprowadz nowy adres email" << endl;
                for (vector <DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr++)
                    if (itr -> NumerIdZnajomego == IdOsobyDoEdycji)
                        itr -> AdresEmailZnajomego = wczytajLinie();

                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,IdOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,IdOsobyDoEdycji);
                break;
            case 5:
                cout << "Wprowadz nowy adres domowy" << endl;
                for (vector <DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr++)
                    if (itr -> NumerIdZnajomego == IdOsobyDoEdycji)
                        itr -> AdresDomowyZnajomego = wczytajLinie();

                WyswietlUzytkownikaPoEdycji (WszyscyZnajomi,IdOsobyDoEdycji);
                aktualizujPlikTekstowyPoEdycjiWpisu(WszyscyZnajomi,IdOsobyDoEdycji);
                break;
            case 6:
                break;
            default:
                cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie.";
                cout << endl;
            }

        } while (zmiana < 1 || zmiana > 6);
    } else
        cout << "Brak adresata o podanym ID "<< endl;
}

    system("pause");
}

string wczytajLinie() {
    string Linia;
    cin.sync();
    getline(cin,Linia);
    return Linia;
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

void wypiszZnajomychZWektora (vector <DaneZnajomego> & WszyscyZnajomi) {

    for (vector<DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr++) {
        cout <<"Numer ID: "<< itr->NumerIdZnajomego << " " << itr->ImieZnajomego << " " << itr->NazwiskoZnajomego << endl << endl;
    }

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

bool WyswietlMenuEdycjiWpisu (vector <DaneZnajomego> & WszyscyZnajomi, int IdOsobyDoEdycji) {
    //system("cls");

    bool czyAdresatIstnieje = false;


    for (vector <DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr ++) {
        if(itr->NumerIdZnajomego == IdOsobyDoEdycji) {

            czyAdresatIstnieje = true;

            cout << "Ktora dana chcesz zmienic?" << endl;
            cout <<"1 - Imie: "<< itr -> ImieZnajomego << endl;
            cout <<"2 - Nazwisko: "<< itr -> NazwiskoZnajomego << endl;
            cout <<"3 - Numer telefonu: "<< itr -> NumerTelefonuZnajomego << endl;
            cout <<"4 - Adres e-mial: "<< itr -> AdresEmailZnajomego << endl;
            cout <<"5 - Adres domowy: "<< itr -> AdresDomowyZnajomego << endl;
            cout <<"6 - powrot do menu" << endl;
            cout << endl;
        }
    }
    return czyAdresatIstnieje;

}

void WyswietlUzytkownikaPoEdycji (vector <DaneZnajomego> & WszyscyZnajomi, int IdOsobyDoEdycji) {

    for (vector <DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr ++) {
        if(itr->NumerIdZnajomego == IdOsobyDoEdycji) {
            cout <<"Imie: "<< itr -> ImieZnajomego << endl;
            cout <<"Nazwisko: "<< itr -> NazwiskoZnajomego << endl;
            cout <<"Numer telefonu: "<< itr -> NumerTelefonuZnajomego << endl;
            cout <<"Adres e-mial: "<< itr -> AdresEmailZnajomego << endl;
            cout <<"Adres domowy: "<< itr -> AdresDomowyZnajomego << endl;
            cout << endl;
        }
    }

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

    while (getline(AdressBook,LiniaPlikuDoWczytania)) {
        znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

        if (znalezionaPozycja != std::string::npos) {
            numerIDosoby = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            WczytywanyZnajomy.NumerIdZnajomego = atoi(numerIDosoby.c_str());
            if(WczytywanyZnajomy.NumerIdZnajomego == IdEdytowanegoWpisu) {
                for (vector<DaneZnajomego>::iterator itr = WszyscyZnajomi.begin(); itr != WszyscyZnajomi.end(); itr++) {
                    if(itr -> NumerIdZnajomego == IdEdytowanegoWpisu) {

                        AdressBookTemp << itr -> NumerIdZnajomego << "|";
                        AdressBookTemp << itr -> IdUzytkownika << "|";
                        AdressBookTemp << itr -> ImieZnajomego << "|";
                        AdressBookTemp << itr -> NazwiskoZnajomego << "|";
                        AdressBookTemp << itr -> NumerTelefonuZnajomego << "|";
                        AdressBookTemp << itr -> AdresEmailZnajomego << "|";
                        AdressBookTemp << itr -> AdresDomowyZnajomego << "|" << endl;
                    }
                }
            } else
                AdressBookTemp << LiniaPlikuDoWczytania << endl;
        }
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

