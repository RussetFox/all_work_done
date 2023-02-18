DOW=$(date +%u)
##DOW=$(($DOW + 3)) ##do testowania dni 
if [ "$DOW" -lt 6 ]
then
    echo "Dzien pracowniczy"
else
    echo "Dzien wolny"
fi

