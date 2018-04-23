/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
 * Lista 
 * Implementacion de Lista Doblemente Enlazada con Templates
 * Version: 1.0
 * Autor: Mariano Simone (marianosimone+7541@gmail.com)
 *        Mariano Tugnarelli
 **/

#ifndef __LISTA_DOBLEMENTE_ENLAZADA_H__
#define __LISTA_DOBLEMENTE_ENLAZADA_H__

#include "Nodo.h"
#include "IteradorLista.h"
#include "Comparador.h"

/**
 * Una Lista es una colección de elementos ordenados secuencialmente. 
 * Los elementos contenidos en una Lista pueden ser recorridos a través
 * del uso de Iteradores, entidad que encapsula el estado y comportamiento
 * de un instancia de recorrido sobre la estructura de datos.
 * 
 */
template<class T> class Lista {

    private:

        /* Puntero al primer elemento de la lista */
        Nodo<T>* primero;
        
        /* Puntero al último elemento de la lista */
        Nodo<T>* ultimo;

        /* Comparador que utiliza para ordenar los elementos */
        Comparador<T>* comparador;
        
    public:
        /**
         * pre : ninguna.
         * post: instancia vacia. Ordena los elementos de acuerdo al orden de 
         *       inserción. 
         *        
         */
        Lista() {
            this->setPrimero(NULL);
            this->setUltimo(NULL);
            
            /* utiliza el comparador por defecto */
            this->setComparador(new ComparadorConstante<T>());
        }
        
        /**
         * pre : el comparador no es nulo.
         * post: instancia vacia. Ordena los elementos de acuerdo a comparador.
         *  
         */
        Lista(Comparador<T>* comparador) {
         
            this->setPrimero(NULL);
            this->setUltimo(NULL);
            this->setComparador(comparador);
        }

        /**
         * pre : ninguna.
         * post: libera los recursos asociados a la instancia.
         * 
         */
        virtual ~Lista() {
            
            IteradorLista<T> iterador = this->iterador();
            while (iterador.tieneSiguiente()) {

                iterador.remover();
            }
            
            delete this->getComparador();
        }

        /*
         * Determina si la lista esta vacia o no
         */
        bool estaVacia() {

            return (this->getPrimero() == NULL);
        }

        /**
         * pre : ninguna.
         * post: devuelve la cantidad de elementos que tiene la lista.
         * 
         */
        unsigned int tamanio() {
            
            unsigned int elementos = 0;
            IteradorLista<T> unIterador = this->iterador();
            
            while (unIterador.tieneSiguiente()) {
                elementos++;
                unIterador.siguiente();
            }
            return elementos;
        }

        /**
         * pre : ninguna.
         * post: agrega el dato a la estructura de lista, estructurando la
         *       secuencia de elementos de acuerdo al comparador asociado.
         * 
         */
        void agregar(T dato) {
            
            bool insertar = false;
            Comparador<T>* comparador = this->getComparador();
            
            /* itera por todos los elemento buscando el lugar para hacer
             * la inserción */
            IteradorLista<T> iterador = this->iterador();
            while (iterador.tieneSiguiente() && ! insertar) {

                if (comparador->comparar(iterador.get(), dato) == MAYOR) {
                    
                    /* lo inserta antes del elemento */
                    insertar = true;

                } else {
                
                    /* pasa al siguiente elemento */
                    iterador.siguiente();
                }
            }
            
            /* lo inserta en donde haya quedado el iterador */
            iterador.insertar(dato);
        }

        /**
         * pre : ninguna.
         * post: devuelve una nueva instancia de iterador localizado en el 
         *       comienzo de la lista.
         *  
         */ 
        IteradorLista<T> iterador() {

            IteradorLista<T> unIterador(this);
            return unIterador;
        }

        /**
         * pre : ninguna.
         * post: busca el dato entre los elementos de la lista, utilizando
         *       el comparador asignado. Devuelve un Iterador localizado
         *       en el elemento si lo encuentra o en el fin de la lista
         *       si no lo encuentra.  
         *  
         */
        IteradorLista<T> buscar(T dato) {
            
            bool encontrado = false;
            Comparador<T>* comparador = this->getComparador();

            /* itera por todos los elementos hasta encontrar el buscado o 
             * no tener más elementos */
            IteradorLista<T> iterador = this->iterador();
            while (iterador.tieneSiguiente() && ! encontrado) {
                
                encontrado = comparador->comparar(dato, iterador.get()) 
                                == IGUAL;
                    
                if (! encontrado){
                    
                    iterador.siguiente();
                }
            }
            
            return iterador;
        }
        
    private:
    
        /**
         * post: devuelve el primer nodo de la lista.
         */
        Nodo<T>* getPrimero() {
            
            return this->primero;
        }
    
        /**
         * post: cambia el primer nodo de la lista.
         */
        void setPrimero(Nodo<T>* nodo) {
            
            this->primero = nodo;
        }
        
        /**
         * post: devuelve el último nodo de la lista.
         */ 
        Nodo<T>* getUltimo() {
            
            return this->ultimo;
        }
        
        /**
         * post: cambia el último nodo de la lista.
         */
        void setUltimo(Nodo<T>* nodo) {
        
            this->ultimo = nodo;
        }

        /**
         * pre : ninguna.
         * post: devuelve el comparador usado para ordenar los elementos.
         */ 
        Comparador<T>* getComparador() {
            
            return this->comparador;
        }
        
        /**
         * pre : la lista está vacia.
         * post: cambia el comparador usado para ordenar los elementos.
         */
        void setComparador(Comparador<T>* comparador) {
            
            this->comparador = comparador;
        }
    
    /**
     * La clase IteradorLista<T> tiene acceso a todos los métodos
     * privados de Lista<T> ya que ambas entidades están vinculadas 
     * intrínsecamente. 
     */ 
    friend class IteradorLista<T>;
};

#endif
