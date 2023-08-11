#!/bin/bash

# Este script corre 150 veces ContarPalabras con distintos parámetros (1-1, 2-2, 4-4 y 8-8) con 8 archivos iguales
# Luego, guarda el output en /output/iguales

rm -rvf ./output/iguales/output-1-1-carga.txt
rm -rvf ./output/iguales/output-2-2-carga.txt
rm -rvf ./output/iguales/output-4-4-carga.txt
rm -rvf ./output/iguales/output-8-8-carga.txt
rm -rvf ./output/iguales/output-2-2-computo.txt
rm -rvf ./output/iguales/output-4-4-computo.txt
rm -rvf ./output/iguales/output-8-8-computo.txt
rm -rvf ./output/iguales/output-1-1-computo.txt


echo "Corriendo los tests 1-1"
for i in $(seq 1 150)
do
	par=$(../build/ContarPalabras 1 1 ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt)
	set -- $par
	echo $1 >> ./output/iguales/output-1-1-carga.txt
	echo $2 >> ./output/iguales/output-1-1-computo.txt
done 

echo "Corriendo los tests 2-2"
for i in $(seq 1 150)
do
	par=$(../build/ContarPalabras 2 2 ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt)
	set -- $par
	echo $1 >> ./output/iguales/output-2-2-carga.txt
	echo $2 >> ./output/iguales/output-2-2-computo.txt
done

echo "Corriendo los tests 4-4"
for i in $(seq 1 150)
do
	par=$(../build/ContarPalabras 4 4 ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt)
	set -- $par
	echo $1 >> ./output/iguales/output-4-4-carga.txt
	echo $2 >> ./output/iguales/output-4-4-computo.txt
done

echo "Corriendo los tests 8-8"
for i in $(seq 1 150)
do	
	par=$(../build/ContarPalabras 8 8 ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt ../data/words1.txt)
	set -- $par
	echo $1 >> ./output/iguales/output-8-8-carga.txt
	echo $2 >> ./output/iguales/output-8-8-computo.txt
done 