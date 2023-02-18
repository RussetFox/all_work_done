#ifndef MACIERZ_HH
#define MACIERZ_HH

#include"Wektor.hh"
#include <iostream>
#include <array>

/*definiuje macierz obrotu*/
template <int ROZMIAR> 
class Macierz_Rot {
  std::array<Wektor<ROZMIAR>,ROZMIAR> wiersz;
  public:
  Macierz_Rot<ROZMIAR> transpozycja()const;  
  Wektor<ROZMIAR> operator*(const Wektor<ROZMIAR> & skl2) const;
  Macierz_Rot<ROZMIAR> operator*(const Macierz_Rot<ROZMIAR> & skl2) const;
  //konstruktory:
  Macierz_Rot();//identycznosciowa
  Macierz_Rot(double kat_stopnie, Wektor<ROZMIAR> os);
  //get:
  const Wektor<ROZMIAR> & operator[](int i) const{
    if(i<0||i>ROZMIAR-1){ std::cerr << "poza pamiecia" << std::endl; exit(1);}
    return wiersz[i];};
};
template <int ROZMIAR> 
std::ostream& operator << (std::ostream &Strm, const Macierz_Rot<ROZMIAR> &Mac);

#endif
