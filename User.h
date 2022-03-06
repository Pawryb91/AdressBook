#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class User {

public:

    struct UserData {

        int UserID = 0;
        string UserLogin, UserPassword;

    }struct1;

    vector <UserData> AllUsers;

    User(int = 0, string = "Login", string = "Password");
    string setLogin();
    string setPassword();
    int Login();
    UserData SetNewUserData ();
    void AddNewUserToVector();
    void RegistrationNewUser();
    string wczytajLinie();
    vector <UserData> WczytajUzytkownikow();
    bool sprawdzCzyNazwaUzytkownikaJestZajeta(string UserLogin);
    void zmianaHasla ();
    void aktualizujPlikTekstowyPoZmianieHaslaUzytkownika ();


};

