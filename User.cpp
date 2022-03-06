#include "User.h"
#include <iostream>
#include <vector>
#include <fstream>

User::User(int ID, string Login, string Password)
{
  struct1.UserID = ID;
  struct1.UserLogin = Login;
  struct1.UserPassword = Password;
}

vector <User::UserData> AllUsers;

string User::wczytajLinie(){
    string Linia;
    cin.sync();
    getline(cin,Linia);
    return Linia;

}

string User::setLogin(){

cout << "Podaj login uzytkownika: " << endl;
struct1.UserLogin = wczytajLinie();
return struct1.UserLogin;

}

string User::setPassword(){

cout << "Podaj haslo: " << endl;
struct1.UserPassword = wczytajLinie();
return struct1.UserPassword;

}

User::UserData User::SetNewUserData (){


    if(AllUsers.size() == 0){
        cout<<AllUsers.size();
        struct1.UserID = 1;

    }
    else{
        cout<<AllUsers.size();
        struct1.UserID = AllUsers.size() + 1;
    }

    struct1.UserLogin = User::setLogin();
    struct1.UserPassword = User::setPassword();

return struct1;

}
void User::AddNewUserToVector(){

User::AllUsers.push_back(struct1);

}

void User::RegistrationNewUser(){

    bool CzyNazwaUzytkownikaJestZajeta;

    if (AllUsers.size() == 0)
        struct1.UserID = 1;
    else
        struct1.UserID = AllUsers.size() + 1;

    do {
        system ("cls");
        cout << "Podaj nazwe uzytkownika" << endl;
        struct1.UserLogin = wczytajLinie();
        CzyNazwaUzytkownikaJestZajeta = User::sprawdzCzyNazwaUzytkownikaJestZajeta (struct1.UserLogin);
    } while(CzyNazwaUzytkownikaJestZajeta == true);


    cout << "Podaj haslo" << endl;
    struct1.UserPassword = wczytajLinie();

    fstream UzytkownicyPlik;

    UzytkownicyPlik.open("listauzytkownikow.txt",ios::out | ios::app);

    UzytkownicyPlik << struct1.UserID << "|" ;
    UzytkownicyPlik << struct1.UserLogin << "|" ;
    UzytkownicyPlik << struct1.UserPassword << "|" ;
    UzytkownicyPlik << endl;

    UzytkownicyPlik.close();

    cout << "Zarejestrowano uzytkownika: " << struct1.UserLogin << endl;
    system("pause");

}

vector <User::UserData> User::WczytajUzytkownikow () {



    string LiniaPlikuDoWczytania;
    size_t znalezionaPozycja = 0;
    string numerID;

    AllUsers.clear();

    fstream UzytkownicyPlik;

    UzytkownicyPlik.open ("listauzytkownikow.txt", ios::in);

    while (getline(UzytkownicyPlik,LiniaPlikuDoWczytania)) {
        znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

        if (znalezionaPozycja != std::string::npos) {
            numerID = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            struct1.UserID = atoi(numerID.c_str());
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            struct1.UserLogin = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
            LiniaPlikuDoWczytania = LiniaPlikuDoWczytania.erase(0,znalezionaPozycja+1);
            znalezionaPozycja = LiniaPlikuDoWczytania.find("|");

            struct1.UserPassword = LiniaPlikuDoWczytania.substr(0,znalezionaPozycja);
        }
        User::AllUsers.push_back(struct1);
    }
    return AllUsers;
}

bool User::sprawdzCzyNazwaUzytkownikaJestZajeta (string Login) {

    bool test = true;
    if (AllUsers.size() == 0)
        test = false;
    else{
    for (int i = 0; i < AllUsers.size(); i++) {
        if( Login == AllUsers[i].UserLogin) {
            cout << "Nazwa uzytkownika jest zajeta" << endl;
            system("pause");
            test = true;
            break;
        }else
        test = false;
    }
    }
    return test;

}

int User::Login () {

    string NazwaLogowanie;
    string HasloLogowanie;
    int IdUzytkownika;

    cout << "Wpisz nazwe uzytkownika" << endl;
    NazwaLogowanie = User::wczytajLinie();

    cout << "Podaj haslo" << endl;
    HasloLogowanie = User::wczytajLinie();

    if(AllUsers.size() == 0) {
        cout << "Brak uzytkownikow w bazie, przejdz do rejestracji." << endl;
        cout << endl;
        system("pause");
        return 0;
    }

    for (int i = 0; i <= AllUsers.size() + 1; i++) {
        if(NazwaLogowanie == AllUsers[i].UserLogin) {
            if (HasloLogowanie == AllUsers[i].UserPassword) {
                cout << "Nazwa i haslo sa poprawne. Udalo sie zalogowac." << endl;
                IdUzytkownika = AllUsers[i].UserID;
                //Sleep(1000);
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
    system("pause");

    return IdUzytkownika;
}

void User::aktualizujPlikTekstowyPoZmianieHaslaUzytkownika () {

    fstream UzytkownicyPlik;

    UzytkownicyPlik.open("listauzytkownikow.txt", ios::out);

    for(vector <User::UserData> :: iterator itr = User::AllUsers.begin(); itr != User::AllUsers.end(); itr++) {

        UzytkownicyPlik << itr -> User::UserData::UserID << "|";
        UzytkownicyPlik << itr -> User::UserData::UserLogin << "|";
        UzytkownicyPlik << itr -> User::UserData::UserPassword << "|" << endl;
    }

    UzytkownicyPlik.close();
}


void User::zmianaHasla (){

    string stareHaslo;
    string noweHaslo;

    cout << "Podaj stare haslo:" << endl;
    //cout << "IdUzytkownika "<< struct1.UserID << endl;
    stareHaslo = User::wczytajLinie();

    for (vector<User::UserData>::iterator itr = User::AllUsers.begin(); itr != User::AllUsers.end(); itr++) {

        if(itr -> UserData::UserID == struct1.UserID) {
            if (itr -> UserData::UserPassword == stareHaslo) {
                cout << "Podaj nowe haslo: " << endl;
                noweHaslo = User::wczytajLinie();
                itr -> UserData::UserPassword = noweHaslo;
                aktualizujPlikTekstowyPoZmianieHaslaUzytkownika();
                cout << "Haslo zostalo zmienione" << endl;
                break;
            } else {
                cout << "Bledne haslo" << endl;
                break;
            }
        }

    }
    system("pause");
}

