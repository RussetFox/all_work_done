#include "Macierz.hh"

/************************************************************
 * Realizuje transpozycje macierzy                          *
 * Zwraca:													*
 *    	Transponowana macierz   							*
 ***********************************************************/
template <int ROZMIAR>
Macierz_Rot<ROZMIAR> Macierz_Rot<ROZMIAR>::transpozycja()const{
    Macierz_Rot<ROZMIAR> mac_wynik;
    for(int i=0; i<ROZMIAR; i++){
        for(int j=0; j<ROZMIAR; j++){
            mac_wynik.wiersz[i][j]=wiersz[j][i];
        }
    }
    return mac_wynik;
}

/************************************************************
 * Realizuje mnozenie macierzy razy wektor (nie na odwrot)  *
 * Argumenty:                                               *
 *      skl2 - wektor razy ktory mnozymy macierz			*
 * Zwraca:													*
 *    	Wynik mnozenia macierzy razy wektor (tez wektor)    *
 ***********************************************************/
template<int ROZMIAR>
Wektor<ROZMIAR> Macierz_Rot<ROZMIAR>::operator*(const Wektor<ROZMIAR> & skl2) const{
    Wektor<ROZMIAR> wek_wynik;
    for(int i=0; i<ROZMIAR; i++){
        wek_wynik[i] = wiersz[i]*skl2; //iloczyn skalarny wektora z macierzy i obracanego wektora
    }
    return wek_wynik;
}

/************************************************************
 * Realizuje mnozenie dwoch macierzy                        *
 * Argumenty:                                               *
 *      skl2 - druga macierz             					*
 * Zwraca:													*
 *    	Wynik mnozenia dwuch macierzy (tez macierz)			*
 ***********************************************************/
template<int ROZMIAR>
Macierz_Rot<ROZMIAR> Macierz_Rot<ROZMIAR>::operator*(const Macierz_Rot<ROZMIAR> & skl2) const{
    Macierz_Rot<ROZMIAR> mac_wynik;
    Macierz_Rot<ROZMIAR> skl2_transp;
    skl2_transp = skl2.transpozycja();
    for(int i=0; i<ROZMIAR; i++){
        for(int j=0; j<ROZMIAR; j++){
        // iloczyn skalarny wektorow (wierszy z macierzy1 i transponowanej macierzy2)
            mac_wynik.wiersz[i][j]=wiersz[i]*skl2_transp.wiersz[j]; 
        }
    }
    return mac_wynik;
}

/************************************************************
 * Konstruktor klasy Macierz_Rot,                            *
 * ustawia macierz domyslnie jako jednostkowa               *
 ***********************************************************/
template<int ROZMIAR>
Macierz_Rot<ROZMIAR>::Macierz_Rot(){
    for(int i=0; i<ROZMIAR; i++){ 
        for (int j=0; j<ROZMIAR; j++){
            if(i==j){ 
                wiersz[i][j]=1;
            }else{
                wiersz[i][j]=0;
            }
        }
    }
}

/*****************************************************************
 * Konstruktor klasy Macierz_Rot ze specjalizacjami szablonu     *
 * ustawia wartosc macierzy obrotu zgodnie z podanym katem i osia*
 ****************************************************************/
template<int ROZMIAR>
Macierz_Rot<ROZMIAR>::Macierz_Rot(double kat_stopnie, Wektor<ROZMIAR> os){
            std::cerr << "Obslugiwane tylko macierze obrotu 2D i 3D" << std::endl;
}
template<>
Macierz_Rot<2>::Macierz_Rot(double kat_stopnie, Wektor<2> os ){
    double kat_radiany = (kat_stopnie*M_PI)/180;
    wiersz[0][0] = cos(kat_radiany);
    wiersz[0][1] = -sin(kat_radiany);
    wiersz[1][0] = -wiersz[0][1];
    wiersz[1][1] = wiersz[0][0];
    wiersz[0][0] = cos(kat_radiany);
}

template<>
Macierz_Rot<3>::Macierz_Rot(double kat_stopnie, Wektor<3> os){
    if(os.dlugosc()!=1){
        //std::cout<< os.dlugosc();
        std::cerr << "Wektor osi musi być jednostkowy!" << std::endl;
        exit(1);
    }
    double kat_radiany = (kat_stopnie*M_PI)/180;
    wiersz[0][0] = cos(kat_radiany) + pow(os[0],2)*(1-cos(kat_radiany));
    wiersz[0][1] = os[0]*os[1]*(1-cos(kat_radiany))-os[2]*sin(kat_radiany);
    wiersz[0][2] = os[0]*os[2]*(1-cos(kat_radiany))+os[1]*sin(kat_radiany);

    wiersz[1][0] = os[0]*os[1]*(1-cos(kat_radiany))+os[2]*sin(kat_radiany);
    wiersz[1][1] = cos(kat_radiany) + pow(os[1],2)*(1-cos(kat_radiany));
    wiersz[1][2] = os[1]*os[2]*(1-cos(kat_radiany))-os[0]*sin(kat_radiany);

    wiersz[2][0] = os[0]*os[2]*(1-cos(kat_radiany))-os[1]*sin(kat_radiany);
    wiersz[2][1] = os[1]*os[2]*(1-cos(kat_radiany))+os[0]*sin(kat_radiany);
    wiersz[2][2] = cos(kat_radiany) + pow(os[2],2)*(1-cos(kat_radiany));
}

/************************************************************
 * Wypisuje macierz na strumien wyjsciowy	           		*
 * Argumenty:												*
 *    strm - strumien										*
 *    mac - wyswietlana macierz      						*
 * Zwraca:													*
 *    Strumien z zapisem macierzy                           *
 ***********************************************************/
template<int ROZMIAR>
std::ostream& operator << (std::ostream &strm, const Macierz_Rot<ROZMIAR> &mac){
    for(int i=0; i<ROZMIAR; i++){
        for(int j=0; j<ROZMIAR; j++){
            strm << mac[i][j] << "      ";
        }
    strm << std::endl;
    }
    return strm;
}

template class Macierz_Rot<2>;
template class Macierz_Rot<3>;
template std::ostream& operator << (std::ostream &Strm, const Macierz_Rot<2> &Mac);
template std::ostream& operator << (std::ostream &Strm, const Macierz_Rot<3> &Mac);
