#include <iostream>
#include <time.h>

#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"

using namespace std; 

int main(int argc, char **argv) {
    if (argc < 4) {
        std::cout << "Error: faltan argumentos." << std::endl;
        std::cout << std::endl;
        std::cout << "Modo de uso: " << argv[0] << " <threads_lectura> <threads_maximo>" << std::endl;
        std::cout << "    " << "<archivo1> [<archivo2>...]" << std::endl;
        std::cout << std::endl;
        std::cout << "    threads_lectura: "
            << "Cantidad de threads a usar para leer archivos." << std::endl;
        std::cout << "    threads_maximo: "
            << "Cantidad de threads a usar para computar máximo." << std::endl;
        std::cout << "    archivo1, archivo2...: "
            << "Archivos a procesar." << std::endl;
        return 1;
    }
    int cantThreadsLectura = std::stoi(argv[1]);
    int cantThreadsMaximo = std::stoi(argv[2]);

    std::vector<std::string> filePaths = {};
    for (int i = 3; i < argc; i++) {
        filePaths.push_back(argv[i]);
    }

    
    HashMapConcurrente hashMap = HashMapConcurrente();
    
    /*
    cargarMultiplesArchivos(hashMap, cantThreadsLectura, filePaths);
    auto maximo = hashMap.maximoParalelo(cantThreadsMaximo);
    std::cout << maximo.first << " " << maximo.second << std::endl;
    */

    // ARREGLAR ANTES DE ENTREGAR
    // Acá agregamos código para cronometrar las funciones

    // https://stackoverflow.com/questions/2962785/c-using-clock-to-measure-time-in-multi-threaded-programs
    
    struct timespec start, end;
    double cpu_time_used;

    clock_gettime(CLOCK_MONOTONIC, &start);
    cargarMultiplesArchivos(hashMap, cantThreadsLectura, filePaths);
    clock_gettime(CLOCK_MONOTONIC, &end);

    cpu_time_used =  ((double) (end.tv_sec  - start.tv_sec));
    cpu_time_used += ((double) (end.tv_nsec - start.tv_nsec) / 1000000000.0);
    
    std::cout << cpu_time_used << std::endl; // segundos de carga

    clock_gettime(CLOCK_MONOTONIC, &start);
    auto maximo = hashMap.maximoParalelo(cantThreadsMaximo);
    clock_gettime(CLOCK_MONOTONIC, &end);

    cpu_time_used =  ((double) (end.tv_sec  - start.tv_sec));
    cpu_time_used += ((double) (end.tv_nsec - start.tv_nsec) / 1000000000.0);

    std::cout << cpu_time_used << std::endl; // segundos de computo
    std::cout << maximo.first << " " << maximo.second << std::endl;

    return 0;
}
