#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <atomic> // Para el ej4
#include <thread> // Para el ej4

#include "CargarArchivos.hpp"

using namespace std;

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Completar (Ejercicio 4)
        cant++;
        hashMap.incrementar(palabraActual);
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

void cargarArchivoThread(HashMapConcurrente &hashMap, unsigned int cantThreads, vector<string> &filePaths, atomic<unsigned int> &sigIndex){
    
    unsigned int index = sigIndex.fetch_add(1);

    while(index < filePaths.size()){
        string path = filePaths[index];
        cargarArchivo(hashMap, path);
        index = sigIndex.fetch_add(1);
    }
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {

    // Completar (Ejercicio 4)

    atomic<unsigned int> sigIndex(0);
    vector<thread> threads;
    threads.reserve(cantThreads);

    for(unsigned int i=0; i<cantThreads; i++){
        threads.emplace_back(cargarArchivoThread, ref(hashMap), cantThreads, ref(filePaths), ref(sigIndex));
    }

    for(auto &t : threads) t.join();
}

#endif
