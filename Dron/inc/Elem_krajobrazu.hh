#ifndef ELEMKRAJ_HH
#define ELEMKRAJ_HH

#include "Dron_i_jego_czesci.hh"
#include "Interfejsy.hh"
#include "Dr3D_gnuplot_api.hh"
#include <iostream>
#include <random>

uint random(uint min, uint max);



class Plaskowyz : public Uklad_W, public Interfejs_rysowanie, public Interfejs_elem_kraj {
    std::vector<Wektor<3>> wierzcholki_dol;
    double wysokosc;
public:
    void rysuj(drawNS::Draw3DAPI* rysownik) override;
    bool czy_nad(Interfejs_Dron *D) override{return true;};
    bool czy_ladowac(Interfejs_Dron *D, double & wys) override{return true;};
    Wektor<3> get_srodek() override {return srodek;};
    //konstruktor
    Plaskowyz(Wektor<3> Srodek, uint min, uint max):Uklad_W(Srodek,Macierz_Rot<3>(),nullptr),
    wysokosc(random(min,max)) {
    uint ilosc_wierzch(random(min,max));
    Macierz_Rot<3> rot(360/ilosc_wierzch,Wektor<3>({0,0,1}));
    Macierz_Rot<3> mac_pom;
    for(uint i=0; i<ilosc_wierzch; i++){
        Wektor<3> R({random(min,max),0,0});
        wierzcholki_dol.push_back(Srodek + mac_pom*R); 
        mac_pom=rot*mac_pom;
    }};
};

class Wzgorze : public Uklad_W, public Interfejs_rysowanie, public Interfejs_elem_kraj {
    std::vector<Wektor<3>> wierzcholki_dol;
    double wysokosc;
public:
    void rysuj(drawNS::Draw3DAPI* rysownik) override;
    bool czy_nad(Interfejs_Dron *D) override{return true;};
    bool czy_ladowac(Interfejs_Dron *D, double & wys) override{return true;};
    Wektor<3> get_srodek() override {return srodek;};
    //konstruktor
    Wzgorze(Wektor<3> Srodek, uint min, uint max):Uklad_W(Srodek,Macierz_Rot<3>(),nullptr),
    wysokosc(random(min,max)) {
    uint ilosc_wierzch(random(min,max));
    Macierz_Rot<3> rot(360/ilosc_wierzch,Wektor<3>({0,0,1}));
    Macierz_Rot<3> mac_pom;
    for(uint i=0; i<ilosc_wierzch; i++){
        Wektor<3> R({random(min,max),0,0});
        wierzcholki_dol.push_back(Srodek + mac_pom*R); 
        mac_pom=rot*mac_pom;
    }};
};

class Plaskowyz_prost : public Prostopadloscian, public Interfejs_elem_kraj {
public:
    void rysuj(drawNS::Draw3DAPI* rysownik)override;
    bool czy_nad(Interfejs_Dron *D) override{return true;};
    bool czy_ladowac(Interfejs_Dron *D, double & wys) override{return true;};
    Wektor<3> get_srodek() override {return srodek;};
    //konstruktor
    Plaskowyz_prost(Wektor<3> Srodek, uint min, uint max): 
    Prostopadloscian(Srodek,Macierz_Rot<3>(),nullptr,random(min,max),random(min,max),random(min,max)){};
};

#endif