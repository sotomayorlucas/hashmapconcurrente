#ifndef LISTA_ATOMICA_HPP
#define LISTA_ATOMICA_HPP

#include <atomic>

template<typename T>
class ListaAtomica {
    // Variables privadas
    private:
        struct Nodo {
            Nodo(const T &val) : _valor(val), _siguiente(nullptr) {}

            T _valor;
            Nodo *_siguiente;
        };

        std::atomic<Nodo *> _cabeza;

    // Variables publicas
    public:
        ListaAtomica() : _cabeza(nullptr) {}

        // Destructor
        ~ListaAtomica() {
            Nodo *n, *t;
            n = _cabeza.load();
            while (n) {
                t = n;
                n = n->_siguiente;
                delete t;
            }
        }

        // Insertar un nodo al inicio de la lista, atomicamente.
        void insertar(const T &valor) {

            // Creamos un nuevo nodo. No pasa nada si varios threads lo hacen en simultáneo.
            Nodo *nuevoNodo = new Nodo(valor);

            // https://en.cppreference.com/w/cpp/atomic/atomic/exchange
            nuevoNodo->_siguiente = _cabeza.exchange(nuevoNodo);

            // La línea 41 hace esto:
            //     nuevoNodo->_siguiente = _cabeza;
            //     _cabeza = nuevoNodo;

        }

        // Retorna el valor del primer elemento
        T &cabeza() const {
            return _cabeza.load()->_valor;
        }

        // Retorna el valor del elemento i
        T &iesimo(unsigned int i) const {
            Nodo *n = _cabeza.load();
            for (unsigned int j = 0; j < i; j++) {
                n = n->_siguiente;
            }
            return n->_valor;
        }

        // Retorna la longitud de la lista
        unsigned int longitud() const {
            Nodo *n = _cabeza.load();
            unsigned int cant = 0;
            while (n != nullptr) {
                cant++;
                n = n->_siguiente;
            }
            return cant;
        }


        class Iterador {
             private:
                ListaAtomica *_lista;

                typename ListaAtomica::Nodo *_nodo_sig;

                Iterador(ListaAtomica<T> *lista, typename ListaAtomica<T>::Nodo *sig)
                    : _lista(lista), _nodo_sig(sig) {}

                friend typename ListaAtomica<T>::Iterador ListaAtomica<T>::crearIt();

             public:
                Iterador() : _lista(nullptr), _nodo_sig(nullptr) {}

                Iterador &operator=(const typename ListaAtomica::Iterador &otro) {
                    _lista = otro._lista;
                    _nodo_sig = otro._nodo_sig;
                    return *this;
                }

                bool haySiguiente() const {
                    return _nodo_sig != nullptr;
                }

                T &siguiente() {
                    return _nodo_sig->_valor;
                }

                void avanzar() {
                    _nodo_sig = _nodo_sig->_siguiente;
                }

                bool operator==(const typename ListaAtomica::Iterador &otro) const {
                    return _lista->_cabeza.load() == otro._lista->_cabeza.load()
                        && _nodo_sig == otro._nodo_sig;
                }
            };

        Iterador crearIt() {
            return Iterador(this, _cabeza);
        }
};

#endif /* LISTA_ATOMICA_HPP */
