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
