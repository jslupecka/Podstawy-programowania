#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;


void wprowadz_licz(int & i)
{
	cout << "Wprowadz licznik poczatkowy:";
	cin >> i;
}
int tryb()
{
	int i;
	cout << "Szyfrowanie-wcisnij 1, Deszyfrowanie-wcisnij 2:";
	cin >> i;
	return i;
}

int wprowadz_plik_i_zrob_nowy(ifstream & plikwe, ofstream & plikwy)
{
	string nazwa_we;
	cout << "Podaj nazwe pliku, ktory chcesz zaszyfrowac:";
	cin  >> nazwa_we;

 plikwe=ifstream (nazwa_we.c_str());

	if (!plikwe)
	{
		cerr << "blad: nie mozna otworzyc pliku wejsciowego: "
			<< nazwa_we << endl;
		return -1;
	}

	string nazwa_wy = nazwa_we;
	auto kropka = nazwa_wy.rfind(".");
	nazwa_wy.insert(kropka, "zaszyfrowany.");

	plikwy=ofstream (nazwa_wy.c_str());
	if (!plikwy)
	{
		cerr << "blad: nie mozna otworzyc pliku wyjsciowego: "
			<< nazwa_wy << endl;
		return -2;

	}

}

void szyfrowanie(ifstream & plikwe, ofstream & plikwy, int licznik, bool deszyfruj )
{
	const int rozmiar = 16;
	char bufWe [rozmiar];
	char bufWy[rozmiar];
	char wektor = 0xAA;
	bool szyfruj=true;

	while (szyfruj)
	{
		plikwe.read(bufWe, rozmiar);
		int liczba_wczytanych = plikwe.gcount();
		for (int i = 0; i < liczba_wczytanych; i++)
		{
			wektor = bufWe[i] ^ wektor ^ (char) licznik;
			bufWy[i] = wektor;
			if (deszyfruj)
			{
				wektor = bufWe[i];
			}
			licznik++;
			if (licznik > 255)
			{
				licznik = 0;
			}
		}
		plikwy.write(bufWy, liczba_wczytanych);
		if (liczba_wczytanych < rozmiar)
			szyfruj = false;
	}

}


int main()

{
	int licznik; 
	bool czy_deszyf;
	int tryb_pracy = tryb();
	switch (tryb_pracy)
	{
	case 1:
		czy_deszyf = false;
		break;
	case 2:
		czy_deszyf = true;
		break;
	default:
		return 1;
		break;
	}
	ifstream plikwe;
	ofstream plikwy;
	wprowadz_licz(licznik);
	wprowadz_plik_i_zrob_nowy(plikwe, plikwy);
	szyfrowanie(plikwe, plikwy, licznik, czy_deszyf);
	plikwe.close();
	plikwy.close();
	return 0;
}

