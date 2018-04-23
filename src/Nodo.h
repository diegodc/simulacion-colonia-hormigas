/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
 * Nodo Doblemente Enlazado
 * Implementacion con utilización de Templates
 * Versión: 1.0
 * Autor: Mariano Simone (marianosimone+7541@gmail.com)
 *        Mariano Tugnarelli
 **/

#ifndef __NODO_DOBLEMENTE_ENLAZADO_H__
#define __NODO_DOBLEMENTE_ENLAZADO_H__

template<class T> class Nodo {

    private:
        
        /* elemento almacenado */ 
        T dato;
        
        /* puntero al siguiente nodo */
        Nodo<T>* siguiente;
        
        /* puntero al anterior nodo */
        Nodo<T>* anterior;
    
    public:
        /*
         * pre : ninguna.
         * post: inicializa el estado del nodo, dejando el dato con el valor del
         *       parámetro pasado y sin siguiente ni anterior.
         */
        Nodo(T dato) {
            this->setDato(dato);
            this->setSiguiente(NULL);
            this->setAnterior(NULL);
        }
    
        /*
         * pre : ninguna.
         * post: libera los recursos asociados al nodo.
         * 
         */
        virtual ~Nodo() {
        }
    
        /*
         * pre : ninguna.
         * post: cambia el valor del dato.
         * 
         */
        void setDato(T dato) {
            this->dato = dato;
        }
    
        /*
         * pre : ninguna.
         * post: devuelve el valor del dato.
         */
        T getDato() {
            return this->dato;
        }
    
        /*
         * pre : ninguna.
         * post: cambia el valor del siguiente.
         */
        void setSiguiente(Nodo<T>* nodo) {
            this->siguiente = nodo;
        }
    
        /*
         * pre : ninguna.
         * post: devuelve el valor del siguiente.
         */
        Nodo<T>* getSiguiente() {
            return this->siguiente;
        }
    
        /* pre : ninguna.
         * post: indica si existe un Nodo siguiente. 
         */
        bool tieneSiguiente() const {
            
            return (this->siguiente != NULL);
        }

        /*
         * pre : ninguna.
         * post: cambia el valor del anterior.
         */
        void setAnterior(Nodo<T>* nodo) {
            this->anterior = nodo;
        }
    
        /*
         * pre : ninguna.
         * post: devuelve el valor del anterior.
         */
        Nodo<T>* getAnterior() {
            return this->anterior;
        }

        /* pre : ninguna.
         * post: indica si existe un Nodo anterior. 
         */
        bool tieneAnterior() const {
            return (this->anterior != NULL);
        }
};

#endif
