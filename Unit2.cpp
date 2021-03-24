//---------------------------------------------------------------------------

#pragma hdrstop
#include "Unit2.h"
#include "Unit3.h"
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>

//---------------------------------------------------------------------------

/*!
Wskaznik na lancuch znakow
*/
const char* in = "IN:";

/*!
ilosc wezlow
*/
int ilWezlow;

/*!
ilosc danych wejsciowych
*/
int ilDanychIN;

/*!
ilosc danych wyjsciowych
*/
int ilDanychOUT;

/*!
Wskaznik na lancuch znakow
*/
char *FileNameWynik;

/*!
wskaznik na pierwszy element listy
*/
wezel *uGlowa;

/*!
Wskaznik na ostatni element listy
*/
wezel *uOgon;

/*!
Wskaznik na akt element listy
*/
wezel *uAkt; 

//---------------------------------------------------------------------------


void DrukujUC( wezel *g )
{
  string we1, we1val, we2, we2val, wyf, wyfval;
  string funkcja;
  string spacje;
  while( g != NULL )
    {
      spacje = "     ";
      funkcja = spacje.insert(0, g->funkcja).substr(0, 6); //funkcja insert wstawia wartosc elementu na ktory wskazuje g->funkcja przed miejscem wskazanym przez 0. Substr-podstring, 0 oznacza pozycje pierwszego znaku ³añcucha, a 6 ilosc znakow
      we1 = its(g->we1);  we1val = its(g->we1val); //wywolanie funkcji its czyli zamiana typu int na string
      we2 = its(g->we2);  we2val = its(g->we2val);
      wyf = its(g->wyf);  wyfval = its(g->wyfval);
      cout << funkcja << "  " << we1 << ":" << we1val << "  " << we2 << ":" << we2val << "    " << wyf << ":" << wyfval << "  " << endl;
      g = g->nst;
    }
}

//---------------------------------------------------------------------------


void UsunListeWezlow( wezel *&glowa )
{
  wezel * pom = uGlowa;
  while( pom != NULL )
    {
      pom = uGlowa->nst;
      delete uGlowa;
      uGlowa = pom;
      if ( uGlowa != NULL )  // obsluga ostatniego wezla w liscie
        uGlowa->pop = NULL;
    }
}

//---------------------------------------------------------------------------

void TworzWezel( string funkcja, int we1, int we1val, int we2, int we2val, int wyf, int wyfval)
{
  wezel *NowyW = new wezel;
  ilWezlow++;
  NowyW->funkcja = funkcja;
  NowyW->we1 = we1;          NowyW->we1val = we1val;
  NowyW->we2 = we2,          NowyW->we2val = we2val;
  NowyW->wyf = wyf;          NowyW->wyfval = wyfval;
  if (ilWezlow == 1)
    {
      uGlowa = NowyW;
      uAkt    = NowyW;
      NowyW->pop = NULL;
    }
  else
   {
      uAkt->nst = NowyW;
      NowyW->pop = uAkt;
      uAkt = NowyW;
   }
  NowyW->nst = NULL;
}

//---------------------------------------------------------------------------

void WczytajWezel(string ln)
{
  int ilParam;
  char *param;
  string funkcja;
  int we1,  we1val,  we2,  we2val,  wyf,  wyfval;
  we1 = -1;  we1val = -1;
  we2 = -1;  we2val = -1;
  wyf = -1;  wyfval = -1;

  /*
  char *y = new char[ln.length() + 1];
  strcpy(y, ln.c_str());
  */

  if ( ln.find("IN:") == 0)
    {
	  //param =strtok(y, " ");
	  param = strtok(_strdup(ln.c_str())," "); //funkcja strtok zastepuje pierwszy znaleziony znak " " w podanym stringu czyli "ln" znakiem terminalnym - 0
      funkcja.append(param); // dodaje na koniec stringa "funkcja" ci¹g znakow "param"
      while(param != NULL)
        {
          param = strtok(NULL, " ");
          if (param != NULL)
            {
              TworzWezel(funkcja, we1, we1val, we2, we2val, atoi(param), wyfval);
              ilDanychIN++; //ilosc danych in
            }
        }
     }
  else
    if ( ln.find("OUT:") == 0)
      { //param =strtok(y, " ");
		param = strtok(_strdup(ln.c_str())," ");
        funkcja.append(param);
        while(param != NULL)
          {
            param = strtok(NULL, " ");
            if (param != NULL)
              {
                TworzWezel(funkcja, we1, we1val, we2, we2, atoi(param), wyfval);
                ilDanychOUT++; //ilosc danych out
              }
          }
       }
    else
      if ( ln.find("AND") == 0 || ln.find("NAND") == 0 || ln.find("OR") == 0 || ln.find("NOR") == 0 || ln.find("XOR") == 0 || ln.find("XNOR") == 0)
        { 
          ilParam = 1;
		  //param =strtok(y, " ");
          param = strtok(_strdup(ln.c_str())," ");
          funkcja.append(param);
          while(param != NULL)
            {
              param = strtok(NULL, " ");
              if (param != NULL)
                {
                  ilParam++;
                  if (ilParam == 2)  we1 = atoi(param);
                  if (ilParam == 3)  we2 = atoi(param);
                  if (ilParam == 4)  wyf = atoi(param);
                }
            }
          if (ilParam == 4 )
            TworzWezel(funkcja, we1, we1val, we2, we2val, wyf, wyfval);
          else
            {
              cout << "Error! za du¿o parametrow w lini:  !\n" ;
              cout << ln << endl;
            }
        }
      else
        if ( ln.find("NEG") == 0)
          { 
            ilParam = 1;
			//param =strtok(y, " ");
            param = strtok(_strdup(ln.c_str())," ");
            funkcja.append(param);
            while(param != NULL)
              {
                param = strtok(NULL, " ");
                if (param != NULL)
                {
                  ilParam++;
                  if (ilParam == 2)  we1 = atoi(param);
                  if (ilParam == 3)  wyf = atoi(param);
                }
              }
          if (ilParam == 3 )
            TworzWezel(funkcja, we1, we1val, we2, we2val, wyf, wyfval);
          else
            {
              cout << "Error! za duzo parametrow w lini:  !\n" ;
              cout << ln << endl;
            }
          }
        else
          {
            cout << "Error! niedozwolony operator logiczny w lini:  !\n    " ;
            cout << ln << endl;
          }
}

//---------------------------------------------------------------------------

void TUC(char* FNameUklad, char *FNameDane, char *FNameWynik)
{
  fstream fUklad;
  string LiniaIn;
  string linia;

  uGlowa   = NULL;
  ilWezlow = 0;
  ilDanychIN  = 0;
  FileNameWynik = FNameWynik;
  char *param;

  /*
  char *y = new char[LiniaIn.length() + 1];
  strcpy(y, LiniaIn.c_str());
  */

  ofstream fWynik;
  fWynik.open(FNameWynik, ios::out);
  if(! fWynik.good()) cout << "Error! Nie udalo otworzyc sie pliku do zapisania wynikow testu UC!" << endl;
  else fWynik.close();

  fUklad.open( FNameUklad, ios::in );
  if( fUklad.good())
    {
      while( !fUklad.eof() )
        {
          getline(fUklad, LiniaIn);
          transform( LiniaIn.begin(), LiniaIn.end(), LiniaIn.begin(),::toupper ); // replace_if( LiniaIn.begin(), LiniaIn.end(), ::isspace, ' ' );  -- Z zakresu [ LiniaIn.begin(),LiniaIn.end() ] zamienia ::isspace na spacje 
          linia.clear();
		  //param = strtok(y, "\ \t");
          param = strtok(_strdup(LiniaIn.c_str()),"\ \t");
          while(param != NULL)
            {
              linia.operator +=(param);
              param = strtok(NULL, "\ \t");
              if (param != NULL)
                linia.operator +=(' ');
            }
          if (! linia.empty())
             WczytajWezel(linia);
        }
      fUklad.close();
    }
  else
    cout << "Error! Nie udalo otworzyc sie pliku Wejsciowego.input!" << endl;

  WczytajDANE(FNameDane);
  UsunListeWezlow(uGlowa);
  uAkt = NULL;
}

//--------------------------------------------------------------------------

void ZerowanieUC(void)
{
  wezel *g;
  g = uGlowa;
  while( g != NULL )
    {
       g->wyfval = -1;
       g->we1val = -1;
       g->we2val = -1;
       g = g->nst;
    }
}

//--------------------------------------------------------------------------

void WczytajDANE(char *FNameDane)
{
  fstream fDane;
  string LiniaIn;
  string ln;
  char *param;

  /*
  char *y = new char[LiniaIn.length() + 1];
  strcpy(y, LiniaIn.c_str());
  */

  fDane.open( FNameDane, ios::in );
  if( fDane.good())
    {
      while( !fDane.eof() )
        {
          getline(fDane, LiniaIn); //wczytywanie tekstu
          ln.clear();
		  //param = strtok(y, "\ \t");
          param = strtok(_strdup(LiniaIn.c_str()),"\ \t");
          while(param != NULL)
            {
              ln.operator +=(param);
              param = strtok(NULL, "\ \t");
              if (param != NULL)
                ln.operator +=(' ');
            }
          if (! ln.empty())
            {
              ZerowanieUC();
              cout << "=====TUC:"<< endl;

              DrukujUC( uGlowa );
              DANEdoUC(uGlowa, ln);

              cout << endl << "=====UC po wprowadzeniu danych IN:" << ln << endl;
              DrukujUC( uGlowa );

              cout << endl << "=====symulacja UC:" << endl;

              SymulacjaUC(uGlowa, uOgon);
              cout << "-------- " << endl;

              DrukujUC( uGlowa );
              WynikiDoPliku(uGlowa, FileNameWynik);
              cout << endl << "==================koniec symulacji==========================" << endl;
            }
        }
      fDane.close();
    }
  else
    cout << "Error! Nie udalo otworzyc sie pliku Wejsciowego.input!" << endl;
}

//--------------------------------------------------------------------------

void DANEdoUC(wezel *g, string ln)
{
  int ww, vv;
  string ll = ln;
  int ilezmennych = 0;
  if (ileznk(ll, ':') == ilDanychIN && testlinidadanych(ll))
    if (ll.find(":") > 0 && ll.find(":") < ll.length())
      {
        while (ll.length() && ilezmennych < ilDanychIN)
          {
            if (! czytajWW(ll, ww)) 
				{ cout << "error: formatu danych! " << endl; break; }
            if (ll[0] != ':')       
				{ cout << "error: formatu danych! " << endl; break; }
            else                    
				ll.erase(0,1);
            if (! czytajWW(ll, vv)) 
				{ cout << "error: konwersji liczby! " << endl; break; }
            if (vv < 0 || vv > 1 )  
				{ cout << "error: zakresu wartosci wezla: <0; 1> " << endl; break; }

            ilezmennych++;

            if (! WczytajWartWezlaIN(ww, vv)) 
				{ cout << "error: nie znaleziono nr wezla w UC " << endl; break; }

          }
      }
    else { cout << "error: formatu danych! " << endl;  }
  else { cout << "error: ilosc Danych IN:! " << endl;  }
}
//--------------------------------------------------------------------------

bool WczytajWartWezlaIN(int Wezel, int Wartosc) // funkcja zwraca wartosc true gdy wszystkie wezly IN: maja nadana wartosc, dodatkowo wpisuje <Wartosc> <Wezla> wszystkich wezlow w ktorych wystepuje.
{
  bool ZnalazlemWezel = false;
  wezel *g;
  g = uGlowa;
  while( g != NULL )
    {
      if (strcmp(g->funkcja.c_str(), string("IN:").c_str()) == 0 && g->wyf == Wezel) // funkcja strcmp porownuje dwa lancuchy znakow
        {
          g->wyfval = Wartosc;
          ZnalazlemWezel = true;
        }
      else
        if (strcmp(g->funkcja.c_str(), string("NEG").c_str()) == 0 && g->we1 == Wezel)
          { 
            g->we1val = Wartosc;
            g->wyfval = ! Wartosc;
          }
        else
         {
           if (g->we1 == Wezel) g->we1val = Wartosc;
           if (g->we2 == Wezel) g->we2val = Wartosc;
           // ale nie jest to konieczne:  if (g->we1val > -1 && g->we2val > -1) g->wyfval = FnLog(g->funkcja, g->we1val, g->we2val);
         }
      g = g->nst;
    }
  return ZnalazlemWezel;
}

//--------------------------------------------------------------------------

wezel *SzukWezel(int nrw, wezel *&w)
{
  w = uGlowa;
  while(w != NULL )
    {
      if ( w->funkcja.find("AND") == 0 || w->funkcja.find("NAND") == 0 || w->funkcja.find("OR") == 0 || w->funkcja.find("NOR") == 0 || w->funkcja.find("XOR") == 0 || w->funkcja.find("XNOR") == 0 || w->funkcja.find("NEG") == 0)
        {
          if (w->wyf == nrw)
            { break; }
        }
      w = w->nst;
    }
  return w;
}

//--------------------------------------------------------------------------

int ObliczWyFValWezela(int nrWezla)  // funkcja REKURENCYJNA max ilosc zagniezdzen <= (IloscBramek-1)*2
{
  wezel *z;
  int zVal = -1;
  SzukWezel(nrWezla, z);
  z->funkcja;
  z->we1;
  z->we2;
  if (z != NULL)
    if (z->funkcja.find("NEG") != 0)  // NEG mozna realizowac NAND'em o zwartych wejsciach
      {
        if (z->we1val == -1) 
			zVal = z->we1val = ObliczWyFValWezela(z->we1);
        if 
			(z->we2val == -1) zVal = z->we2val = ObliczWyFValWezela(z->we2);
        if 
			(z->we1val != -1 && z->we2val != -1) zVal = z->wyfval = FnLog(z->funkcja, z->we1val, z->we2val);
      }
    else
      {
        if (z->we1val == -1) 
			zVal = z->we1val = ObliczWyFValWezela(z->we1);
        if (z->we1val != -1) 
			zVal = z->wyfval = FnLog(z->funkcja, z->we1val, z->we2val);
      }
  return zVal;
}

//--------------------------------------------------------------------------

void SymulacjaUC(wezel *glowa, wezel *ogon)
{
  int wyf, wyfval;
  wezel *g, *w;
  g = uGlowa;
  while (g != NULL)
    {
      if (g->funkcja.find("OUT:") == 0)
        {
          SzukWezel(g->wyf, w); //szuka wezla wyjsciowego idziemy od wyjscia uc do wejscia
          g->wyfval = ObliczWyFValWezela(g->wyf);
        }
      g = g->nst;
    }
}

//--------------------------------------------------------------------------

//lista to naturalny sposob opisania ukladu, ciag linii, 1 linia opisuje wejscie 2 wyjscie. 
//LiniaIN opisuje 2 wejscia wiec powstana 2 wezly, a jedno wyjscie.
//lista ma tyle elementow ile jest wezlow.
void WynikiDoPliku(wezel *g, char *FNameWynik)
{
  g = uGlowa;
  string LiniaIN = "IN: ";
  string LiniaOUT = "OUT: ";
  while (g != NULL)
    {
      if (g->funkcja.find("IN:") == 0)
        {
           LiniaIN += its(g->wyf) + ":" + its(g->wyfval) + " ";
        }
      if (g->funkcja.find("OUT") == 0)
        {
           LiniaOUT += its(g->wyf) + ":" + its(g->wyfval) + " ";
        }
      g = g->nst;
    }
 ofstream fWynik(FNameWynik, ios::app);
 if (fWynik.good())
   {
     fWynik << LiniaIN << "  " << LiniaOUT << endl;
     fWynik.close();
   }
 else cout << "Error! Nie udalo otworzyc sie pliku wynikowUC w trybie dopisywania!" << endl;
}

//--------------------------------------------------------------------------


