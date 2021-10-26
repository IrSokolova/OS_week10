mkdir week01
FILEDIR='../week01/file.txt'
printf "Irina Sokolova" > $FILEDIR
link $FILEDIR '_ex2.txt' > 'ex2.txt'
INODENUM = $(ls -i $FILEDIR | awk '{print $1}')
find../ -inum $INODENUM >> 'ex2.txt'
find ../ -inum $INODENUM -exec rm {} \; >> 'ex2.txt'
