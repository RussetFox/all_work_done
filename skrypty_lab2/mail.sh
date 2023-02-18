
while read -r line
do
	mutt -s "Mail testowy" -- "$line" < trescmaila
done < zad5_plik_testowy
##test
