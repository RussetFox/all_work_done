#include "Dron_i_jego_czesci.hh"

Uklad_W Uklad_W::Przelicz_uklad_do_globalnego()const{
    Uklad_W w_globalnym(Wektor<3>({0,0,0}), Macierz_Rot<3>(), nullptr);
    Uklad_W tmp(*this);
    while(tmp.rodzic != nullptr){
        w_globalnym.srodek = (tmp.rodzic->orientacja * tmp.srodek) + tmp.rodzic->srodek;
        w_globalnym.orientacja = tmp.rodzic->orientacja * tmp.orientacja;
        tmp.srodek = w_globalnym.srodek;
        tmp.orientacja = w_globalnym.orientacja;
        tmp.rodzic = tmp.rodzic->rodzic;
    }
    if(tmp.rodzic == nullptr){
        return tmp;
    }
    return w_globalnym;
}


Wektor<3> Uklad_W::Przelicz_wierzcholek_do_globalnego(Wektor<3> wierzcholek_lok) const{
    Uklad_W globalny = Przelicz_uklad_do_globalnego();
    Wektor<3> wynik;
    wynik = (globalny.orientacja * wierzcholek_lok) + globalny.srodek;
    return wynik;
}
/*******************************************************************************/

void Prostopadloscian::rysuj(drawNS::Draw3DAPI* rysownik){
    Wektor<3> wierzcholek1, wierzcholek2,wierzcholek3,wierzcholek4,wierzcholek5,wierzcholek6,wierzcholek7,wierzcholek8;
  
    wierzcholek1 = Przelicz_wierzcholek_do_globalnego(Wektor<3>({0.5*szerokosc,0.5*glebokosc,0.5*wysokosc}));
    wierzcholek2 = Przelicz_wierzcholek_do_globalnego(Wektor<3>({0.5*szerokosc,-0.5*glebokosc,0.5*wysokosc}));
    wierzcholek3 = Przelicz_wierzcholek_do_globalnego(Wektor<3>({-0.5*szerokosc,-0.5*glebokosc,0.5*wysokosc}));
    wierzcholek4 = Przelicz_wierzcholek_do_globalnego(Wektor<3>({-0.5*szerokosc,0.5*glebokosc,0.5*wysokosc}));
    wierzcholek5 = Przelicz_wierzcholek_do_globalnego(Wektor<3>({0.5*szerokosc,0.5*glebokosc,-0.5*wysokosc}));
    wierzcholek6 = Przelicz_wierzcholek_do_globalnego(Wektor<3>({0.5*szerokosc,-0.5*glebokosc,-0.5*wysokosc}));
    wierzcholek7 = Przelicz_wierzcholek_do_globalnego(Wektor<3>({-0.5*szerokosc,-0.5*glebokosc,-0.5*wysokosc}));
    wierzcholek8 = Przelicz_wierzcholek_do_globalnego(Wektor<3>({-0.5*szerokosc,0.5*glebokosc,-0.5*wysokosc}));

    
    id = rysownik->draw_polyhedron(std::vector<std::vector<drawNS::Point3D> > {{
      konwertuj(wierzcholek1),konwertuj(wierzcholek2),
      konwertuj(wierzcholek3),konwertuj(wierzcholek4)
      },{
      konwertuj(wierzcholek5),konwertuj(wierzcholek6),
      konwertuj(wierzcholek7),konwertuj(wierzcholek8)
      }},"purple");

}

void Prostopadloscian::usun_rys(drawNS::Draw3DAPI* rysownik) const{
    rysownik->erase_shape(id);
}
/*******************************************************************************/

void Graniastoslup6::rysuj(drawNS::Draw3DAPI* rysownik){
    std::array<Wektor<3>,12> wierzcholki;
    double r = 0.5*bok_podst*sqrt(3);

    wierzcholki[0] = Przelicz_wierzcholek_do_globalnego(Wektor<3>({bok_podst,0,-0.5*wysokosc})); //bok_podst = R
    wierzcholki[1] = Przelicz_wierzcholek_do_globalnego(Wektor<3>({0.5*bok_podst,r,-0.5*wysokosc}));
    wierzcholki[2] = Przelicz_wierzcholek_do_globalnego(Wektor<3>({-0.5*bok_podst,r,-0.5*wysokosc}));
    wierzcholki[3] = Przelicz_wierzcholek_do_globalnego(Wektor<3>({-bok_podst,0,-0.5*wysokosc}));
    wierzcholki[4] = Przelicz_wierzcholek_do_globalnego(Wektor<3>({-0.5*bok_podst,-r,-0.5*wysokosc}));
    wierzcholki[5] = Przelicz_wierzcholek_do_globalnego(Wektor<3>({0.5*bok_podst,-r,-0.5*wysokosc}));
    
    for(int i=0;i<6;i++){
        wierzcholki[6+i] = wierzcholki[i]+Wektor<3>({0,0,wysokosc});
    }
    

    id = rysownik->draw_polyhedron(std::vector<std::vector<drawNS::Point3D> > {{
      konwertuj(wierzcholki[0]),konwertuj(wierzcholki[1]),
      konwertuj(wierzcholki[2]),konwertuj(wierzcholki[3]),
      konwertuj(wierzcholki[4]),konwertuj(wierzcholki[5]),
      },{
      konwertuj(wierzcholki[6]),konwertuj(wierzcholki[7]),
      konwertuj(wierzcholki[8]),konwertuj(wierzcholki[9]),
      konwertuj(wierzcholki[10]),konwertuj(wierzcholki[11]),
      }},"purple");
}


void Graniastoslup6::usun_rys(drawNS::Draw3DAPI* rysownik) const{
    rysownik->erase_shape(id);
}
/*******************************************************************************/

void Dron::rysuj(drawNS::Draw3DAPI* rysownik){
    korpus.rysuj(rysownik);
    wierniki[0].rysuj(rysownik);
    wierniki[1].rysuj(rysownik);
    wierniki[2].rysuj(rysownik);
    wierniki[3].rysuj(rysownik);
}

void Dron::usun_rys(drawNS::Draw3DAPI* rysownik) const{
    korpus.usun_rys(rysownik);
    wierniki[0].usun_rys(rysownik);
    wierniki[1].usun_rys(rysownik);
    wierniki[2].usun_rys(rysownik);
    wierniki[3].usun_rys(rysownik);

}
/*******************************************************************************/

void Dron::przekrec_wirniki(drawNS::Draw3DAPI* rysownik){
    Macierz_Rot<3> mac_obr(15,Wektor<3>({0,0,1}));
    wierniki[0].Obrot(mac_obr);
    wierniki[1].Obrot(mac_obr);
    wierniki[2].Obrot(mac_obr);
    wierniki[3].Obrot(mac_obr);
    rysuj(rysownik);
}
/*******************************************************************************/

void Dron::lec_przod(double ile,drawNS::Draw3DAPI* rysownik){ 
    srodek = srodek + orientacja*Wektor<3>({0,ile,0});
    rysuj(rysownik);

}

void Dron::lec_gora(double ile,drawNS::Draw3DAPI* rysownik){
    srodek = srodek + Wektor<3>({0,0,ile});
    rysuj(rysownik);
}

void Dron::obroc(double kat_stopnie,drawNS::Draw3DAPI* rysownik){
    Macierz_Rot<3> Mac_obr(kat_stopnie, Wektor<3>({0,0,1}));
    orientacja = Mac_obr*orientacja;
    rysuj(rysownik);
}
/*******************************************************************************/

void Powierzchnia::rysuj(drawNS::Draw3DAPI* rysownik){
    std::vector<std::vector<drawNS::Point3D>> tmp1;
    std::vector<drawNS::Point3D> tmp2;
    for(int i=-20; i<=20; i+=5){
        for (int j=-20; j<=20; j+=5){
            tmp2.push_back(drawNS::Point3D(i,j, wysokosc));
        }
        tmp1.push_back(tmp2);
        tmp2.clear();
    }
    rysownik->draw_surface(tmp1,"grey");
}

/*******************************************************************************/

  drawNS::Point3D konwertuj(Wektor<3> W){
      return drawNS::Point3D(W[0],W[1],W[2]);
}

