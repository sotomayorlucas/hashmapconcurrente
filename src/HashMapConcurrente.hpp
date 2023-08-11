#ifndef HMC_HPP
#define HMC_HPP

#include <atomic>
#include <string>
#include <vector>
#include <mutex>
#include <thread>

#include "ListaAtomica.hpp"

typedef std::pair<std::string, unsigned int> hashMapPair;

class HashMapConcurrente {
 
    // friend class thread;
 
 public:

    HashMapConcurrente();                            // Constructor
    HashMapConcurrente(const HashMapConcurrente &t); // Copiador
    static const unsigned int cantLetras = 26;


    void incrementar(std::string clave);
    std::vector<std::string> claves();
    unsigned int valor(std::string clave);

    hashMapPair maximo();
    hashMapPair maximoParalelo(unsigned int cantThreads);
   
 private:

    static unsigned int hashIndex(std::string clave);
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];
    
    // Usado por incrementar, maximo y maximoPorBucket
    std::mutex totalKeys[cantLetras];

    // Usadas para maximoParalelo
    hashMapPair maximoPorBucket(unsigned int);
    static void maximoPorThread(HashMapConcurrente *data, std::atomic<unsigned int> &sigIndex, hashMapPair &max);
};


#endif  /* HMC_HPP */
