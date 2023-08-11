#!/bin/bash

# Este script corre 150 veces ContarPalabras con distintos parámetros (1-1, 2-2, 4-4 y 8-8) con 8 archivos distintos
# Luego, guarda el output en /output/distintos

rm -rvf ./output/distintos/output-1-1-carga.txt
rm -rvf ./output/distintos/output-2-2-carga.txt
rm -rvf ./output/distintos/output-4-4-carga.txt
rm -rvf ./output/distintos/output-8-8-carga.txt
rm -rvf ./output/distintos/output-2-2-computo.txt
rm -rvf ./output/distintos/output-4-4-computo.txt
rm -rvf ./output/distintos/output-8-8-computo.txt
rm -rvf ./output/distintos/output-1-1-computo.txt

echo "Corriendo los tests 1-1"
for i in $(seq 1 150)
do
	par=$(../build/ContarPalabras 1 1 ../data/words1.txt ../data/words2.txt ../data/words3.txt ../data/words4.txt ../data/words5.txt ../data/words6.txt ../data/words7.txt ../data/words8.txt ../data/words9.txt ../data/1words0.txt)
	set -- $par
	echo $1 >> ./output/distintos/output-1-1-carga.txt
	echo $2 >> ./output/distintos/output-1-1-computo.txt
done 

echo "Corriendo los tests 2-2"
for i in $(seq 1 150)
done
	par=$(../build/ContarPalabras 2 2 ../data/words1.txt ../data/words2.txt ../data/words3.txt ../data/words4.txt ../data/words5.txt ../data/words6.txt ../data/words7.txt ../data/words8.txt ../data/words9.txt ../data/1words0.txt)
	set -- $par
	echo $1 >> ./output/distintos/output-2-2-carga.txt
	echo $2 >> ./output/distintos/output-2-2-computo.txt
done

echo "Corriendo los tests 4-4"
for i in $(seq 1 150)
do
	par=$(../build/ContarPalabras 4 4 ../data/words1.txt ../data/words2.txt ../data/words3.txt ../data/words4.txt ../data/words5.txt ../data/words6.txt ../data/words7.txt ../data/words8.txt ../data/words9.txt ../data/1words0.txt)
	set -- $par
	echo $1 >> ./output/distintos/output-4-4-carga.txt
	echo $2 >> ./output/distintos/output-4-4-computo.txt
done

echo "Corriendo los tests 8-8"
for i in $(seq 1 150)
do
	par=$(../build/ContarPalabras 8 8 ../data/words1.txt ../data/words2.txt ../data/words3.txt ../data/words4.txt ../data/words5.txt ../data/words6.txt ../data/words7.txt ../data/words8.txt ../data/words9.txt ../data/1words0.txt)
	set -- $par
	echo $1 >> ./output/distintos/output-8-8-carga.txt
	echo $2 >> ./output/distintos/output-8-8-computo.txt
done 