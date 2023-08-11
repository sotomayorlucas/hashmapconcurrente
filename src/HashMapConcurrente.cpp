#ifndef CHM_CPP
#define CHM_CPP
#define iteradorLista ListaAtomica<pair<std::basic_string<char>, unsigned int>>::Iterador

#include <iostream>
#include <fstream>
#include <pthread.h> // esto venia incluido...

#include "HashMapConcurrente.hpp"

enum{READ, WRITE};

using namespace std;

// Constructor
HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

// Devuelve el índice de clave
unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

// Obs: es bloqueante cuando cuando colisionan buckets
void HashMapConcurrente::incrementar(std::string clave) {

    // Tengo el bucket
    int index = hashIndex(clave);

    // El mutex esta libre, el primero que llega pasa y lo lockea, hace lo que tiene que hacer, y deja pasar al siguiente
    totalKeys[index].lock();

    // -- Agrego key/incremento significado --

    // Recorro la lista, y si encuentro mi clave la incremento
    for (iteradorLista reviso = tabla[index]->crearIt(); reviso.haySiguiente() ; reviso.avanzar()) {
        if (reviso.siguiente().first == clave){
            reviso.siguiente().second++;
            totalKeys[index].unlock();
            return;
        }
    }

    // Si no la encuentro, tengo que insertar {clave, 1}
    hashMapPair *nuevaClave = new hashMapPair{clave, 1};
    tabla[index]->insertar(*nuevaClave);

    // Termino de operar, libero el mutex
    totalKeys[index].unlock();

    return;
}



// Devuelve la lista de todas las claves
std::vector<std::string> HashMapConcurrente::claves() {

    vector<string> claves;
    for (unsigned int i = 0; i < cantLetras; ++i) {
        for (iteradorLista it = tabla[i]->crearIt(); it.haySiguiente(); it.avanzar()) {
            claves.push_back(it.siguiente().first);
        }
    }

    return claves;
}



// Dada una clave, te devuelve su valor
unsigned int HashMapConcurrente::valor(std::string clave) {
    int index = hashIndex(clave);
    for (iteradorLista it = tabla[index]->crearIt(); it.haySiguiente() ; it.avanzar()) {
        if (it.siguiente().first == clave){
            return it.siguiente().second;
        }
    }
    return 0;
}



// Dado un index, busca el máximo del bucket index
// (Accede a datos privados de la estructura)
hashMapPair HashMapConcurrente::maximoPorBucket(unsigned int index){

    hashMapPair max = hashMapPair{"a", 0};

    // Bloqueamos el bucket index
    totalKeys[index].lock();

    // Buscamos el máximo
    for (auto it = tabla[index]->crearIt(); it.haySiguiente(); it.avanzar() ) {
        if (it.siguiente().second > max.second) {
            max.first  = it.siguiente().first;
            max.second = it.siguiente().second;
        }
    }

    // Desbloqueamos el bucket index
    totalKeys[index].unlock();

    return max;
}



hashMapPair HashMapConcurrente::maximo() {

    hashMapPair max       = hashMapPair{"a",0};
    hashMapPair maxBucket = hashMapPair{"a", 0};

    // Por cada bucket, llamo a maximoPorBucket
    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        maxBucket = maximoPorBucket(index);
        if(maxBucket.second > max.second) max = maxBucket;
    }

    return max;
}



// Busca el siguiente index y llama a maximoPorBucket con ese index
// (No accede a datos privados de la estructura)
void HashMapConcurrente::maximoPorThread(HashMapConcurrente *data, atomic<unsigned int> &sigIndex, hashMapPair &max){

    unsigned int index = sigIndex.fetch_add(1);
    //    La linea anterior hace esto:   index = sigIndex;
    //                                   sigIndex++

    while(index < cantLetras) {

        // Buscamos el maximo del bucket index
        hashMapPair maxBucket = data->maximoPorBucket(index);

        if (max.second < maxBucket.second) max = maxBucket;
        
        // Buscamos el siguiente index
        index = sigIndex.fetch_add(1);
    }
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads) {

    hashMapPair max = hashMapPair{"a",0};
    
    // Acá voy a guardar el máximo de cada thread
    vector<hashMapPair> maxThread(cantThreads, hashMapPair{"a",0});
    
    // Variable que indica cuál es el siguiente index por recorrer (está disponible para todas las threads)
    atomic<unsigned int> sigIndex(0);

    vector<thread> threads;
    threads.reserve(cantThreads);

    // Llamamos a cantThreads threads para que corran maximoPorThread(this, &sigIndex, &maxThread[i])
    for(unsigned int i=0; i<cantThreads; i++){
        threads.emplace_back(maximoPorThread, this, ref(sigIndex), ref(maxThread[i]));
    }

    // Espero a que todos los threads terminen de operar
    for(auto &t : threads){
        t.join();
    }

    // Chequeo los máximos de cada thread
    for(unsigned int i=0; i<cantThreads; i++){
        if (maxThread[i].second > max.second) {
            max = maxThread[i];
        }
    }

    // Devuelvo el máximo de los máximos
    return max;
}

#endif
