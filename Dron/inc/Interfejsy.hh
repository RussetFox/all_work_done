#ifndef INTERFEJSY_HH
#define INTERFEJSY_HH


#include "Dr3D_gnuplot_api.hh"

class Interfejs_rysowanie{
public:
    virtual void rysuj(drawNS::Draw3DAPI* rysownik) = 0;

};

class Interfejs_Dron{
public:
    virtual void przekrec_wirniki(drawNS::Draw3DAPI* rysownik)=0;
    virtual void lec_przod(double ile,drawNS::Draw3DAPI* rysownik)=0;
    virtual void lec_gora(double ile,drawNS::Draw3DAPI* rysownik)=0;
    virtual void obroc(double kat_stopnie,drawNS::Draw3DAPI* rysownik)=0;

};

class Interfejs_elem_kraj{
public:
    virtual bool czy_nad(Interfejs_Dron *D)=0;
    virtual bool czy_ladowac(Interfejs_Dron* D, double & wys)=0;
    virtual Wektor<3> get_srodek()=0;
};

#endif