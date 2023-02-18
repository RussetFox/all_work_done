# <b>Kacper Piejko, 259241 - Laboratorium 2</b>

## <b> 1. Cele laboratorium:

Poznanie narzędzi systemowych oraz podstawowych skryptów w systemie UNIX

## <b>2. Wykonane zadania:
### <b>2.1. Skrypt z funkcją date:
```
DOW=$(date +%u)
##DOW=$(($DOW + 2)) do testowania dni tygodnia
if [ "$DOW" -lt 6 ]
then
	echo "Dzien pracowniczy"
else
	echo "Dzien wolny"
fi
```
Skrypt zadziałał zgodnie z założeniami i w zależności od dnia tygodnia (lub testowanego dnia tygodnia) wyświetlał czy jest to dzień wolny czy pracowniczy

### <b>2.2. Skrypt liczący ilość plików w danym katalogu: </b>
```
ls -l $1 | grep ^- | wc -l
```
Skrypt zgodnie z założeniami zliczał ilość plików w obecnym katalogu, a dzięki dodaniu <code> $1 </code> reagował również na argument <code> -a </code> przy uruchamianiu skryptu, pozwalającego na wylistowanie również plików ukrytych

### <b>2.3. Wykorzystanie pętli for: </b>
```
for i in $@
do
    if [ -e $i ]
    then
    if [ -f $i ]
    then
    echo $i "- plik istnieje"
        elif [ -d $i ]
        then
		cd $i
		quantity_file_in_folder=$[$(ls -l -a | wc -l)-3]
		cd ..
		if [ $quantity_file_in_folder -eq 0 ]
			then
			echo $i "- katalog pusty"
		else
			echo $i "- jest katalogiem"
        	fi
        fi
    else
        echo $i "- nie istnieje"
        fi
done
```
Skrypt działał zgodnie z oczekiwaniami. Dzięki przejściu bezpośrednio do badanego folderu i użyciu wewnątrz fukckcji <code> ls </code> oraz <code> cat </code> po spełnieniu warunku istnienia danego folderu, można było określić czy folder ten jest pusty.

### <b> 2.4. </b> Funkcja find oraz tar: </b>
```
mkdir $3
find ~ -type f -name "*.$1" -mtime "-$2" -exec cp {} $3 \;
tar cf $3.tar $3
rm -rf $3
```
Skrypt działa poprawnie, dzięki odpowiednio argumentom <code> $1 $2 $3 </code> moża odpowiednio wyszukać konkretne rozszerzenia plików, czas ich stworzenia oraz nadać nazwę archiwum do którego mają zostać zapakowane. Funkcja <code> -exec cp </code> pozwala skopiować wszystkie pliki do tymczasowo utworzonego folderu, z którego później powstaje ich archiwum

### <b> 2.5. Skrypt wysyłający maila:
```
while read -r line
do
	mutt -s "Mail testowy" -- "$line" < trescmaila
done < zad5_plik_testowy
```
Skrypt działa poprawnie, korzystając z klienta mailowego jakim jest mutt. Pozwala on na wysłanie maila o tytule "Mail testowy" z treścią zawartą w pliku <code> trescmaila </code> do wszystkich adresów znajdujących się w pliku <code> zad5_plik_testowy </code>. Adresy te jednak muszą zostać wylistowane jeden pod drugim, a plik musi kończyć się pustą linią, w celu weryfikacji końca pliku.
