#ifndef SCENA_HH
#define SCENA_HH

#include "Dron_i_jego_czesci.hh"
#include "Elem_krajobrazu.hh"
#include "Interfejsy.hh"
#include <iostream>
#include <array>
#include <algorithm>

class Scena {
std::vector<std::shared_ptr<Interfejs_rysowanie>> Do_narysowania;
std::vector<std::shared_ptr<Interfejs_Dron>>Drony;
std::vector<std::shared_ptr<Interfejs_elem_kraj>>Elementy_krajobrazu;
std::shared_ptr<Interfejs_Dron> Aktualny_dron;
public:
void rysuj_wszystkie(drawNS::Draw3DAPI* rysownik);
void animacja(double wys_przelotu, double kat_stopnie, double odleglolsc,drawNS::Draw3DAPI* rysownik);

bool sprawdz_kolizje(Interfejs_Dron*);
void dodaj_elem_kraj();
void usun_elem_kraj();
void pokaz_elem_kraj();
void dodaj_dron();
void usun_dron();
void pokaz_drony();
void wybierz_dron();
//konstruktor
Scena(){
    Do_narysowania.push_back(std::shared_ptr<Interfejs_rysowanie>(new Powierzchnia(-0.5)));
    Elementy_krajobrazu.push_back(std::shared_ptr<Interfejs_elem_kraj>(new Plaskowyz(Wektor<3>({10,10,0}),3,9)));
    Do_narysowania.push_back(std::dynamic_pointer_cast<Interfejs_rysowanie>(Elementy_krajobrazu.back()));
    Elementy_krajobrazu.push_back(std::shared_ptr<Interf
    ejs_elem_kraj>(new Wzgorze(Wektor<3>({-10,10,0}),3,9)));
    Do_narysowania.push_back(std::dynamic_pointer_cast<Interfejs_rysowanie>(Elementy_krajobrazu.back()));
    Elementy_krajobrazu.push_back(std::shared_ptr<Interfejs_elem_kraj>(new Plaskowyz_prost(Wektor<3>({10,-10,0}),3,9)));
    Do_narysowania.push_back(std::dynamic_pointer_cast<Interfejs_rysowanie>(Elementy_krajobrazu.back()));
    Drony.push_back(std::shared_ptr<Interfejs_Dron>(new Dron(Wektor<3>({-15,-15,0}),Macierz_Rot<3>())));
    Do_narysowania.push_back(std::dynamic_pointer_cast<Interfejs_rysowanie>(Drony.back()));
    Drony.push_back(std::shared_ptr<Interfejs_Dron>(new Dron(Wektor<3>({-5,-5,0}),Macierz_Rot<3>())));
    Do_narysowania.push_back(std::dynamic_pointer_cast<Interfejs_rysowanie>(Drony.back()));
    Drony.push_back(std::shared_ptr<Interfejs_Dron>(new Dron(Wektor<3>({15,0,0}),Macierz_Rot<3>(90,Wektor<3>({0,0,1})))));
    Do_narysowania.push_back(std::dynamic_pointer_cast<Interfejs_rysowanie>(Drony.back()));
    Aktualny_dron = Drony.front();
    };
};

#endif