#ifndef UKLADW_HH
#define UKLADW_HH

#include "Wektor.hh"
#include "Macierz.hh"
#include "Dr3D_gnuplot_api.hh"
#include "Interfejsy.hh"
#include <iostream>
#include <array>


class Uklad_W {
protected:
    Wektor<3> srodek;
    Macierz_Rot<3> orientacja;
    Uklad_W * rodzic;
public:
    void Przesuniecie(Wektor<3> Wek_przes) {srodek = srodek + Wek_przes;};
    void Obrot(Macierz_Rot<3> Mac_obr) {orientacja = Mac_obr * orientacja;};
    Uklad_W Przelicz_uklad_do_globalnego() const;
    Wektor<3> Przelicz_wierzcholek_do_globalnego(Wektor<3> wierzcholek) const;
    //konstruktor
    Uklad_W(Wektor<3> Sro, Macierz_Rot<3> Orient, Uklad_W * Rodz): 
    srodek(Sro), orientacja(Orient), rodzic(Rodz) {};
};

/*******************************************************************************/
class Prostopadloscian : public Interfejs_rysowanie, public Uklad_W {
protected:
    double szerokosc; //x
    double glebokosc; //y
    double wysokosc; //z
    int id;
public:
    void rysuj(drawNS::Draw3DAPI* rysownik) override;
    void usun_rys(drawNS::Draw3DAPI* rysownik) const;
    //konstruktor
    Prostopadloscian(Wektor<3> Sro, Macierz_Rot<3> Orient, Uklad_W * Rodz,
     double Szerokosc, double Glebokosc, double Wysokosc):
    Uklad_W(Sro, Orient, Rodz), szerokosc(Szerokosc), 
    glebokosc(Glebokosc), wysokosc(Wysokosc), id(-1) {};
};

/*******************************************************************************/
class Graniastoslup6: public Interfejs_rysowanie, public Uklad_W {
    double wysokosc;
    double bok_podst;
    int id;
public:
    void rysuj(drawNS::Draw3DAPI* rysownik) override;
    void usun_rys(drawNS::Draw3DAPI* rysownik) const;
    //konstruktor
    Graniastoslup6(Wektor<3> Sro, Macierz_Rot<3> Orient, Uklad_W * Rodz, double Wys, double Bok):
    Uklad_W(Sro, Orient, Rodz), wysokosc(Wys), bok_podst(Bok), id(-1) {};
};

/*******************************************************************************/
class Dron: public Interfejs_rysowanie, protected Uklad_W, public Interfejs_Dron, public Interfejs_elem_kraj {
    Prostopadloscian korpus;
    std::array<Graniastoslup6, 4> wierniki;
public:
    void rysuj(drawNS::Draw3DAPI* rysownik) override;
    void usun_rys(drawNS::Draw3DAPI* rysownik) const;
    void przekrec_wirniki(drawNS::Draw3DAPI* rysownik) override;
    void lec_przod(double ile,drawNS::Draw3DAPI* rysownik) override;
    void lec_gora(double ile,drawNS::Draw3DAPI* rysownik) override;
    void obroc(double kat_stopnie,drawNS::Draw3DAPI* rysownik)override;
    bool czy_nad(Interfejs_Dron *D)override{return true;};
    bool czy_ladowac(Interfejs_Dron* D, double & wys)override{return false;};
    Wektor<3> get_srodek() override {return srodek;};
    //konstruktor
    Dron(Wektor<3> Sro, Macierz_Rot<3> Orient):
    Uklad_W(Sro, Orient, nullptr),
    korpus(Wektor<3>({0,0,0}), Macierz_Rot<3>(), this, 2, 3, 1), 
    wierniki({Graniastoslup6(Wektor<3>({1,1.5,0.7}),Macierz_Rot<3>(),this,0.4,0.8),
    Graniastoslup6(Wektor<3>({1,-1.5,0.7}),Macierz_Rot<3>(),this,0.4,0.8),
    Graniastoslup6(Wektor<3>({-1,-1.5,0.7}),Macierz_Rot<3>(),this,0.4,0.8),
    Graniastoslup6(Wektor<3>({-1,1.5,0.7}),Macierz_Rot<3>(),this,0.4,0.8)}) {};

};

/*******************************************************************************/
class Powierzchnia : public Interfejs_rysowanie{
    double wysokosc;
public:
    void rysuj(drawNS::Draw3DAPI* rysownik) override;
    //konstruktor
    Powierzchnia(double Wys): wysokosc(Wys) {};
};
/*******************************************************************************/

drawNS::Point3D konwertuj(Wektor<3> W);

#endif