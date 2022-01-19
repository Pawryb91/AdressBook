#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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
    cout << "9. Zakoncz " << endl;
    cout << endl;
    cout << "Twoj wybor: " << endl;
}


struct DaneZnajomego {
    int NumerIdZnajomego = 0;
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

int wyznaczID (vector <DaneZnajomego> WszyscyZnajomi) {
    if (WszyscyZnajomi.size() == 0)
        return 1;

    else
        return WszyscyZnajomi[WszyscyZnajomi.size() - 1].NumerIdZnajomego + 1;

}


vector <DaneZnajomego>DodajZnajomego (vector <DaneZnajomego> WszyscyZnajomi) {


    DaneZnajomego DodawanyZnajomy;
    string WprowadzoneImieZnajomego;
    string WprowadzoneNazwiskoZnajomego;
    string WprowadzonyNumerTelefonuZnajomego;
    string WprowadzonyAdresEmailZnajomego;
    string WprowadzonyAdresDomowyZnajomego;
    int NadajID = wyznaczID(WszyscyZnajomi);

    system("cls");
    cout << "Wprowadz imie" << endl;
    cin >> WprowadzoneImieZnajomego;
    DodawanyZnajomy.NumerIdZnajomego = NadajID;
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

    adressBook.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    adressBook << DodawanyZnajomy.NumerIdZnajomego << "|";
    adressBook << DodawanyZnajomy.ImieZnajomego << "|";
    adressBook << DodawanyZnajomy.NazwiskoZnajomego << "|";
    adressBook << DodawanyZnajomy.NumerTelefonuZnajomego << "|";
    adressBook << DodawanyZnajomy.AdresEmailZnajomego << "|";
    adressBook << DodawanyZnajomy.AdresDomowyZnajomego << "|" << endl;

    adressBook.close();

    cout << "Wpis " << DodawanyZnajomy.ImieZnajomego << " " << DodawanyZnajomy.NazwiskoZnajomego << " zostal dodany do Ksiazki Adresowej.";
    cout << endl;

    system("pause");
    return WszyscyZnajomi;
}


vector<DaneZnajomego> wczytajZnajomegoZPliku() {

    DaneZnajomego WczytywanyZnajomy;
    vector <DaneZnajomego> WszyscyZnajomi;
    string LiniaPlikuDoWczytania;
    size_t znalezionaPozycja = 0;
    string numerID;

    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt", ios::in);

    while (getline(adressBook,LiniaPlikuDoWczytania)) {
        znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

        if( znalezionaPozycja != std::string::npos ) {
            numerID = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            WczytywanyZnajomy.NumerIdZnajomego = atoi(numerID.c_str());
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

            WszyscyZnajomi.push_back(WczytywanyZnajomy);
        }


    }
    adressBook.close();
    return WszyscyZnajomi;
}

void wypiszZnajomego (vector <DaneZnajomego> WszyscyZnajomi) {
    int iloscOsob = 1;
    for ( DaneZnajomego &e : WszyscyZnajomi ) {
        cout << iloscOsob << endl;
        iloscOsob++;
        cout <<"ID: "<< e.NumerIdZnajomego << endl;
        cout << e.ImieZnajomego <<" "<< e.NazwiskoZnajomego << endl;
        cout <<"Numer telefonu: "<< e.NumerTelefonuZnajomego << endl;
        cout <<"E-mail: "<< e.AdresEmailZnajomego << endl;
        cout <<"Adres: "<< e.AdresDomowyZnajomego << endl;
        cout << endl;
    }
    system("pause");
}

void WyszukajPoImieniu (vector <DaneZnajomego> WszyscyZnajomi) {

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

void WyszukajPoNazwisku (vector <DaneZnajomego> WszyscyZnajomi) {

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

vector<DaneZnajomego> usunWpis (vector <DaneZnajomego> WszyscyZnajomi) {

    int numerOsobyDoUsuniecia;
    char potwierdzenie;

    for (int i = 0; i < WszyscyZnajomi.size(); i++) {
        cout << i + 1 << " " << WszyscyZnajomi[i].ImieZnajomego << " " << WszyscyZnajomi[i].NazwiskoZnajomego << endl;
    }

    cout << endl;
    cout << "Ktory wpis usunac (wpisz odpowiedni numer) ?" << endl;

    do {
        cin >> numerOsobyDoUsuniecia;

        if(numerOsobyDoUsuniecia < 1 || numerOsobyDoUsuniecia > WszyscyZnajomi.size()+1)
            cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;

    } while (numerOsobyDoUsuniecia < 1 || numerOsobyDoUsuniecia > WszyscyZnajomi.size()+1);

    cout << endl;
    cout << "Jestes pewien, ze chcesz usunac wpis "<< numerOsobyDoUsuniecia <<", jesli tak wcisnij: t " <<  endl;

    cin >> potwierdzenie;

    vector <DaneZnajomego>::iterator it;

    it = WszyscyZnajomi.begin() + numerOsobyDoUsuniecia - 1;

    if (potwierdzenie == 't') {
        WszyscyZnajomi.erase (it);
        cout << "Wpis zostal usuniety";
        cout << endl;
    } else {
        cout << "Wpis nie zostal usuniety";
        cout << endl;
    }
    system("pause");
    return WszyscyZnajomi;
}

vector<DaneZnajomego> edytujWpis (vector <DaneZnajomego> WszyscyZnajomi) {

    int numerOsobyDoEdycji;
    int zmiana;
    string NowaDana;

    cout << "Kogo dane chcesz edytowac (wybierz odpowiedni numer?)" << endl;
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
    return WszyscyZnajomi;
}

bool CzyPlikIstnieje () {

    bool plik;
    fstream adressBook;

    adressBook.open("KsiazkaAdresowa.txt",ios::in);

    if (adressBook.good() == true)
        plik = true;
    else
        plik = false;

    adressBook.close();

    return plik;
}

void aktualizujPlikTekstowy (vector <DaneZnajomego> WszyscyZnajomi) {

    DaneZnajomego ZapisywanyZnajomy;
    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt", ios::out );

    for (int i = 0; i < WszyscyZnajomi.size(); i++) {

        ZapisywanyZnajomy.NumerIdZnajomego = WszyscyZnajomi[i].NumerIdZnajomego;
        ZapisywanyZnajomy.ImieZnajomego = WszyscyZnajomi[i].ImieZnajomego;
        ZapisywanyZnajomy.NazwiskoZnajomego = WszyscyZnajomi[i].NazwiskoZnajomego;
        ZapisywanyZnajomy.NumerTelefonuZnajomego = WszyscyZnajomi[i].NumerTelefonuZnajomego;
        ZapisywanyZnajomy.AdresEmailZnajomego = WszyscyZnajomi[i].AdresEmailZnajomego;
        ZapisywanyZnajomy.AdresDomowyZnajomego = WszyscyZnajomi[i].AdresDomowyZnajomego;


        adressBook << ZapisywanyZnajomy.NumerIdZnajomego << "|";
        adressBook << ZapisywanyZnajomy.ImieZnajomego << "|";
        adressBook << ZapisywanyZnajomy.NazwiskoZnajomego << "|";
        adressBook << ZapisywanyZnajomy.NumerTelefonuZnajomego << "|";
        adressBook << ZapisywanyZnajomy.AdresEmailZnajomego << "|";
        adressBook << ZapisywanyZnajomy.AdresDomowyZnajomego << "|" << endl;


    }

    adressBook.close();


}
int main() {

    vector <DaneZnajomego> WszyscyZnajomi;
    bool plik;
    char wybor;

    plik = CzyPlikIstnieje();

    if (plik == true )
        WszyscyZnajomi = wczytajZnajomegoZPliku();



    while(true) {
        cin.sync();
        WyswietlMenuGlowne();


        wybor = wczytajZnak();

        cout << endl;

        if(wybor == '1') {
            WszyscyZnajomi = DodajZnajomego (WszyscyZnajomi);
            aktualizujPlikTekstowy(WszyscyZnajomi);
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
                WszyscyZnajomi = usunWpis(WszyscyZnajomi);

            aktualizujPlikTekstowy(WszyscyZnajomi);
        } else if(wybor == '6') {

            system("cls");

            if(WszyscyZnajomi.size() == 0) {
                cout << "Brak wpisow w ksiazce!" << endl;
                system("pause");
            } else
                WszyscyZnajomi =  edytujWpis(WszyscyZnajomi);
            aktualizujPlikTekstowy(WszyscyZnajomi);
        } else if(wybor == '9') {
            aktualizujPlikTekstowy(WszyscyZnajomi);
            exit(0);
        } else {
            cin.sync();
            cout << "Wprowadzono nieprawidlowa wartosc. Sprobuj ponownie." << endl;
            system("pause");
        }


    }

    return 0;
}
