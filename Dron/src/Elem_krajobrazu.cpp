#include "Elem_krajobrazu.hh"

uint random(uint min, uint max){
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<> distribution(min,max);
    return distribution(generator);
}


void Plaskowyz::rysuj(drawNS::Draw3DAPI *rysownik){
    std::vector<std::vector<drawNS::Point3D>> wierzch_wszystkie;
    std::vector<drawNS::Point3D> wierzch_dol_konw;
    std::vector<drawNS::Point3D> wierzch_gora_konw;

    for(uint i=0; i<wierzcholki_dol.size(); i++){
        wierzch_dol_konw.push_back(konwertuj(wierzcholki_dol[i]));
    }

    for(uint i=0; i<wierzcholki_dol.size(); i++){
        wierzch_gora_konw.push_back(konwertuj(wierzcholki_dol[i]+Wektor<3>({0,0,wysokosc})));
    }

    wierzch_wszystkie.push_back(wierzch_dol_konw);
    wierzch_wszystkie.push_back(wierzch_gora_konw);

    rysownik->draw_polyhedron(wierzch_wszystkie, "grey");

}

void Wzgorze::rysuj(drawNS::Draw3DAPI *rysownik){
    std::vector<std::vector<drawNS::Point3D>> wierzch_wszystkie;
    std::vector<drawNS::Point3D> wierzch_dol_konw;
    std::vector<drawNS::Point3D> wierzch_gora_konw;

    for(uint i=0; i<wierzcholki_dol.size(); i++){
        wierzch_dol_konw.push_back(konwertuj(wierzcholki_dol[i]));
    }

    for(uint i=0; i<wierzcholki_dol.size(); i++){
        wierzch_gora_konw.push_back(konwertuj(srodek+Wektor<3>({0,0,wysokosc})));
    }
   
    wierzch_wszystkie.push_back(wierzch_dol_konw);
    wierzch_wszystkie.push_back(wierzch_gora_konw);

    rysownik->draw_polyhedron(wierzch_wszystkie, "grey");

}


void Plaskowyz_prost::rysuj(drawNS::Draw3DAPI* rysownik){
    std::vector<std::vector<drawNS::Point3D>> wierzch_wszystkie;
    std::vector<drawNS::Point3D> wierzch_dol_konw;
    std::vector<drawNS::Point3D> wierzch_gora_konw;
    std::vector<Wektor<3>> wierzch_dol;

    
    wierzch_dol.push_back(Wektor<3>({0.5*szerokosc,0.5*glebokosc,0})+srodek);
    wierzch_dol.push_back(Wektor<3>({0.5*szerokosc,-0.5*glebokosc,0})+srodek);
    wierzch_dol.push_back(Wektor<3>({-0.5*szerokosc,-0.5*glebokosc,0})+srodek);
    wierzch_dol.push_back(Wektor<3>({-0.5*szerokosc,0.5*glebokosc,0})+srodek);

    for(int i=0; i<4; i++){
        wierzch_dol_konw.push_back(konwertuj(wierzch_dol[i]));
    }
    for(int i=0; i<4; i++){
        wierzch_gora_konw.push_back(konwertuj(wierzch_dol[i]+Wektor<3>({0,0,wysokosc})));
    }

    wierzch_wszystkie.push_back(wierzch_dol_konw);
    wierzch_wszystkie.push_back(wierzch_gora_konw);

    rysownik->draw_polyhedron(wierzch_wszystkie, "grey");

}