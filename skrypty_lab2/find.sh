mkdir $3

find ~ -type f -name "*.$1" -mtime "-$2" -exec cp {} $3 \;
tar cf $3.tar $3
rm -rf $3
