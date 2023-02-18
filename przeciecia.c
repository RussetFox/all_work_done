#include <stdio.h>

#define MAX 10//maksymalny pomiar
#define MIN -10//minimalny pomiar
#define HMAX 14//maksymalny puls
#define HMIN 8 //minimaly puls
#define PACZKA 99 /*pomimo zdefiniowania paczki danych w poleceniu jako 99 pomiarow
sa one dostarczane w 100 wierszach kazda paczka, dlatego definiujemy ja jako 99*/
#define WYZERUJ (poprz=licznik=czest=0)//pozwala na wyzerowanie potrzebnych parametrow


int main()
{
  float akt;
  float poprz=0;
  int licznik=0;
  int czest=0;
//ustawienie wartosci poczatkowych
  while(akt!=99)//petla wczytujaca liczbe do momentu pojawienia sie 99 na wejsciu
  {
    scanf ("%f", &akt);
    if(MIN<=akt && akt<=MAX && licznik!=PACZKA && akt!=0)/*dla liczby wczytanej nalezacej
    do przedzialu MIN MAX, nastepuja 2 mozliwosci*/
    {
      if(akt*poprz<0)//pomiedzy 2 liczbami doszlo do przeciecia zera
      {
      licznik++;
      czest++;
      poprz=akt;
      }
      else if (akt*poprz>=0)/*pomiedzy 2 liczbami nie doszlo do przeciecia 0,
      uwzgledniany jest warunek ==0, poniewaz startowa poprz=0*/
      {
        licznik++;
        poprz=akt;
      }
    }
    if ((MIN>akt | MAX<akt) && licznik!=PACZKA && akt!=99)/*dla liczby spoza przedzialu dodawana jest wartosc
    do licznika, okreslajacego paczke danych*/
    {
      licznik++;
    }
    if (akt==0 && licznik!=PACZKA)/*dla akt==0 nastepuje dodanie wartosci do licznika,
    warunek konieczny do uwzglednienia, w przypadku braku tej opcji generuje bledne wyniki*/
    {
      licznik++;
    }

    if((licznik==PACZKA) && czest<HMIN | czest>HMAX)/*po przeanalizowaniu calej paczki, dla
    niepoprawnego tetna generowany jest komunikat oraz zerowane sa odpowiednie parametry*/
    {
      printf("Puls spoza zakresu normy i wynosi: %i\n", czest);
      WYZERUJ;
    }

    else if(licznik==PACZKA && HMIN<=czest<=HMAX)/*zerowanie parametrow dla poprawnego
    tetna, bez komunikatu*/
    {
      WYZERUJ;
    }

  }
  return 0;
}

/*Autor: Kacper Piejko

Przebieg testow:
Testy zostaly przeprowadzone na 2 plikach tekstowych , dostepnych na stronie dr. inz. Roberta Muszynskiego,
zawierajace po 10 pelnych paczek danych oraz paczke zawierajaca akt=99, przy pomocy komend:
cut -f 2- -d ' ' nazwapliku| cut -f1 -d '.'| ./a.out, pozwalajacych na wyciecie z pliku danych czasowych,
oraz zamiane danych akt na liczby calkowite.

Test 1:
Do programu w segmencie zerowania parametrow dla poprawnego tetna zostala dopisana funkcja printf,
drukujaca poprawne tetno, pozwalajaca na okreslenie poprawnosci jego zliczania. Poza petla while zostal dodany
printf, informujacy o koncu pakietu danych dla akt=99 pokazujacy, czy petla przestaje dzialac dla akt=99.
W segmencie uwzgledniajacym wprowadzone liczby spoza przedzialu [-10, 10] dodana zostala funkcja printf,
odpowiedzialna za komunikat o liczbie spoza tego zakresu. Dopisano rowniez printf informujacy o akt=0 w tej sekcji

Oczekiwane wyniki: 11, komunikat o braku poprawnosci tetna wraz z liczba 5, 10, 12, 12, 12, 12, 13, komunikat o
braku poprawnosci tetna wraz z liczba 18, 11, komunikat o zakonczenu pakietu danych. Otrzymane wyniki powinny
byc takie same dla obu plikow, poniewaz po wlasnorecznym przeanalizowaniu danych obydwu plikow, mozna wnioskowac,
ze ilosc przeciec uznawana za niepoprawna w obu plikach wystepuje w 2 oraz 9 pakiecie danych. W pozostalych ilosc
przeciec zera jest rowna liczbom podanym wyzej. Dla testow pliku "dane wejsciowe 1" oczekiwane jest takze 11 komunikatow
o liczbie spoza przedzialu, 5 komunikatow o akt=0 w 3 pakiecie danych, a dla pliku "dane wejsciowe 2" 12 komunikatow o
liczbie spoza przedzialu oraz 6 komunikatow o akt=0 w 3 pakiecie danych . Poprawnosc tego testu pozwoli na stwierdzenie,
ze program dziala poprawnie.

Otrzymane wyniki: czesciowo zgode z oczekiwaniami. Zauwazono 11 komunikatow "Liczba spoza przedzialu" dla pliku "dane wejsciowe 1"
oraz 12 takich komunikatow dla pliku "dane wejsciowe 2". Pojawil sie takze komunikat o koncu paczki danych. Liczba
komunikatow o akt=0 zdecydowanie przekroczyla ilosc oczekiwanych, pojawily sie one takze w sekcjach gdzie 1>akt>0 lub -1<akt<0.

Wnioski: zastosowana komenda cut nie zamienia liczb na najwyzsza calkowita dla liczb dodatnich lub najnizsza calkowita
dla liczb ujemna, a jedynie "ucina". Ich czesc po przecinku. Moze to generowac bledy dla akt nalezacej do (-1,1) oraz
dla akt (-11,-10) oraz akt(10,11).

Test 2:
Z kodu w segmencie zerowania parametrow zostal usuniety printf, odpowiedzialny za wyswietlanie prawidlowych wartosci
tetna. Zlikwidowano funkcje printf, wyswietlajaca komunikat o danej spoza przedzialu [-10,10]. Usunieto takze printf
informujacy o koncu paczki danych oraz o akt=0.

Oczekiwane wyniki: komunikat o braku poprawnosci tetna wraz z liczba 5, kominikat o braku poprawnosci tetna wraz z
liczba 18. Jest to proba podobna do pierwszego testu, jednak tym razem uwzgledniany jest warunek podany w zadaniu,
mowiacy, ze maja wyswietlac sie jedynie komunikaty o niepoprawnym tetnie. Poprawnosc tego testu pozwoli na uznanie
programu, za dzialajacy czesciowo poprawnie i zgodnie z zalozeniami.

Otrzymane wyniki: komunikat o braku poprawnosci tetna wraz z liczba 5, komunikat o braku poprawnosci tetna wraz z liczba
18 dla obu plikow tekstowych. Otrzymane wyniki sa zgodne z oczekiwaniami.

Wnioski ogolne: W zwiazku ze specyfikacja uzytej komendy cut, program dziala poprawnie tylko, jezeli przeciecia nie znajduja
sie przy akt (-1,1) oraz jesli podane akt nie naleza do przedzialu (-11,-10) oraz (10,11). Dla wymienionych aktualnych uzycie
komendy cut przy uruchamianiu programu moze generowac bledy*/
