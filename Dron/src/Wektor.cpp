#include "Wektor.hh"

template <int ROZMIAR>
 uint Wektor<ROZMIAR>::ile_jest = 0;

template <int ROZMIAR>
 uint Wektor<ROZMIAR>::ile_stworzono = 0;


/************************************************************
 * Realizuje dodanie wektorow                               *
 * Argumenty:                                               *
 *      skl2 - drugi skladnik sumy         					*
 * Zwraca:													*
 *    	Sume dwoch wektorow     							*
 ***********************************************************/
template <int ROZMIAR>
Wektor<ROZMIAR> Wektor<ROZMIAR>::operator+(const Wektor<ROZMIAR> & skl2) const{
    Wektor<ROZMIAR> wektor;
    for (int i=0; i<ROZMIAR; i++){
        wektor.wsp[i] = wsp[i] + skl2.wsp[i];
    }
    return wektor;
}

/************************************************************
 * Realizuje odejmowanie wektorow                           *
 * Argumenty:                                               *
 *      skl2 - drugi skladnik roznicy     					*
 * Zwraca:													*
 *    	Roznice dwoch wektorow     							*
 ***********************************************************/
template <int ROZMIAR>
Wektor<ROZMIAR> Wektor<ROZMIAR>::operator-(const Wektor<ROZMIAR> & skl2) const{
    Wektor<ROZMIAR> wektor;
    for (int i=0; i<ROZMIAR; i++){
        wektor.wsp[i] = wsp[i] - skl2.wsp[i];
    }
    return wektor;
}

/************************************************************
 * Realizuje mnozenie wektora razy liczbe                   *
 * Argumenty:                                               *
 *      skl2 - liczba razy ktora mnozymy wektor 			*
 * Zwraca:													*
 *    	Iloczyn wektora i liczby  							*
 ***********************************************************/
template <int ROZMIAR>
Wektor<ROZMIAR> Wektor<ROZMIAR>::operator*(double skl2) const{
    Wektor<ROZMIAR> wektor;
    for (int i=0; i<ROZMIAR; i++){
        wektor.wsp[i] = wsp[i] * skl2;
    }
    return wektor;
}

/************************************************************
 * Realizuje iloczyn skalarny wektorow                      *
 * Argumenty:                                               *
 *      skl2 - drugi skladnik iloczynu     					*
 * Zwraca:													*
 *    	Iloczyn skalarny dwoch wektorow     				*
 ***********************************************************/
template <int ROZMIAR>
double Wektor<ROZMIAR>::operator*(const Wektor<ROZMIAR> & skl2) const{
    double wynik=0;
    for (int i=0; i<ROZMIAR; i++){
        wynik+=wsp[i]*skl2.wsp[i];
    }
    return wynik;
}

/************************************************************
 * Oblicza dlugosc wektora                                  *
 * Zwraca:													*
 *    	Dlugosc wektora         							*
 ***********************************************************/
template <int ROZMIAR>
double Wektor<ROZMIAR>::dlugosc() const{
    double suma_kwad=0;
    for (int i=0; i<ROZMIAR; i++){
        suma_kwad+=pow(wsp[i],2);
    }
    return (sqrt(suma_kwad));
}

/************************************************************
 * Wczytuje wektor ze strumienia wejsciowego        		*
 * Argumenty:												*
 *    strm - strumien										*
 *    wek - wczytywany wektor      							*
 * Zwraca:													*
 *    Strumien z wczytanym wektorem              			*
 ***********************************************************/
template <int ROZMIAR>
std::istream& operator >> (std::istream &strm, Wektor<ROZMIAR> &wek){
    char temp;
    strm >> temp;
    if(temp != '('){
		strm.setstate(std::ios::failbit);
	}
    for(int i=0; i<(ROZMIAR-1); i++){
        strm >> wek[i];
        strm >> temp;
        if(temp != ','){
		    strm.setstate(std::ios::failbit);
	    }
    }
    strm >> wek[ROZMIAR-1];
    strm >> temp;
    if(temp != ')'){
		strm.setstate(std::ios::failbit);
	}
    return strm;
}

/************************************************************
 * Wypisuje wektor na strumien wyjsciowy	           		*
 * Argumenty:												*
 *    strm - strumien										*
 *    wek - wyswietlany wektor      						*
 * Zwraca:													*
 *    Strumien z zapisem wektora w formie (1,2)   			*
 ***********************************************************/
template <int ROZMIAR>
std::ostream& operator << (std::ostream &strm, const Wektor<ROZMIAR> &wek){
    strm << "(";
    for(int i=0; i< ROZMIAR-1; i++){
        strm << wek[i] << ",";
    }
    strm << wek[ROZMIAR-1] << ")";
    return strm; 
}

template class Wektor<2>;
template class Wektor<3>;
template std::istream& operator >> (std::istream &strm, Wektor<2> &wek);
template std::istream& operator >> (std::istream &strm, Wektor<3> &wek);
template std::ostream& operator << (std::ostream &strm, const Wektor<2> &wek);
template std::ostream& operator << (std::ostream &strm, const Wektor<3> &wek);

