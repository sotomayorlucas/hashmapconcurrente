#ifndef HMC_ARCHIVOS_HPP
#define HMC_ARCHIVOS_HPP

#include <ctype.h>
#include <vector>
#include <string>
#include <pthread.h>

#include "HashMapConcurrente.hpp"

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
);

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
);

void cargarArchivoThread(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> &filePaths,
    std::atomic<unsigned int> &sigIndex
);

#endif /* HMC_ARCHIVOS_HPP */
