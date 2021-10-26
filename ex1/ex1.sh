nano _ex1.txt
ls -i
ln _ex1.txt _ex1_1.txt
ln _ex1.txt _ex1_2.txt
ls -li
ls -i _ex1.txt | awk '{print $1}' >> output.txt
ls -i _ex1_1.txt | awk '{print $1}' >> output.txt
ls -i _ex1_2.txt | awk '{print $1}' >> output.txt
cat output.txt
