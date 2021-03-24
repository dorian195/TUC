/**
*@file Unit3.h
*@author Dorian Baranski
*@version 1.0
*@date 2019-01-18
*/

//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------

/*!
Opis funkcji:

Ponizsza funkcja sprawdza ilosc znakow w linii.

parametry funkcji:

string l - pojedyncza linia
char znk - pojedynczy znak
*/
int ileznk(string l, char znk);

/*!
Opis funkcji:

Funkcja sprawdza poprawnosc znakow wystepujacych w linii.
Dozwolone sa tylko liczby 0-9, : , znak bialy oraz tabulacja.

parametry funkcji:

string l - pojedyncza linia
*/
bool testlinidadanych(string l);

/*!
Opis funkcji:

Funkcja usuwa ewentualne spacje wiod¹ce. Dokonuje konwersji z lancucha znakow do wartosci calkowitych int.

parametry funkcji:

string &l - referencja do linii l
*/
bool czytajWW(string &l, int &wart);

/*!
Opis funkcji:

Jest to funkcja logiczna, ktora oblicza wartosci wyjsciowe w zaleznosci od wykorzystywanych bramek.
Bramki "AND", "NAND", "OR", "NOR", "XOR", "XNOR" sa dwuwejsciowego, dlatego do obliczenia wartosci wyjsciowej
potrzebne sa wartosci wejscia pierwszego i drugiego.
Natomiast bramka "NEG" wykorzystuje tylko jedno wejscie, drugie jest bez znaczenia, czyli zostaje pominiete.
W przypadku nie rozpoznania bramki, funkcja logiczna przyjmuje wartosc -1, czyli wartosc 'nieistniejaca'

parametry funkcji:

int w1v - wartosc pierwszego wejscia
int w2v - wartosc drugiego wejscia
*/
int FnLog(string fun, int w1v, int w2v);

/*!
Opis funkcji:

Funkcja konwertuje typ integer do typu string

parametry funkcji:

string &l - referencja do linii l
*/
string its(int n);

#endif
// !Unit3H

//--------------------------------------------------------------------------- 
