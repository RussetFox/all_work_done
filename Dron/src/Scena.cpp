#include "Scena.hh"

void Scena::rysuj_wszystkie(drawNS::Draw3DAPI* rysownik){
  for (auto &x : Do_narysowania){
    x->rysuj(rysownik);
  }
  rysownik->redraw();
}

void Scena::animacja(double wys_przelotu, double kat_stopnie, double odleglolsc,drawNS::Draw3DAPI* rysownik){
  int l_klatek_pion(wys_przelotu/0.2);
  int l_klatek_poz(odleglolsc/0.2);
  int l_klatek_kat(kat_stopnie/4);

  for(int i=0; i<l_klatek_pion; i++){
    Aktualny_dron->lec_gora(wys_przelotu/l_klatek_pion, rysownik);
    Aktualny_dron->przekrec_wirniki(rysownik);
    rysownik->redraw();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  for(int i=0; i<l_klatek_kat; i++){
    Aktualny_dron->obroc(kat_stopnie/l_klatek_kat, rysownik);
    Aktualny_dron->przekrec_wirniki(rysownik);
    rysownik->redraw();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  for(int i=0; i<l_klatek_poz; i++){
    Aktualny_dron->lec_przod(odleglolsc/l_klatek_poz,rysownik);
    Aktualny_dron->przekrec_wirniki(rysownik);
    rysownik->redraw();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

//   for(int i=l_klatek_pion; i>0; i--){
//     dron->usun_rys(rysownik);
//     dron->lec_gora(-wys_przelotu/l_klatek_pion);
//     dron->przekrec_wirniki();
//     dron->rysuj(rysownik);
//     rysownik->redraw();
//     std::this_thread::sleep_for(std::chrono::milliseconds(200));
//   }

}

//bool sprawdz_kolizje(Interfejs_Dron*);

void Scena::dodaj_elem_kraj(){
  int wybor_elem;
  uint min, max;
  Wektor<3> Srodek;
  std::cout << "Jaki element chcesz dodać?" << std::endl;
  std::cout << "1 - Plaskowyz" << std::endl;
  std::cout << "2 - Wzgorze" << std::endl;
  std::cout << "3 - Plaskowyz prostopadloscienny " << std::endl;
  std::cout << "twoj wybor to:  ";
  std::cin >> wybor_elem;

  std::cout << "Podaj srodek (np: (1,2,3) )" << std::endl;
  std::cout << "srodek:  ";
  std::cin >> Srodek;

  std::cout << "Jakiej wielkosci ma byc element?" << std::endl;
  std::cout << "min:  ";
  std::cin >> min;
  std::cout << "max:  ";
  std::cin >> max;
  if(min<0 || max<0 || max<min){
    std::cerr << "Nie prawidlowa wartosc min lub max!" << std::endl;
    std::cin.setstate(std::ios::failbit);
  }

  switch(wybor_elem){void
    case 1: 
    Elementy_krajobrazu.push_back(std::shared_ptr<Interfejs_elem_kraj>(new Plaskowyz(Srodek, min, max))); break;
    case 2: 
    Elementy_krajobrazu.push_back(std::shared_ptr<Interfejs_elem_kraj>(new Wzgorze(Srodek, min, max))); break;
    case 3: 
    Elementy_krajobrazu.push_back(std::shared_ptr<Interfejs_elem_kraj>(new Plaskowyz_prost(Srodek, min, max))); break;
    default:
    std::cerr << "Nie ma takiego elementu do dodania!" << std::endl;
    std::cin.setstate(std::ios::failbit);
  }
  Do_narysowania.push_back(std::dynamic_pointer_cast<Interfejs_rysowanie>(Elementy_krajobrazu.back()));
}

void Scena::usun_elem_kraj(){
    uint wybor;
  std::cout << "Ktory element chcesz usunac? " << std::endl;
  pokaz_elem_kraj();
  std::cout << "Twoj wybor to: ";
  std::cin >> wybor;
  std::shared_ptr<Interfejs_elem_kraj>tmp = Elementy_krajobrazu[wybor];
  Elementy_krajobrazu.erase(std::remove(Elementy_krajobrazu.begin(), Elementy_krajobrazu.end(), tmp));
  Do_narysowania.erase(std::remove(Do_narysowania.begin(), Do_narysowania.end(),std::dynamic_pointer_cast<Interfejs_rysowanie>(tmp)));
}

void Scena::pokaz_elem_kraj(){
  std::cout << std::endl;
  std::cout << "Elementy krajobrazu na scenie: " << std::endl;
  for(uint i=0; i<Elementy_krajobrazu.size();i++){
    std::cout << "ID: " << i << " - srodek: " << Elementy_krajobrazu[i]->get_srodek() << std::endl;
  }
}

void Scena::dodaj_dron(){
  Wektor<3> Srodek;
  std::cout << "Podaj srodek (np: (1,2,3) )" << std::endl;
  std::cout << "srodek:  ";
  std::cin >> Srodek;

  Drony.push_back(std::shared_ptr<Interfejs_Dron>(new Dron(Srodek,Macierz_Rot<3>())));
  Do_narysowania.push_back(std::dynamic_pointer_cast<Interfejs_rysowanie>(Drony.back()));
}

void Scena::usun_dron(){
  uint wybor;
  std::cout << "Ktory dron chcesz usunac? " << std::endl;
  pokaz_drony();
  std::cout << "Twoj wybor to: ";
  std::cin >> wybor;
  std::shared_ptr<Interfejs_Dron>tmp = Drony[wybor];
  Drony.erase(std::remove(Drony.begin(), Drony.end(), tmp),Drony.end());
  Do_narysowania.erase(std::remove(Do_narysowania.begin(), Do_narysowania.end(),std::dynamic_pointer_cast<Interfejs_rysowanie>(tmp)),Do_narysowania.end());
}

void Scena::pokaz_drony(){
  std::cout << std::endl;
  std::cout << "Drony na scenie: " << std::endl;
  for(uint i=0; i<Drony.size();i++){
    std::cout << "ID: " << i << " - srodek: " << std::dynamic_pointer_cast<Interfejs_elem_kraj>(Drony[i])->get_srodek() << std::endl;
  }
}

void Scena::wybierz_dron(){
  uint wybor;
  std::cout << "Ktory dron wybierasz? " << std::endl;
  pokaz_drony();
  std::cout << "Twoj wybor to: ";
  std::cin >> wybor;
  Aktualny_dron = Drony[wybor];
}



