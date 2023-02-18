#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <thread>
#include "Wektor.hh"
#include "Macierz.hh"
#include "Dron_i_jego_czesci.hh"
#include "Elem_krajobrazu.hh"
#include "Scena.hh"



int main(){ 

drawNS::Draw3DAPI * rysownik = new drawNS::APIGnuPlot3D(-20,20,-20,20,-5,20,-1);
Scena nowa_scena;

nowa_scena.rysuj_wszystkie(rysownik);

nowa_scena.pokaz_elem_kraj();
nowa_scena.pokaz_drony();
// nowa_scena.dodaj_dron();
// nowa_scena.pokaz_drony();
// nowa_scena.rysuj_wszystkie(rysownik);
// nowa_scena.usun_dron();
// nowa_scena.pokaz_drony();
nowa_scena.animacja(10,45,10,rysownik);


}

