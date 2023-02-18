#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <array>
#include <cmath>

/*modeluje pojecie wektora*/

template <int ROZMIAR>
class Wektor {
  std::array<double,ROZMIAR> wsp;
  static uint ile_jest;
  static uint ile_stworzono;
public:
  Wektor<ROZMIAR> operator+(const Wektor<ROZMIAR> & skl2) const;
  Wektor<ROZMIAR> operator-(const Wektor<ROZMIAR> & skl2) const;
  Wektor<ROZMIAR> operator*(double skl2) const;
  double operator*(const Wektor<ROZMIAR> & skl2) const; //skalarne
  double dlugosc() const;
  // konstruktory:
  Wektor() { ile_jest++; ile_stworzono++;};
  Wektor(std::array<double,ROZMIAR> arg): wsp(arg) {ile_jest++; ile_stworzono++;};
  Wektor(const Wektor &W): wsp(W.wsp) {ile_jest++;ile_stworzono++;};
  //destruktor:
  ~Wektor(){ile_jest--;};
  //get:
  static uint get_ile_jest() {return ile_jest; };
  static uint get_ile_stworzono() {return ile_stworzono;};
  const double & operator[] (int i) const{
    if(i<0||i>ROZMIAR-1){std::cerr << "poza pamiecia" << std::endl; exit(1);}
    return wsp[i];}
  //set:
  double & operator[](int i){
    if(i<0||i>ROZMIAR-1){std::cerr << "poza pamiecia" << std::endl; exit(1);}
    return wsp[i];}
};

template <int ROZMIAR>
std::istream& operator >> (std::istream &strm, Wektor<ROZMIAR> &wek);

template <int ROZMIAR>
std::ostream& operator << (std::ostream &strm, const Wektor<ROZMIAR> &wek);

#endif
