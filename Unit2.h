/**
*@file Unit2.h
*@author Dorian Baranski
*@version 1.0
*@date 2019-01-18
*/

//---------------------------------------------------------------------------

#define _CRTDBG_MAP_ALLOC
#ifndef Unit2H
#define Unit2H
#include <fstream>
using namespace std;

//---------------------------------------------------------------------------

/*! Structura wezel
Struktura listy dwukierunkowej, ktora przechowuje informacje o wezle ukladu
*/
struct wezel
{
  string  funkcja; //!funkcja logiczna
  int     we1; //!wejscie pierwsze
  int	  we1val; //1 wartosc wejscia pierwszego
  int     we2; //!wejscie drugie
  int	  we2val; //!wartosc wejscia drugiego
  int     wyf;//!wyjscie wezla
  int	  wyfval;//!wartosc wyjscia
  wezel   *nst; //!wskaznik na nastepny element listy
  wezel   *pop; //!wskaznik na poprzedni element lsity
};

/*!
Opis funkcji:

Ponizsza funkcja wyswietla informacje na temat przykladowego uruchomienia.
Jest to pomoc w przypadku ewentualnych problemow przy odpaleniu programu.

parametry funkcji:

-brak-
*/
void OpcjeProgramu(void);

/*!
Opis funkcji:

Sprawdza czy uzyte przez uzytkownika przerzutniki maja poprawna forme.
Musza miec dlugosc rowna 2, a ich kolejnosc moze byc dowolna.
W przypadku nieodpowiedniego formatu zostaje podana informacja o popelnionym bledzie.

parametry funkcji:

-i - Przerzutnik do pliku z danymi wejsciowymi
-u - Przerzutnik do pliku z ukladem
-o - Przerzutnik do pliku wyjsciowego
*/
bool CzyDozwolony(string przelacznik);

/*!
Opis funkcji:

Funkcja wywoluje funkcje konwersji typu int do string, nastepnie drukuje liste dwukierunkowa w postaci:
we1:we1val we2:we2val wyf:wyfval
Przykladowo:
1:0 6:0 3:0

parametry funkcji:

wezel *g - wskaznik na pierwszy element listy
we1 - wejscie pierwsze
we1val - wartosc wejscia pierwszego
we2 - wejscie drugie
we2val - wartosc wejscia drugiego
wyf - wyjscie
wyfval - wartosc wyjscia
*/
void DrukujUC(wezel *g);

/*!
Opis funkcji:

Funkcja usuwajaca liste w celu zwolnienia pamiecia.
Sprzata po sobie.

parametry funkcji:

wezel *&glowa - wskaznik na pierwszy element listy
*/
void UsunListeWezlow(wezel *&glowa);

/*!
Opis funkcji:

Funkcja tworzy nowy wezel i umieszcza w liscie na miejscu zaleznym od tego
ile elementow znajduje sie aktualnie w liscie.

parametry funkcji:

wezel *NowyW - wskaznik na nowo powstaly element listy
*/
void TworzWezel(string funkcja, int we1, int we1val, int we2, int we2val, int wyf, int wyfval);

/*!
Opis funkcji:

Funkcja konstruuje liste dwukierunkowa. Dla kazdego IN: i OUT: tworzy wezly w zaleznosci od tego ile maja wejsc i wyjsc.
W przypadku bramek dwuwejsciowych wystepuje dwa wejscia i jedno wyjscie.
Natomiast wyjatek stanowi bramka NEG, ktora posiada tylko jedno wejscie, drugie jest pomijane.
Poczatkowe wartosci elementu maja przypisana wartosc -1, czyli nieistniejaca wartosc logiczna (pusta).
W przypadku blednych danych zostaje podane informacje o bledzie.

parametry funkcji:

int ilParam - ilosc parametrow
char *param - wskaznik na parametr
*/
void WczytajWezel(string ln);

/*!
Opis funkcji:

Funkcja wczytuje uporzadkowany plik z danymi.
Porzadkuje plik z ukladem zastepujac wielokrotne wystapienia spacji i tabulacji pojedynczym znakiem bialym.
Inicjuje plik wynikow (otwiera pusty plik). W przypadku gdy nie udalo sie otworzyc pliku wejsciowego lub
wyjsciowego, zostaje wygenerowana informacja o bledzie.

parametry funkcji:

char* FNameUklad - sciezka dostepu i nazwa pliku ze schematem ukladu
char* FNameDane - sciezka dostepu i nazwa pliku z danymi
char* FNameWynik - sciezka dostepu i nazwa pliku wynikowego
*/

void TUC(char* FNameUklad, char *FNameDane, char *FNameWynik);

/*!
Opis funkcji:

Funkcja czysci liste przed zaladowaniem nowych danych do symulacji.
Czyli ustawia wartosci wejsc i wyjsc elementow na -1 (Nieistniejaca wartosc logiczna)

parametry funkcji:

wezel *g - wskaznik na pierwszy element listy
*/
void ZerowanieUC(void);

/*!
Opis funkcji:

Funkcja ma za zadanie wczytac plik z danymi i sprawdzic czy jego zawartosc jest poprawna.
Gdy jest wszystko jest poprawne, wowczas nastepuje szereg operacji zwiazanych z testowaniem ukladu.
Jednak gdy plik jest niepoprawny, wtedy zostaje podana informacja o bledzie.

parametry funkcji:

char *FNameDane - sciezka dostepu i nazwa pliku z danymi
*/
void WczytajDANE(char *FNameDane);


/*!
Opis funkcji:

Funkcja wprowadza dane do ukladu cyfrowego i przede wszystkim kontroluje ich ilosc i format.
Musza sie one zgadzac z wczytanym schematem w przeciwnym wypadku zostana podane informacje o bledach.

parametry funkcji:

wezel *g - wskaznik na element listy (wezel)
*/
void DANEdoUC(wezel *g, string ln);


/*!
Opis funkcji:

Funkcja przypisuje wejsciom i wyjsciom odpowiednia wartosc.
Zwraca wartosc true gdy wszystkie wezly IN maja nadana wartosc.
Wpisuje <Wartosc> <Wezla> wszystkich wezlow w ktorych wystepuje.

parametry funkcji:

int wartosc - wartosc ktora zostanie przypisana wejsciom, wyjsciom
*/
bool WczytajWartWezlaIN(int Wezel, int wartosc);

/*!
Opis funkcji:

Przeszukuje liste w celu znalezienia odpowiedniego wezla.

parametry funkcji:

wezel *&w - wskaznik na element listy
*/
wezel *SzukWezel(int nrw, wezel *&w);

/*!
Opis funkcji:

Jest to funkcja rekurencyjna, czyli wywo³uje sam¹ siebie.
Gdy wartosci wejsc wynosza -1, najpierw zostaje im przypisana odpowiednia wartosc.
Nastepnie zostaje obliczona wartosc na wyjsciu.

parametry funkcji:

wezel *glowa - wskaznik na pierwszy element listy
wezel *ogon	- wskaznik na ostatni element listy
*/
int ObliczWyFValWezela(int nrWezla);

/*!
Opis funkcji:

Funkcja przeprowadza symulacje ukladu cyfrowego w poszukiwaniu wartosci wezla wyjsciowego ukladu.
Przeszukuje cala liste do momentu znalezienia wezla wyjsciowego, wowczas oblicza jego wartosc.

parametry funkcji:

wezel *glowa - wskaznik na pierwszy element listy
wezel *ogon	- wskaznik na ostatni element listy
*/
void SymulacjaUC(wezel *g, wezel *o);

/*!
Opis funkcji:

Funkcja przeszukuje liste w celu pozyskania informacji o numerach wezlow wejsciowych, o numerze wezla wyjsciowego oraz o wartosciach jakie przyjmuja.
Zapisuje otrzymane wyniki do pliku wynikowego w przykladowej postaci: 
IN: 1:0 6:0 OUT: 3:0
IN: 1:0 6:1 OUT: 3:1
IN: 1:1 6:0 OUT: 3:1
IN: 1:1 6:1 OUT: 3:0

parametry funkcji:

wezel *g - wskaznik na pierwszy element listy
char *FNameWynik - sciezka dostepu i nazwa pliku wynikowego
*/
void WynikiDoPliku(wezel *g, char *FNameWynik);

#endif // !Unit2H

//---------------------------------------------------------------------------

 