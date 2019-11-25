//POP 2014-12-16 projekt 1 S³upecka Joanna IBM 3 155331; VS Professional 2013, cl

#include<iostream>
#include<iomanip>
#include <string>
#include<cctype>
using namespace std;

const int n = 26;

void drukuj(char a[n][n])						//wypisywanie tablicy
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << string(1, a[i][j]) << " ";
		}
		cout << endl;
	}
}

void wpisywanie(string & zdanie, string & haslo)
{
	cout << "Podaj tekst ktory chcesz zaszyfrowac: ";
	getline(cin, zdanie);
	cout << "Podaj haslo: ";
	getline(cin, haslo);

}

void zamiana(string & s)						//zamiana ma³ych liter na wielkie
{
	for (int i = 0; i < s.size(); i++)
	{
		s[i] = toupper(s[i]);
	}

}
string szyfrowanie(string & zdanie, string & haslo, char a[n][n])
{
	string wynik(zdanie.size(), '*');
	int k = 0;
	for (int i = 0; i < zdanie.size(); i++)
	{
		char znakZdania = zdanie[i];
		if (znakZdania >= 'A' && znakZdania <= 'Z')
		{
			int kolumna = znakZdania - 'A';

			char znakhasla = haslo[k % haslo.size()];
			int wiersz = znakhasla - 'A';

			char zaszyfrowanaliterka = a[kolumna][wiersz];   // zaszyfrowana literka
			wynik[i] = zaszyfrowanaliterka;				   //zaszyfrowane zdanie
			k++;
		}
		else
		{
			wynik[i] = znakZdania;
		}
	}
	return wynik;
}
string rozszyfrowanie(string & tekstZaszyfrowany, string & haslo, char a[n][n])
{
	string wynik(tekstZaszyfrowany.size(), '*');
	int k = 0;
	for (int i = 0; i < tekstZaszyfrowany.size(); i++)
	{
		char znak = tekstZaszyfrowany[i];				//znak zaszyfrowanego tekstu
		if (znak >= 'A' && znak <= 'Z')
		{
			char znakHasla = haslo[k % haslo.size()];
			int kolumna = znakHasla - 'A';
			int wiersz;
			for (int w = 0; w < n; w++)
			{
				if (a[kolumna][w] == znak)
				{
					wiersz = w;
					break;
				}
			}

			char rozszyfrowanaliterka = a[0][wiersz];
			wynik[i] = rozszyfrowanaliterka;
			k++;
		}
		else
		{
			wynik[i] = znak;
		}
	}
	return wynik;
}


int main()
{
	string zdanie;
	string haslo;
	char a[n][n];
	const int n = 26;


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = (i + j) % n + 'A';
		}

	}
	drukuj(a);
	wpisywanie(zdanie, haslo);
	zamiana(zdanie);
	zamiana(haslo);
	string tekstZaszyfrowany = szyfrowanie(zdanie, haslo, a);
	rozszyfrowanie(tekstZaszyfrowany, haslo, a);
	string tekstRozszyfrowany = rozszyfrowanie(tekstZaszyfrowany, haslo, a);
	cout << tekstZaszyfrowany << endl;
	cout << tekstRozszyfrowany << endl;


	system("pause");
	return 0;
}