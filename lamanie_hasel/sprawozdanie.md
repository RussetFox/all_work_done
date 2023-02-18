# Kacper Piejko, 259241

## Zadanie 1-2:
Zadanie zostalo wykonane przy pomocy funkcji napisanej w czesci glownej programu. Sprawdza ona czy plik z haslami podany jako <code>argv[1]</code> jest otwarty a nastepnie wczytuje kolejne hasla do tablicy <code>std::vector <std::string> passw</code>. Kolejna funkcja otwiera plik z nazwami uzytkownika i zahaszowanymi haslami  oraz umieszcza je w tablicy dynamicznej n x 2 <code>std::vector <std::vector<std::string>>hashPlusUser</code> gdzie n jest liczba uzytkownikow ktora zczytuje program z pliku podanego jako <code>argv[2]</code>. 
## Zadanie 3:
Do lamania hasel metoda slownikowa w tej czesci programu zostaly napisane 3 funkcje. Funkcja <code>void breakPasswordMethod1</code> uzywajaca funkcji kowersji hasla slownikowego do zahaszowanego hasla, a nastepnie porownujaca go z haslami danych uzytkownikow. Druga funkcja jest funkcja <code>void breakPasswordMethod2</code>. Dopisuje ona do podanego hasla slownikowego cyfry od 0 do 9 na poczatku lub na koncu hasla. Nastepnie zamienia takie haslo na wersje zahaszowana i porownuje z haslami uzytkownikow z tablicy uzytkownikow. Trzecia funkcja jest funkcja <code>void breakPasswordMethod1</code> ktora wybiera uzytkownika, nastepnie bierze haslo ze slownika, pozniej w petli dopisuje prefix od 00 do 99, a na koncu w petli dopisuje postfixy od 00 do 99. Po dopisaniu porownuje hasla z otrzymanym haslem uzytkownika.
Wszystkie funkcje w przypadku znalezienia hasla przechodza do nastepnego uzytkownika.

