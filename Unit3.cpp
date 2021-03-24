//---------------------------------------------------------------------------

#pragma hdrstop
#include "Unit3.h"
#include <sstream>
#include <functional>
#include <algorithm>

//---------------------------------------------------------------------------

int ileznk(string l, char znk)
{
  unsigned int j = 0;
  for (unsigned int i = 0; i < l.length(); i++)
    if (l[i] == znk) 
		j++;
  return j;
}

//---------------------------------------------------------------------------

bool testlinidadanych(string l)
{
  bool j = true;
  for (unsigned int i = 0; i < l.length(); i++)
    if (! (((l[i] >= '0') && (l[i] <= '9')) || l[i] == ':' || l[i] == ' ' || l[i] == '\t'))
        { j =false; break; }
  return j;
}

//---------------------------------------------------------------------------

bool czytajWW(string &l, int &wart)
{
  string liczba = "";
  while (l[0] == ' ') l.erase(0,1);
  while (l.length() && (l[0] >= '0') && (l[0] <= '9'))  // gdy l jest puste tez przerwij petle
    {
      liczba += l[0];
      l.erase(0,1); //usuniecie z zakresu od 0 do 1
    }
  wart = atoi(liczba.c_str());
  return liczba != "";
}

//---------------------------------------------------------------------------

int FnLog(string fun, int w1v, int w2v)
{
  // "AND", "NAND", "OR", "NOR", "XOR", "XNOR", "NEG", "IN:", "OUT:"
  unsigned int FnVal = 0;
  if ( fun.find("AND" ) == 0)  FnVal =   (w1v && w2v);
  else
    if ( fun.find("NAND") == 0)  FnVal = ! (w1v && w2v);
    else
      if ( fun.find("OR"  ) == 0)  FnVal =   (w1v || w2v);
      else
        if ( fun.find("NOR" ) == 0)  FnVal = ! (w1v || w2v);
        else
          if ( fun.find("XOR" ) == 0)  FnVal =   (w1v && !w2v) || (!w1v && w2v);
          else
            if ( fun.find("XNOR") == 0)  FnVal = ! (w1v && !w2v) || (!w1v && w2v);
              else
                if ( fun.find("NEG") == 0)  FnVal = ! w1v; // przyjmujemy ze w2v jest pomijana
                else FnVal = -1;  // error : nieznana funkcja
  return FnVal;
}

//---------------------------------------------------------------------------

string its(int n)                              // char intStr [35];
{                                              // for (int i = 1; i < 35; i++) intStr[i] = ' ';
  stringstream ss;                             // itoa(n, intStr, 10);
  ss << n;                                     // string str = "";
  string str = ss.str();                       // if (n == -1)
  if (n == -1)                                 //   str = "\ ";
	str = "\ ";   // znak SPACE                // else
  return str;                                  //   str = string(intStr);
}                                              // return str;

//---------------------------------------------------------------------------

