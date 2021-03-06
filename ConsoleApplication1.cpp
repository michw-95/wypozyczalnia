#define _CRT_SECURE_NO_WARNINGS
#include <iostream> // cout/cin
#include <string> // string
#include <fstream> //edycja plikow
#include <cstdlib> // exit(0) , rand
#include <time.h> // zczytuje czas w funkcji rand == losowe liczby
#include <Windows.h> // funkcja sleep
#include <consoleapi.h> // Funkcja system("cls") czyszczaca ekran

using namespace std;
// //////////////////////////////////////////////////////// KLIENT
void wczytaj_klienta()
{
	string imie, nazwisko, pesel, email, nr_telefonu;
	int id;

	int losuj_nr_id_klienta();
	id = losuj_nr_id_klienta(); // tworzy unikatowy numer id

	cout << "Podaj imie: ";

	cin.sync();
	getline(cin, imie);

	cout << "Podaj nazwisko: ";

	cin.sync();
	getline(cin, nazwisko);

	cout << "Podaj pesel: ";

	cin.sync();
	getline(cin, pesel);

	cout << "Podaj email: ";

	cin.sync();
	getline(cin, email);

	cout << "Podaj nr telefonu: ";

	cin.sync();
	getline(cin, nr_telefonu);

	fstream plik;
	plik.open("Lista_klientow.txt", ios::out | ios::app);

	plik << id << endl;
	plik << imie << endl;
	plik << nazwisko << endl;
	plik << pesel << endl;
	plik << email << endl;
	plik << nr_telefonu << endl;


	plik.close();
	plik.clear();

};

int ile_klientow_w_pliku() // zwroci ilo elementowa tablice powinnismy utowrzyc aby wpisac np. numer id wszystkich klientow
{
	fstream plik;
	plik.open("Lista_klientow.txt", ios::in | ios::app);

	if (plik.good() == false)
	{
		cout << "Plik nie istanieje" << endl;
		exit(0);
	}

	string linia;
	int numer_lini = 1;
	int ile = 0;

	while (getline(plik, linia))
	{
		switch (numer_lini)
		{
		case 1:
		{
			ile += 1;
		}
		default: break;
		}
		numer_lini++;
		if (numer_lini == 7) numer_lini = 1;
	}

	return ile;
}

int losuj_nr_id_klienta() // wylosuje unikatowy nr id ktory przypiszemy do klienta
{

	int elementy_tablicy;
	int ile_klientow_w_pliku();

	elementy_tablicy = ile_klientow_w_pliku();

	int *tablica;
	tablica = new int[elementy_tablicy]; // tworzy tablice

										 //////////////////////////////////////////////// wpisuje uzywane juz id do tablicy
	fstream plik;
	plik.open("Lista_klientow.txt", ios::in | ios::app);

	if (plik.good() == false)
	{
		cout << "Plik nie istnieje" << endl;
		exit(0);
	}

	int nr_lini = 1;
	string linia;

	while (getline(plik, linia))
	{
		switch (nr_lini)
		{
		case 1:
		{
			*tablica = atoi(linia.c_str()); 
			tablica++;
		}
		default: break;
		}

		nr_lini++;

		if (nr_lini == 7) nr_lini = 1;
	}

	//////////////////////////////////////////////////////////// losuje unikatowy id
	int losowana;

	losowana = rand() % 100;
	int i = 0;

	do
	{

		if (losowana == tablica[i])
		{
			losowana = rand() % 100;
			i = -1;
		}
		i++;

	} while (i < elementy_tablicy);

	return losowana;

	delete[] tablica;
	plik.close();
	plik.clear();
};

void odczytaj_liste_klientow()
{


	int ile_klientow_w_pliku();

	if (ile_klientow_w_pliku() == 0)
	{
		cout << "W pliku nic nie ma" << endl;
	}

	fstream plik;
	plik.open("Lista_klientow.txt", ios::in | ios::app);

	if (plik.good() == false)
	{
		cout << "Plik nie istnieje" << endl;
		exit(0);
	}

	int ile;
	ile = ile_klientow_w_pliku();

	string *T_id;
	T_id = new string[ile];

	string *T_imie;
	T_imie = new string[ile];

	string *T_nazwisko;
	T_nazwisko = new string[ile];

	string *T_pesel;
	T_pesel = new string[ile];

	string *T_email;
	T_email = new string[ile];

	string *T_telefon;
	T_telefon = new string[ile];



	string linia;
	int nr_lini = 1;
	int numer_klienta = 0;

	while (getline(plik, linia))
	{
		switch (nr_lini)
		{
		case 1:
		{	
			T_id[numer_klienta] = linia;
			break;
		}

		case 2:
		{
			T_imie[numer_klienta] = linia;
			break;
		}

		case 3:
		{
			T_nazwisko[numer_klienta] = linia;
			break;
		}

		case 4:
		{
			T_pesel[numer_klienta] = linia;
			break;
		}
		case 5:
		{
			T_email[numer_klienta] = linia;
			break;
		}
		case 6:
		{
			T_telefon[numer_klienta] = linia;
			break;
		}
		default:
			break;
		}

		nr_lini++;
		if (nr_lini == 7)
		{
			nr_lini = 1;
			numer_klienta++;
		}
	};

	cout << "ID: ";
	cout.width(15);
	cout << "Imie: ";
	cout.width(18);
	cout << "Nazwisko: ";
	cout.width(15);
	cout << "Pesel: ";
	cout.width(26);
	cout << "Email: ";
	cout.width(27);
	cout << "Numer tel: " << endl;

	int temp = 0;
	do
	{

		cout << T_id[temp];
		cout.width(16);
		cout << T_imie[temp];
		cout.width(18);
		cout << T_nazwisko[temp];
		cout.width(16);
		cout << T_pesel[temp];
		cout.width(30);
		cout << T_email[temp];
		cout.width(21);
		cout << T_telefon[temp] << endl;

		temp++;
	} while (temp < ile);

	delete[] T_id;
	delete[] T_imie;
	delete[] T_nazwisko;
	delete[] T_pesel;
	delete[] T_email;
	delete[] T_telefon;

	plik.close();
	plik.clear();
};

void usun_klienta()
{
	///// SPRAWDZA ILE JEST OSOB I TWORZY TABLICE TYLO ELEMENTOWE 

	void odczytaj_liste_klientow();
	int ile_klientow_w_pliku();
	bool czy_dobry_numer_id_chcemy_usunac(int *tab, int ile, int liczba);
	int numer_id, ile_elementow_w_tablicy;

	int ile;
	ile = ile_klientow_w_pliku();
	if (ile == 0)
	{
		cout << "Plik jest pusty, nie ma co usuwac :/" << endl;
		Sleep(2000);
		return;
	}




	ile_elementow_w_tablicy = ile_klientow_w_pliku();


	string *T_imie;
	T_imie = new string[ile_elementow_w_tablicy];

	string *T_nazwisko;
	T_nazwisko = new string[ile_elementow_w_tablicy];

	string *T_pesel;
	T_pesel = new string[ile_elementow_w_tablicy];

	string *T_email;
	T_email = new string[ile_elementow_w_tablicy];

	string *T_numer_tel;
	T_numer_tel = new string[ile_elementow_w_tablicy];

	int *T_id;
	T_id = new int[ile_elementow_w_tablicy];

	///// WPISUJE STARE DANE DO TABLIC 

	fstream plik;
	plik.open("Lista_klientow.txt", ios::in);

	if (plik.good() == false)
	{
		cout << "Cos poszlo nie tak przy otwarciu pliku :( " << endl;
		exit(0);
	}

	string linia;
	int numer_lini = 1;
	int numer_osoby = 0;

	while (getline(plik, linia))
	{
		switch (numer_lini)
		{
		case 1:
		{
			T_id[numer_osoby] = atoi(linia.c_str());
			break;
		}
		case 2:
		{
			T_imie[numer_osoby] = linia;
			break;
		}
		case 3:
		{
			T_nazwisko[numer_osoby] = linia;
			break;
		}
		case 4:
		{
			T_pesel[numer_osoby] = linia;
			break;
		}
		case 5:
		{
			T_email[numer_osoby] = linia;
			break;
		}
		case 6:
		{
			T_numer_tel[numer_osoby] = linia;
			break;
		}


		default: break;
		}

		numer_lini++;

		if (numer_lini == 7)
		{
			numer_lini = 1;
			numer_osoby++;
		};
	}


	plik.close();
	plik.clear();

	// WYPISUJE OSOBY Z STAREGO PLIKU I PYTA KOGO USUNAC

	cout << "To wszystkie osoby w tablicy : " << endl;
	odczytaj_liste_klientow();
	cout << endl;

	char tak_nie;

	do
	{
		do
		{
			cout << "Podaj numer id osoby ktora chcesz usunac : ";
			cin >> numer_id;

			if (czy_dobry_numer_id_chcemy_usunac(T_id, ile_elementow_w_tablicy, numer_id) == false)
			{
				cout << "Podales zly numer id :/" << endl;
			}

		} while (czy_dobry_numer_id_chcemy_usunac(T_id,ile_elementow_w_tablicy, numer_id) != true);

		cout << "Napewno chcesz usunac (y/n): " << endl;
		cin >> tak_nie;

		if (tak_nie == 'n')
		{	
			string co_dalej;
			cout << "Czy chcesz powrocic do menu ? (y/n)" << endl;
			cin >> co_dalej;
			if (co_dalej == "y")
			{
				return;
			}
		}

	} while (tak_nie != 'y');
	// USUWA STARY PLIK 

	remove("Lista_klientow.txt");

	// WPISUJE OSOBY DO NOWEGO PLIKU TXT BEZ OSOBY Z PODANYM NUMEREM ID

	fstream plik1;
	plik1.open("Lista_klientow.txt", ios::out | ios::app);

	numer_osoby = 0;
	do
	{
		if (T_id[numer_osoby] == numer_id)
		{
			numer_osoby++;
			if (numer_osoby == ile_elementow_w_tablicy)
			{
				break;
			}
		}

		plik1 << T_id[numer_osoby] << endl;
		plik1 << T_imie[numer_osoby] << endl;
		plik1 << T_nazwisko[numer_osoby] << endl;
		plik1 << T_pesel[numer_osoby] << endl;
		plik1 << T_email[numer_osoby] << endl;
		plik1 << T_numer_tel[numer_osoby] << endl;

		numer_osoby++;

	} while (numer_osoby < ile_elementow_w_tablicy);


	plik.close();
	plik.clear();


	// USUWA NIEPOTRZEBNE TABLICE I ZWALNIA PAMIEC
	delete[] T_imie;
	delete[] T_nazwisko;
	delete[] T_pesel;
	delete[] T_email;
	delete[] T_numer_tel;
	delete[] T_id;
};
bool czy_dobry_numer_id_chcemy_usunac(int *tab,int ile, int liczba)
{
	for (int i = 0; i < ile; i++)
	{
		if (*tab == liczba) return true;
		else
		{
			tab++;
		}
	}
	
	return false;
}


/////////////////////////////////////////////////////////// SAMOCHOD

void wczytaj_samochod()
{
	string marka, model, nr_rejestracji, rocznik, przebieg, vin;
	int id;
	int losuj_nr_id_samochodu();
	id = losuj_nr_id_samochodu(); // tworzy unikatowy numer id

	cout << "Podaj marke : " << endl;
	cin.sync();
	getline(cin, marka);

	cout << "Podaj model : " << endl;
	cin.sync();
	getline(cin, model);

	cout << "Podaj nr rejestracji : " << endl;
	cin.sync();
	getline(cin, nr_rejestracji);

	cout << "Podaj rocznik : " << endl;
	cin.sync();
	getline(cin, rocznik);

	cout << "Podaj przebieg : " << endl;
	cin.sync();
	getline(cin, przebieg);

	cout << "Podaj nr Vin : " << endl;
	cin.sync();
	getline(cin, vin);

	fstream plik;
	plik.open("Samochody.txt", ios::out | ios::app);

	plik << id << endl;
	plik << marka << endl;
	plik << model << endl;
	plik << nr_rejestracji << endl;
	plik << rocznik << endl;
	plik << przebieg << endl;
	plik << vin << endl;

	plik.close();
	plik.clear();

}

int ile_aut_w_pliku()
{

	fstream plik;
	plik.open("Samochody.txt", ios::in | ios::app);

	if (plik.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku :/" << endl;
		exit(0);
	}

	string linia;
	int numer_lini = 0;
	int ile = 0;

	while (getline(plik, linia))
	{
		switch (numer_lini)
		{
			case 1:
			{
				ile += 1;
			}
		default:
			break;
		}

		numer_lini++;

		if (numer_lini == 8) numer_lini = 1;

	}

	return ile;
}

int losuj_nr_id_samochodu()
{
	int elementy;
	int ile_aut_w_pliku();

	elementy = ile_aut_w_pliku();

	int *tablica;
	tablica = new int[elementy]; // tworzy tablice

    //////////////////////////////////////////////// wpisuje uzywane juz id do tablicy
	fstream plik;
	plik.open("Samochody.txt", ios::in | ios::app);

	if (plik.good() == false)
	{
		cout << "Plik nie istnieje" << endl;
		exit(0);
	}

	int nr_lini = 1;
	string linia;

	while (getline(plik, linia))
	{
		switch (nr_lini)
		{
		case 1:
		{
			*tablica = atoi(linia.c_str()); 
			tablica++;
		}
		default: break;
		}

		nr_lini++;

		if (nr_lini == 8) nr_lini = 1;
	}

	//////////////////////////////////////////////////////////// losuje unikatowy id

	int losowana;

	losowana = rand() % 100 + 101;
	int i = 0;

	do
	{

		if (losowana == tablica[i])
		{
			losowana = rand() % 100 + 101;
			i = -1;
		}
		i++;

	} while (i < elementy);

	return losowana;

	delete[] tablica;
	plik.close();
	plik.clear();
}

void odczytaj_liste_samochodow()
{

	int ile_aut_w_pliku();

	if (ile_aut_w_pliku() == 0)
	{
		cout << "W pliku nic nie ma" << endl;
	}

	fstream plik;
	plik.open("Samochody.txt", ios::in | ios::app);

	if (plik.good() == false)
	{
		cout << "Plik nie istnieje" << endl;
		exit(0);
	}

	int ile;
	ile = ile_aut_w_pliku();

	string *T_id;
	T_id = new string[ile];

	string *T_marka;
	T_marka = new string[ile];

	string *T_model;
	T_model = new string[ile];

	string *T_rej;
	T_rej = new string[ile];

	string *T_rocznik;
	T_rocznik = new string[ile];

	string *T_przebieg;
	T_przebieg = new string[ile];

	string *T_vin;
	T_vin = new string[ile];




	string linia;
	int nr_lini = 1, nr_samochodu = 0;


	while (getline(plik, linia))
	{
		switch (nr_lini)
		{
		case 1:
		{
			T_id[nr_samochodu] = linia;
			break;
		}
		case 2:
		{
			T_marka[nr_samochodu] = linia;
			break;
		}

		case 3:
		{
			T_model[nr_samochodu] = linia;
			break;
		}

		case 4:
		{
			T_rej[nr_samochodu] = linia;
			break;
		}

		case 5:
		{
			T_rocznik[nr_samochodu] = linia;
			break;
		}
		case 6:
		{
			T_przebieg[nr_samochodu] = linia;
			break;
		}
		case 7:
		{
			T_vin[nr_samochodu] = linia;
			break;
		}
		default:
			break;
		}
		nr_lini++;

		if (nr_lini == 8)
		{
			nr_lini = 1;
			nr_samochodu++;
		}
	};


	cout << "ID: ";
	cout.width(12);
	cout << "Marka: ";
	cout.width(13);
	cout << "Model: ";
	cout.width(18);
	cout << "Numer rej: ";
	cout.width(17);
	cout << "Rocznik: ";
	cout.width(20);
	cout << "Przebieg: ";
	cout.width(17);
	cout << "Vin: " << endl;

	int temp = 0;
	do
	{

		cout << T_id[temp];
		cout.width(11);
		cout << T_marka[temp];
		cout.width(14);
		cout << T_model[temp];
		cout.width(16);
		cout << T_rej[temp];
		cout.width(17);
		cout << T_rocznik[temp];
		cout.width(20);
		cout << T_przebieg[temp];
		cout.width(22);
		cout << T_vin[temp] << endl;

		temp++;
	} while (temp < ile);

	delete[] T_id;
	delete[] T_marka;
	delete[] T_model;
	delete[] T_rej;
	delete[] T_rocznik;
	delete[] T_przebieg;
	delete[] T_vin;


	plik.close();
	plik.clear();
};

void usun_samochod()
{
	///// SPRAWDZA ILE JEST OSOB I TWORZY TABLICE TYLO ELEMENTOWE 

	void odczytaj_liste_samochodow();
	int ile_aut_w_pliku();
	bool czy_dobry_numer_id_chcemy_usunac(int *tab, int ile, int liczba);
	int ile_elementow_w_tablicy;

	int ile;
	ile = ile_aut_w_pliku();
	if (ile == 0)
	{
		cout << "Plik jest pusty, nie ma co usuwac :/" << endl;
		Sleep(2000);
		return;
	}




	ile_elementow_w_tablicy = ile_aut_w_pliku();


	string *T_marka;
	T_marka = new string[ile_elementow_w_tablicy];

	string *T_model;
	T_model = new string[ile_elementow_w_tablicy];

	string *T_nr_rejestracji;
	T_nr_rejestracji = new string[ile_elementow_w_tablicy];

	string *T_rocznik;
	T_rocznik = new string[ile_elementow_w_tablicy];

	string *T_przebieg;
	T_przebieg = new string[ile_elementow_w_tablicy];

	string *T_vin;
	T_vin = new string[ile_elementow_w_tablicy];

	int *T_id;
	T_id = new int[ile_elementow_w_tablicy];

	///// WPISUJE STARE DANE DO TABLIC 

	fstream plik;
	plik.open("Samochody.txt", ios::in);

	if (plik.good() == false)
	{
		cout << "Cos poszlo nie tak przy otwarciu pliku :( " << endl;
		exit(0);
	}

	string linia;
	int numer_lini = 1;
	int numer_samochodu = 0;

	while (getline(plik, linia))
	{
		switch (numer_lini)
		{
		case 1:
		{
			T_id[numer_samochodu] = atoi(linia.c_str());
			break;
		}
		case 2:
		{
			T_marka[numer_samochodu] = linia;
			break;
		}
		case 3:
		{
			T_model[numer_samochodu] = linia;
			break;
		}
		case 4:
		{
			T_nr_rejestracji[numer_samochodu] = linia;
			break;
		}
		case 5:
		{
			T_rocznik[numer_samochodu] = linia;
			break;
		}
		case 6:
		{
			T_przebieg[numer_samochodu] = linia;
			break;
		}
		case 7:
		{
			T_vin[numer_samochodu] = linia;
			break;
		}

		default: break;
		}

		numer_lini++;

		if (numer_lini == 8)
		{
			numer_lini = 1;
			numer_samochodu++;
		};
	}


	plik.close();
	plik.clear();

	// WYPISUJE OSOBY Z STAREGO PLIKU I PYTA KOGO USUNAC

	cout << "To wszystkie samochody w tablicy : " << endl;
	odczytaj_liste_samochodow();
	cout << endl;

	char tak_nie;
	int numer_id;
	do
	{
		do
		{
			cout << "Podaj numer id samochodu ktory chcesz usunac : ";
			cin >> numer_id;

			if (czy_dobry_numer_id_chcemy_usunac(T_id, ile_elementow_w_tablicy, numer_id) == false)
			{
				cout << "Podales zly numer id :/" << endl;
			}

		} while (czy_dobry_numer_id_chcemy_usunac(T_id, ile_elementow_w_tablicy, numer_id) != true);

		cout << "Napewno chcesz usunac (y/n): " << endl;
		cin >> tak_nie;

		if (tak_nie == 'n')
		{
			string co_dalej;
			cout << "Czy chcesz powrocic do menu ? (y/n)" << endl;
			cin >> co_dalej;
			if (co_dalej == "y")
			{
				return;
			}
		}

	} while (tak_nie != 'y');
	// USUWA STARY PLIK 

	remove("Samochody.txt");

	// WPISUJE OSOBY DO NOWEGO PLIKU TXT BEZ OSOBY Z PODANYM NUMEREM ID

	fstream plik1;
	plik1.open("Samochody.txt", ios::out | ios::app);

	numer_samochodu = 0;
	do
	{
		if (T_id[numer_samochodu] == numer_id)
		{
			numer_samochodu++;
			if (numer_samochodu == ile_elementow_w_tablicy)
			{
				break;
			}
		}

		plik1 << T_id[numer_samochodu] << endl;
		plik1 << T_marka[numer_samochodu] << endl;
		plik1 << T_model[numer_samochodu] << endl;
		plik1 << T_nr_rejestracji[numer_samochodu] << endl;
		plik1 << T_rocznik[numer_samochodu] << endl;
		plik1 << T_przebieg[numer_samochodu] << endl;
		plik1 << T_vin[numer_samochodu] << endl;

		numer_samochodu++;

	} while (numer_samochodu < ile_elementow_w_tablicy);


	plik.close();
	plik.clear();


	// USUWA NIEPOTRZEBNE TABLICE I ZWALNIA PAMIEC
	delete[] T_model;
	delete[] T_marka;
	delete[] T_nr_rejestracji;
	delete[] T_rocznik;
	delete[] T_przebieg;
	delete[] T_vin;
	delete[] T_id;
};

//////////////////////////////////////////////////////////////
void edytuj()
{
	int na_ktorym_miejscu_w_tablicy(int *tab, int ile, int liczba);
	bool czy_dobry_numer_id_chcemy_usunac(int *tab, int ile, int liczba);
	int ile_aut_w_pliku();
	int ile_klientow_w_pliku();
	int wielkosc_tablicy;

	string otwieramy;
	string ktory_plik;
	
		cout << "Co chcesz zmodyfikowac ? (Samochod/Klient)" << endl;
		getline(cin, ktory_plik);
		if (ktory_plik != "Samochod" && ktory_plik != "Klient") return;

	if (ktory_plik == "Samochod")
	{
		otwieramy = "Samochody.txt";
		wielkosc_tablicy = ile_aut_w_pliku();

		if (wielkosc_tablicy == 0)
		{
			cout << "Plik jest pusty wracam do menu" << endl;
			Sleep(1000);
			return;
		}
	}
	if (ktory_plik == "Klient")
	{
		otwieramy = "Lista_Klientow.txt";
		wielkosc_tablicy = ile_klientow_w_pliku();

		if (wielkosc_tablicy == 0)
		{
			cout << "Plik jest pusty wracam do menu" << endl;
			Sleep(1000);
			return;
		}
	}



	int *T_id;
	T_id = new int[wielkosc_tablicy];

	string *T_pierwszy;
	T_pierwszy = new string[wielkosc_tablicy];

	string *T_drugi;
	T_drugi = new string[wielkosc_tablicy];

	string *T_trzeci;
	T_trzeci = new string[wielkosc_tablicy];

	string *T_czwarty;
	T_czwarty = new string[wielkosc_tablicy];

	string *T_piaty;
	T_piaty = new string[wielkosc_tablicy];

    string *T_szosty;
	T_szosty = new string[wielkosc_tablicy];

	fstream plik;
	plik.open(otwieramy, ios::in | ios::app);



	if (plik.good() == false)
	{
		cout << "Cos zjebales";
	}

	// wczytuje elementy do tablic
	if (ktory_plik == "Samochod")
	{
		string linia;
		int numer_lini = 1;
		int numer = 0;

		while (getline(plik, linia))
		{
			switch (numer_lini)
			{
			case 1:
			{
				T_id[numer] = atoi(linia.c_str());
				break;
			}
			case 2:
			{
				T_pierwszy[numer] = linia;
				break;
			}
			case 3:
			{
				T_drugi[numer] = linia;
				break;
			}
			case 4:
			{
				T_trzeci[numer] = linia;
				break;
			}
			case 5:
			{
				T_czwarty[numer] = linia;
				break;
			}
			case 6:
			{
				T_piaty[numer] = linia;
				break;
			}
			case 7:
			{
				T_szosty[numer] = linia;
				break;
			}

			default: break;
			}

			numer_lini++;

			if (numer_lini == 8)
			{
				numer_lini = 1;
				numer++;
			};
		}

	}

	if (ktory_plik == "Klient")
	{
		string linia;
		int numer_lini = 1;
		int numer = 0;

		while (getline(plik, linia))
		{
			switch (numer_lini)
			{
			case 1:
			{
				T_id[numer] = atoi(linia.c_str());
				break;
			}
			case 2:
			{
				T_pierwszy[numer] = linia;
				break;
			}
			case 3:
			{
				T_drugi[numer] = linia;
				break;
			}
			case 4:
			{
				T_trzeci[numer] = linia;
				break;
			}
			case 5:
			{
				T_czwarty[numer] = linia;
				break;
			}
			case 6:
			{
				T_piaty[numer] = linia;
				break;
			}


			default: break;
			}

			numer_lini++;

			if (numer_lini == 7)
			{
				numer_lini = 1;
				numer++;
			};
		}
		
	}

	plik.close();
	plik.clear();

	// wypisuje elementy

	if (ktory_plik == "Samochod")
	{
		cout << "Oto pelna lista samochodow: " << endl << endl;
		int numer = 0;

		do
		{
			cout << "ID :" << T_id[numer] << endl;
			cout << "Marka :" << T_pierwszy[numer] << endl;
			cout << "Model :" << T_drugi[numer] << endl;
			cout << "Numer rej :" << T_trzeci[numer] << endl;
			cout << "Rocznik :" << T_czwarty[numer] << endl;
			cout << "Przebieg :" << T_piaty[numer] << endl;
			cout << "Nr Vin :" << T_szosty[numer] << endl;
			cout << endl;

			numer++;

		} while (numer < wielkosc_tablicy);
	}
	
	if (ktory_plik == "Klient")
	{
		cout << "Oto pelna lista klientow: " << endl << endl;
		int numer = 0;

		do
		{
			cout << "ID :" << T_id[numer] << endl;
			cout << "Imie :" << T_pierwszy[numer] << endl;
			cout << "Nazwisko :" << T_drugi[numer] << endl;
			cout << "Pesel :" << T_trzeci[numer] << endl;
			cout << "Email :" << T_czwarty[numer] << endl;
			cout << "Numer tel :" << T_piaty[numer] << endl;
			cout << endl;

			numer++;

		} while (numer < wielkosc_tablicy);
	}
	
	int numer_id;
	string tak_nie;

	// wczytuje numer id do zmodyfikowania i sprawdza czy jest poprawny
	do
	{
		do
		{
	
			cout << "Podaj numer id ktory chcesz zmodyfikowac : " << endl;
			cin >> numer_id;
			cin.sync();
			cin.clear();
			cin.ignore();
		
			if (czy_dobry_numer_id_chcemy_usunac(T_id, wielkosc_tablicy, numer_id) == false)
			{
				cout << "Podales zly numer id !" << endl;
			}
		} while (czy_dobry_numer_id_chcemy_usunac(T_id, wielkosc_tablicy, numer_id) != true);

		cout << "Napewno chcesz modyfikowac (y/n): " << endl;
		cin >> tak_nie;

		if (tak_nie != "y" && tak_nie != "n")
		{
			cout << "Cos poszlo nie tak, wracam.";
				Sleep(1000);
				return;
		}

		if (tak_nie == "n")
		{
			string co_dalej;
			cout << "Czy chcesz powrocic do menu ? (y/n)" << endl;
			cin >> co_dalej;
			if (co_dalej == "y")
			{
				return;
			}
		}

	} while (tak_nie != "y");

	int modyfikowany = na_ktorym_miejscu_w_tablicy(T_id, wielkosc_tablicy, numer_id);

	// nadpisuje zmiany 

	if (ktory_plik == "Samochod")
	{
		system("cls");
		cout << "Stare dane :" << endl << endl;
		cout << "ID :" << T_id[modyfikowany] << endl;
		cout << "Marka :" << T_pierwszy[modyfikowany] << endl;
		cout << "Model :" << T_drugi[modyfikowany] << endl;
		cout << "Numer rej :" << T_trzeci[modyfikowany] << endl;
		cout << "Rocznik :" << T_czwarty[modyfikowany] << endl;
		cout << "Przebieg :" << T_piaty[modyfikowany] << endl;
		cout << "Nr Vin :" << T_szosty[modyfikowany] << endl;
		cout << endl;

		cout << "Prosze wczytac nowe dane (Jezeli nie chcesz edytowac przepisz stare dane) : " << endl;

		string marka, model, nr_rejestracji, rocznik, przebieg, vin;

		cin.ignore();
		cout << "Podaj marke : ";
		cin.sync();
		getline(cin, marka);

		cout << "Podaj model : ";
		cin.sync();
		getline(cin, model);

		cout << "Podaj nr rejestracji : ";
		cin.sync();
		getline(cin, nr_rejestracji);

		cout << "Podaj rocznik : ";
		cin.sync();
		getline(cin, rocznik);

		cout << "Podaj przebieg : ";
		cin.sync();
		getline(cin, przebieg);

		cout << "Podaj nr Vin : ";
		cin.sync();
		getline(cin, vin);

		system("cls");
	
		cout << "Nowe dane : " << endl;
		cout << "ID : " << T_id[modyfikowany] << endl;
		cout << "Marka :" << marka << endl;
		cout << "Model : " << model << endl;
		cout << "Nr rej :" << nr_rejestracji << endl;
		cout << "Rocznik :" << rocznik << endl;
		cout << "Przebieg :" << przebieg << endl;
		cout << "Vin :" << vin << endl << endl;

		string temp;

		cout << "Jezeli dane sie zgadzaja potwierdz (y) w przeciwnym wypadku wroc do menu (n)" << endl;
		cin >> temp;

		if (temp == "n")  return;

		T_pierwszy[modyfikowany] = marka;
		T_drugi[modyfikowany] = model;
		T_trzeci[modyfikowany] = nr_rejestracji;
		T_czwarty[modyfikowany] = rocznik;
		T_piaty[modyfikowany] = przebieg;
		T_szosty[modyfikowany] = vin;
	

	}
	if (ktory_plik == "Klient")
	{
		system("cls");
		cout << "Stare dane :" << endl << endl;
		cout << "Id :" << T_id[modyfikowany] << endl;
		cout << "Imie :" << T_pierwszy[modyfikowany] << endl;
		cout << "Nazwisko :" << T_drugi[modyfikowany] << endl;
		cout << "Pesel :" << T_trzeci[modyfikowany] << endl;
		cout << "Email :" << T_czwarty[modyfikowany] << endl;
		cout << "Numer tel :" << T_piaty[modyfikowany] << endl;
		cout << endl;

		cout << "Prosze wczytac nowe dane (Jezeli nie chcesz edytowac przepisz stare dane) : " << endl;

		string imie, nazwisko, pesel, email, numer_tel;

		cin.ignore();
		cout << "Podaj imie : ";
		cin.sync();
		getline(cin, imie);

		cout << "Podaj nazwisko : ";
		cin.sync();
		getline(cin, nazwisko);

		cout << "Podaj pesel : ";
		cin.sync();
		getline(cin, pesel);

		cout << "Podaj email : ";
		cin.sync();
		getline(cin, email);

		cout << "Podaj numer telefonu : ";
		cin.sync();
		getline(cin, numer_tel);

		system("cls");

		cout << "Nowe dane : " << endl;
		cout << "ID : " << T_id[modyfikowany] << endl;
		cout << "Imie :" << imie << endl;
		cout << "Nazwisko : " << nazwisko << endl;
		cout << "Pesel :" << pesel << endl;
		cout << "Email :" << email << endl;
		cout << "Numer tel :" << numer_tel << endl << endl;

		string temp;

		cout << "Jezeli dane sie zgadzaja potwierdz (y) w przeciwnym wypadku wroc do menu (n)" << endl;
		cin >> temp;

		if (temp == "n")  return;

		T_pierwszy[modyfikowany] = imie;
		T_drugi[modyfikowany] = nazwisko;
		T_trzeci[modyfikowany] = pesel;
		T_czwarty[modyfikowany] = email;
		T_piaty[modyfikowany] = numer_tel;
	}

	// USUWA STARY PLIK I TWORZY NOWY (PRZEPISUJE TAM TABLICE)

	if (ktory_plik == "Samochod")
	{
		remove("Samochody.txt");

		fstream plik1;
		plik1.open("Samochody.txt", ios::out | ios::app);;

		int i = 0;
		do
		{
			plik1 << T_id[i] << endl;
			plik1 << T_pierwszy[i] << endl;
			plik1 << T_drugi[i] << endl;
			plik1 << T_trzeci[i] << endl;
			plik1 << T_czwarty[i] << endl;
			plik1 << T_piaty[i] << endl;
			plik1 << T_szosty[i] << endl;

			i++;

		} while (i < wielkosc_tablicy);
	

		plik1.close();
		plik1.clear();
	}

	if (ktory_plik == "Klient")
	{
		remove("Lista_klientow.txt");

		fstream plik1;
		plik1.open("Lista_klientow.txt", ios::out | ios::app);;

		int i = 0;
		do
		{
			plik1 << T_id[i] << endl;
			plik1 << T_pierwszy[i] << endl;
			plik1 << T_drugi[i] << endl;
			plik1 << T_trzeci[i] << endl;
			plik1 << T_czwarty[i] << endl;
			plik1 << T_piaty[i] << endl;

			i++;

		} while (i < wielkosc_tablicy);


		plik1.close();
		plik1.clear();
	}


	delete[] T_id;
	delete[] T_pierwszy;
	delete[] T_drugi;
	delete[] T_trzeci;
	delete[] T_czwarty;
	delete[] T_piaty;
	delete[] T_szosty;
}
int na_ktorym_miejscu_w_tablicy(int *tab, int ile, int liczba)
{
	int na_ktorym = 0;
	do
	{
		if (*tab == liczba)
		{
			return na_ktorym;
		}

		tab++;
		na_ktorym++;

	} while (na_ktorym < ile);

	return na_ktorym;
}

//////////////////////////////////////////////////////////////

void wypozycz_auto()
{



}



int main()
{
	srand(time(NULL));
	int liczba;

	for (;;)
	{
		cout << endl;
		cout << "[0] Wyczysc ekran" << endl;
		cout << "[1] Wyjscie z programu" << endl;
		cout << "[2] Dodaj klienta " << endl;
		cout << "[3] Zobacz liste klientow " << endl;
		cout << "[4] Usun klienta " << endl;
		cout << "[5] Dodaj samochod" << endl;
		cout << "[6] Zobacz liste samochodow" << endl;
		cout << "[7] Usun samochod" << endl;
		cout << "[8] Edycja Klienta/Samochodu" << endl;
		cout << "--------Wypozyczalnia--------" << endl;
		cout << "[9] Dodaj wypozyczenie" << endl;
		cout << "Usun wypozyczenie" << endl;
		cout << "--------Historia--------" << endl;
		cout << "Pokaz historie klienta" << endl;
		cout << "Pokaz historie samochodu" << endl;
		cin >> liczba;

		cin.ignore();
		switch (liczba)
		{
		case 0:
		{
			system("cls");
			break;
		}
		case 1:
		{
			exit(0);
			break;
		}
		case 2:
		{
			system("cls");
			wczytaj_klienta();
			system("cls");
			break;
		}
		case 3:
		{
			system("cls");
			odczytaj_liste_klientow();
			break;
		}
		case 4:
		{
			system("cls");
			usun_klienta();
			system("cls");
			break;
		}
		case 5:
		{
			system("cls");
			wczytaj_samochod();
			system("cls");
			break;
		}
		case 6:
		{
			system("cls");
			odczytaj_liste_samochodow();
			break;
		}
		case 7:
		{
			system("cls");
			usun_samochod();
			system("cls");
			break;
		}
		case 8:
		{
			system("cls");
			edytuj();
			system("cls");
			break;
		}
		case 9:
		{
			system("cls");
			wypozycz_auto();
			system("cls");
			break;
		}
		default:
		{
			cout << "Cos poszlo nie tak :/" << endl;
			break;
		}

		}
	};

	system("Pause");
	return 0;
}