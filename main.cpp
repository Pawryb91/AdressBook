#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

void menuGlowne()
{
    system("cls");
    cout << "Witaj w Twojej ksiazce adresowej, wybierz co chcesz teraz zrobic:" << endl;
    cout << endl;
    cout << "1. Wpisz nowa osobe do ksiazki adresowej" << endl;
    cout << "2. Wyszukaj osobe z ksiazki adresowej" << endl;
    cout << "3. Pokaz wszystkie wpisy z ksiazki adresowej" << endl;
    cout << "0. Zakoncz " << endl;
    cout << endl;
}

void menuWyszukiwanie()
{
    system("cls");
    cout << "I. Wyszukaj osobe z ksiazki adresowej po imieniu" << endl;
    cout << "N. Wyszukaj osobe z ksiazki adresowej po nazwisku" << endl;
    cout << "Z. Zakoncz wyszukiwanie" << endl;
    cout << endl;
}


struct wpisDoKsiazki
{
    int userId;
    string name;
    string surname;
    string phoneNumber;
    string email;
    string adress;
};

void dodajWpis (wpisDoKsiazki znajomy[], int i)
{

    string name;
    string surname;
    string phoneNumber;
    string email;
    string adress;

    system("cls");
    cout << "Wprowadz imie" << endl;
    cin >> name;
    znajomy[i].userId = i + 1;
    znajomy[i].name = name;

    cout << "Wprowadz nazwisko" << endl;
    cin >> surname;
    znajomy[i].surname = surname;

    cout << "Wprowadz numer telefonu" << endl;
    cin >> phoneNumber;
    znajomy[i].phoneNumber = phoneNumber;

    cout << "Wprowadz email" << endl;
    cin >> email;
    znajomy[i].email = email;

    cout << "Wprowadz adres" << endl;
    cin.sync();
    getline(cin,adress);
    cout << endl;

    znajomy[i].adress = adress;
}

void zapiszWpisDoPliku(wpisDoKsiazki znajomy[], int i)
{
    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    adressBook << znajomy[i].userId << endl;
    adressBook << znajomy[i].name << endl;
    adressBook << znajomy[i].surname << endl;
    adressBook << znajomy[i].phoneNumber << endl;
    adressBook << znajomy[i].email << endl;
    adressBook << znajomy[i].adress << endl;

    adressBook.close();
}

void zapiszIloscWpisowDoPliku (wpisDoKsiazki znajomy[], int i)    //program zapisuje liczbe wpisow do osobnego pliku
{
    fstream iloscWpisow;

    iloscWpisow.open("iloscWpisow.txt", ios::out);

    iloscWpisow << znajomy[i].userId ;

    iloscWpisow.close();
}

char PoWyszukiwaniu ()
{
    char kontynuacja;

    cout << "Aby powrocic do menu nacisnij m" << endl;
    cout << "Aby wyszukac ponownie nacisnij dowolny inny klawisz" << endl;
    cin >> kontynuacja;
    if (kontynuacja == 'm')
        return 'm';
    else
        return '2';
}

int wczytajiloscWpisowZPliku()
{
    fstream iloscWpisow;
    string linia_iloscWpisow;
    int i;
    iloscWpisow.open("iloscWpisow.txt", ios::in);

    if (iloscWpisow.good()==false)
    {
        i = 0;

    }

    else
    {
        getline(iloscWpisow,linia_iloscWpisow);
        i = atoi(linia_iloscWpisow.c_str()) ;
    }

    iloscWpisow.close();
    return i;
}

void wczytajZnajomegoZPliku(wpisDoKsiazki znajomy[])
{
    fstream adressBook;

    adressBook.open("ksiazkaAdresowa.txt", ios::in);

    string linia;
    int nr_linii = 1;
    int i = 0;

    while (getline(adressBook,linia))
    {
        switch (nr_linii)
        {
        case 1:
            znajomy[i].userId = atoi(linia.c_str());
            break;
        case 2:
            znajomy[i].name = linia;
            break;
        case 3:
            znajomy[i].surname = linia;
            break;
        case 4:
            znajomy[i].phoneNumber = linia;
            break;
        case 5:
            znajomy[i].email = linia;
            break;
        case 6:
            znajomy[i].adress = linia;
            break;
        }
        if (nr_linii == 6)
        {
            nr_linii = 0;
            i++;
        }
        nr_linii++;
    }

    adressBook.close();
}
void wypiszZnajomego (wpisDoKsiazki znajomy[], int i)
{
    cout << znajomy[i].userId << endl;
    cout << znajomy[i].name <<endl;
    cout << znajomy[i].surname <<endl;
    cout << znajomy[i].phoneNumber <<endl;
    cout << znajomy[i].email <<endl;
    cout << znajomy[i].adress <<endl;
    cout << endl;
}

char poWypisaniuWszystkiego ()
{
    char wybor;
    cout << "Aby wrocic do menu nacisnij m" << endl;
    cout << "Aby zakonczyc wcisnij dowolny inny klawisz" << endl;
    cin >> wybor;
    return wybor;
}

char poWpisie()
{
    char kontynuacja;

    cout << "Jesli chcesz wrocic do menu, nacisnij m" << endl;
    cout << "Jesli chcesz wprowadzic nastepna osobe, nacisnij dowolny inny klawisz" << endl;

    cin >> kontynuacja;
    return kontynuacja;
}

void wyszukajImie (wpisDoKsiazki znajomy[], int userId)
{
    int test;

    cout << "Podaj imie do wyszukania" << endl;
    string imie;
    cin >> imie;
    cout << endl;


    for (int i = 0; i < userId; i++)
    {
        if(imie == znajomy[i].name)
        {
            test = 1;
            break;
        }
        else
            test = 0;
    }

    if (test == 1)
    {
        for (int i = 0; i < userId; i++)
        {

            if(imie == znajomy[i].name)
            {
                wypiszZnajomego(znajomy, i);
            }
        }
    }
    else
        cout << "Brak imienia w bazie" << endl;
    cout << endl;
}

void wyszukajNazwisko (wpisDoKsiazki znajomy[], int userId)
{
    int test;

    cout << "Podaj nazwisko do wyszukania" << endl;
    string nazwisko;
    cin >> nazwisko;
    cout << endl;


    for (int i = 0; i < userId; i++)
    {
        if(nazwisko == znajomy[i].surname)
        {
            test = 1;
            break;
        }
        else
            test = 0;
    }

    if (test == 1)
    {
        for (int i = 0; i < userId; i++)
        {
            if(nazwisko == znajomy[i].surname)
            {
                wypiszZnajomego(znajomy, i);
            }
        }
    }
    else
        cout << "Brak nazwiska w bazie" << endl;
    cout << endl;
}

int czyPlikIstnieje ()
{
    int plik;
    fstream adressBook;
    adressBook.open("ksiazkaAdresowa.txt", ios::in);
    plik = adressBook.good ();
    adressBook.close();
    return plik;
}

int main()
{

    char wybor;
    int i = 0;
    int userId = 1;
    wpisDoKsiazki znajomy[100];

    while(1)
    {

        menuGlowne();

        i = wczytajiloscWpisowZPliku();

        userId = wczytajiloscWpisowZPliku();

        wczytajZnajomegoZPliku(znajomy);

        int plik = czyPlikIstnieje ();

        cin >> wybor;

        while(wybor != '1' && wybor != '2' && wybor != '3' && wybor != '0')
        {
            system ("cls");
            menuGlowne();
            cout<< "Nieprawidlowy wybor, prosze wybrac 1, 2, 3, lub 0" << endl;
            cin >> wybor;
        }

        switch (wybor)
        {
        case '1':
            while(wybor != 'm')
            {
                dodajWpis (znajomy, i);

                zapiszWpisDoPliku(znajomy, i);

                zapiszIloscWpisowDoPliku (znajomy, i);

                userId = znajomy[i].userId;

                i++;

                wybor = poWpisie();
            }
            break;

        case '2':

            while(wybor == '2')
            {
                system ("cls");
                menuWyszukiwanie();
                cin >> wybor;
                if (plik == 0)
                {
                    cout << "Brak wpisow" << endl;
                    Sleep(1000);
                    break;
                }
                while(wybor != 'I' && wybor != 'N' && wybor != 'Z')
                {
                    cout << "Wybierz co chcesz wyszukac: " << endl;
                    cout << "I - imie lub N - nazwisko" << endl;
                    cin >> wybor;
                    system ("cls");
                }
                switch (wybor)
                {
                case 'I':
                    wyszukajImie (znajomy,userId);
                    Sleep(1000);
                    break;
                case 'N':
                    wyszukajNazwisko (znajomy,userId);
                    Sleep(1000);
                    break;
                case 'Z':
                    break;
                }
                if (PoWyszukiwaniu() != 'm')
                    wybor = '2';
                else
                    break;
            }
            break;

        case '3':

            if (plik == 0)
            {
                cout << "Brak wpisow" << endl;
                Sleep(1000);
                break;
            }

            for (int i = 0; i < userId; i++)
            {
                wypiszZnajomego (znajomy,i);
            }
            if(poWypisaniuWszystkiego () == 'm')
                break;
            else
                return 0;
        case '0':
            return 0;
            break;
        }
    }
    return 0;
}
