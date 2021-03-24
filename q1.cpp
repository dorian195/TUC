#include "stdafx.h"
#include <string>
#include <iostream>
#include <regex> 
#include <conio.h>
#include "Unit2.h"
using namespace std;

bool CzyDozwolony(string przelacznik)
{
  bool dobry = false;
  transform(przelacznik.begin(), przelacznik.end(), przelacznik.begin(), ::tolower);
  if (przelacznik.length() == 2 && przelacznik.find("-i") == 0) dobry = true;
  if (przelacznik.length() == 2 && przelacznik.find("-u") == 0) dobry = true;
  if (przelacznik.length() == 2 && przelacznik.find("-o") == 0) dobry = true;
  return dobry;
}

//---------------------------------------------------------------------------

void OpcjeProgramu(void)
{
  cout << "Przykladowe uruchomienie programu:" << endl;
  cout << "         tuc.exe <-u PlikUkladu> <-i PlikDanychWe> <-o PlikWynikow>"	<< endl;
  cout << "                   kolejnosc podawania parametrow -u, -i, -o jest dowolna," << endl;
  cout << "                   PlikUkladu  : plik wejsciowy z ukladem, "	<< endl;
  cout << "                   PlikDanychWe: plik wejsciowy ze stanami wejsc," << endl;
  cout << "                   PlikWynikow : plik wyjsciowy ze stanami wyjsc," << endl;
}

//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  string Linia = "";
  string linia = "";
  string nazw;
  string symk;
  string nrid;

  char  *file_name_uklad = NULL;     bool ukladOK = false;  //file_name_uklad = argv[2];
  char  *file_name_dane  = NULL;     bool daneOK  = false;  //file_name_dane  = argv[4];
  char  *file_name_wynik = NULL;     bool wynikOK = false;  //file_name_wynik = argv[6];
  char *przelacznik;

  przelacznik = NULL;
  if (argc == 7)
    for (int i = 1; i < argc; i++) // argv[0] pomijamy
      {
        if (i % 2 == 0) //parzysta czyli plik
          {
            if (strcmp(przelacznik, "-u") == 0)       { file_name_uklad = argv[i]; ukladOK = true; }
            if (strcmp(przelacznik, "-i") == 0)       { file_name_dane = argv[i];  daneOK  = true; }
            if (strcmp(przelacznik, "-o") == 0)       { file_name_wynik = argv[i]; wynikOK = true; }
          }
        else            //nieparzysta czyli przelacznik
          {
             przelacznik = argv[i];
             if (! CzyDozwolony(przelacznik))
               {
                  cout << "error: zostosowano niedozwolony przelacznik: " << przelacznik << endl << endl;
                  OpcjeProgramu();
                  break; // przerwij petle bo blad przelacznika
               }
          }
      }
  else
    {
      cout << "error: niewlasciwa liczba parametrow programu " << endl << endl;
      OpcjeProgramu();
    }
  if ( ukladOK &&  daneOK && wynikOK)
    TUC(file_name_uklad, file_name_dane, file_name_wynik);
  else
    {
      if (! ukladOK)  { cout << "error: brak pliku wejsciowego z ukladem cyfrowym." << endl << endl; }
      if (! daneOK )  { cout << "error: brak pliku danych dla ukladu cyfrowego."    << endl << endl; }
      if (! wynikOK)  { cout << "error: brak pliku wyjsciowego."                    << endl << endl; }
      OpcjeProgramu();
    }

  _CrtDumpMemoryLeaks();
  return 0;
}

//---------------------------------------------------------------------------

