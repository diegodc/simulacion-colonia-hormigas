/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
 * IteradorLista 
 *
 * Version: 1.0
 * Autor: Mariano Simone (marianosimone+7541@gmail.com)
 *        Mariano Tugnarelli
 **/
#ifndef __ITERADOR_LISTA_H__
#define __ITERADOR_LISTA_H__

#include "Nodo.h"
#include "ElementoInexistenteException.h"

/**
 * Declaración anticipada (forward declaration) de la lista.
 * Es necesario para que el iterador pueda tener una referencia hacia 
 * la Lista.
 */
template<class T> class Lista;

/**
 * Los Iteradores proporcionan un modo de acceder secuencialmente a los
 * elementos de un estructura compuesta de elementos agregados sin 
 * exponer su representación interna
 * El Iterador define una interfaz para recorrer los elementos y acceder
 * a ellos.
 * Separar el mecanismo de recorrido de la estructura de datos permite 
 * definir iteradores con diferentes políticas de recorrido sin necesidad
 * de enumerarlas en la interfaz de la estructura de datos.
 */

/**
 * Iterador de la Lista Simplemente enlazada.
 * 
 */
template<class T> class IteradorLista {

    private:

        /**
         * Lista sobre la cual se realiza la iteración.
         */
        Lista<T>* lista;
        
        /**
         * Nodo por el actualmente se encuentra la iteración.
         */
        Nodo<T>* actual;

        /**
         * Indica si el iterador está haciendo un recorrido progresivo o 
         * regresivo; información necesaria para poder implementar un
         * esquema de lectura adelantada. 
         */
        bool progresivo;
        
    public:
        
        /**
         * pre : ninguna.
         * post: crea el iterador sobre la lista indicada.
         */
        IteradorLista(Lista<T>* lista) {
            this->setLista(lista);
            this->setActual(this->getLista()->getPrimero());
            this->progresivo = true;
        }

        /**
         * pre : ninguna.
         * post: libera los recursos asociados a la instancia. 
         */
        virtual ~IteradorLista() {
        }

        /**
         * pre : ninguna.
         * post: indica si existe un elemento siguiente en la iteración. 
         */
        bool tieneSiguiente() {

            /* para saber si existe un siguiente se debe cambiar a progresivo */
            this->setProgresivo(true);
            
            return this->getActual() != NULL;
        }

        /**
         * pre : existe un elemento siguiente (tieneSiguiente() == true).
         * post: devuelve el elemento siguiente en la iteración y avanza hacia 
         *       en la secuencia.
         */
        T siguiente() {

            this->setProgresivo(true);

            /* obtiene el elemento actual */
            T dato = this->get();
            
            /* avanza hacia la siguient posición */
            this->setActual(this->getActual()->getSiguiente());

            return dato;
        }

        /**
         * pre : ninguna.
         * post: indica si existe un elemento anterior en la iteración. 
         */
        bool tieneAnterior() {

            /* para saber si existe un siguiente se debe cambiar a progresivo */
            this->setProgresivo(false);
            
            return this->getActual() != NULL;
        }

        /**
         * pre : existe un elemento anterior (tieneAnterior() == true).
         * post: devuelve el elemento siguiente en la iteración y avanza hacia 
         *       en la secuencia.
         */
        T anterior() {

            this->setProgresivo(false);

            /* obtiene el elemento actual */
            T dato = this->get();
            
            /* avanza hacia la anterior posición */
            this->setActual(this->getActual()->getAnterior());

            return dato;
        }

        /**
         * pre : existe un elemento para el estado actual de la iteración 
         *       (existeSiguiente() == true ó existeAnterior() == true).
         * 
         * post: devuelve el elemento actual de la iteración.
         */
        T get() {

            if (this->getActual() == NULL) {
                
                throw ElementoInexistenteException("No se puede obtener");
            }
            
            return this->getActual()->getDato();
        }

        /**
         * pre : existe un elemento para el estado actual de la iteración 
         *       (existeSiguiente() == true ó existeAnterior() == true).
         * 
         * post: cambia el elemento actual de la iteración.
         */
        void set(T elemento) {

            if (this->getActual() == NULL) {
                
                throw ElementoInexistenteException("No se puede cambiar");
            }
            
            return this->getActual()->setDato(elemento);
        }

        /**
         * pre : existe un elemento para el estado actual de la iteración
         *       (existeSiguiente() == true ó existeAnterior() == true).
         * post: remueve el elemento actual de la iteración y lo devuelve.
         * 
         */
        T remover() {

            /* toma una copia del elemento para devolverlo */
            T dato = this->get();
            
            Nodo<T>* anterior = this->getActual()->getAnterior();
            Nodo<T>* siguiente = this->getActual()->getSiguiente();
            
            /* si no tiene un anterior es el primero de la lista */
            if (anterior != NULL) {
                
                anterior->setSiguiente(siguiente);
                
            } else {
                
                this->getLista()->setPrimero(siguiente);
            }
            
            /* si no tiene siguietne es el último de la lista */
            if (siguiente != NULL) {
                
                siguiente->setAnterior(anterior);
                
            } else {
                
                this->getLista()->setUltimo(anterior);
            }
            
            /* borra el nodo */
            delete this->getActual();
            
            /* si es progresivo deja el actual en el siguiente, sino en el 
             * anterior */
            this->setActual(this->getProgresivo() ? siguiente : anterior );
            
            return dato;
        }
        
        /**
         * pre : ninguna.
         * post: inserta el dato en la posición actual de la iteración,
         *       desplazando los elementos en sentido del siguiente.
         * 
         */
        void insertar(T dato) {

            Nodo<T>* actual = this->getActual();
            
            /* busca los nodos que serán el anterior y el siguiente */
            Nodo<T>* anterior = NULL;
            Nodo<T>* siguiente = actual;
            if (actual != NULL) {
                anterior = actual->getAnterior();

            } else {
                
                /* en función de cómo se está recorriendo la lista
                 * se puede insertar al comienzo o al final */
                if (this->getProgresivo()) {
                    anterior = this->getLista()->getUltimo();
                    
                } else {
                    siguiente = this->getLista()->getPrimero();
                }
            }
            
            this->insertar(dato, anterior, siguiente);

        }
        
        /**
         * pre : ninguna.
         * post: se coloca el comienzo de la lista.  
         */
        void primero() {

            this->setProgresivo(true);
            this->setActual(this->getLista()->getPrimero());
        }
        
        /**
         * pre : ninguna.
         * post: se coloca al final de la lista.
         */
        void ultimo() {
            
            this->setProgresivo(false);
            this->setActual(this->getLista()->getUltimo());
        }
        
    private:
        
        /**
         * post: cambia el estado de la iteración.
         */
        void setActual(Nodo<T>* nodo) {
            this->actual = nodo;
        }
        
        /**
         * post: devuelve el estado de la iteración. 
         */
        Nodo<T>* getActual() {
            return this->actual;
        }
        
        /**
         * post: devuelve la lista sobre la cual opera el iterador.
         */
        Lista<T>* getLista() {
            return this->lista;
        }

        /**
         * pre : no ha sido asinada previamente.
         * post: asigna la lista por la cual iterar.
         */
        void setLista(Lista<T>* lista) {

            this->lista = lista;
        }
        
        /**
         * post: indica si la iteración se está desarrollando en sentido 
         *       progresivo (true) o regresivo (false).
         */
        bool getProgresivo() {
            
            return this->progresivo;
        }

        /**
         * pre : ninguna.
         * post: se actualiza la estructura de la lista, insertando dato
         *       entre anterior y siguiente. Deja el actual en el elemento
         *       insertado.
         * 
         */
        void insertar(T dato, Nodo<T>* anterior, Nodo<T>* siguiente) {
            
            /* crea el nodo */
            Nodo<T>* nuevo = new Nodo<T>(dato);
            nuevo->setAnterior(anterior);
            nuevo->setSiguiente(siguiente);

            /* actualiza los nodos anterior y siguiente */
            if (anterior != NULL) { 
                anterior->setSiguiente(nuevo);
                
            } else {
                /* actualiza el primero en caso de insertar al comienzo */
                this->getLista()->setPrimero(nuevo);
            }
            
            if (siguiente != NULL) {
                siguiente->setAnterior(nuevo);
                
            } else {
                /* actualiza el último en caso de insertar al final */
                this->getLista()->setUltimo(nuevo);
            }

            /* se queda en la posición que insertó */
            this->setActual(nuevo);
        }
        
        /**
         * pre : ninguna.
         * post: ajusta el estado de la iteración en función del sentido
         *       impuesto: progresivo (esProgresivo == true) o regresivo
         *       (esProgresivo == false). 
         */
        void setProgresivo(bool esProgresivo) {
            
            /* solamente actualiza cuando hay un cambio */
            if (this->progresivo != esProgresivo) {
                
                Nodo<T>* nuevoActual = NULL;
                
                /* atrasa o adelanta el actual si cambio a regresivo o
                 * progresivo respectivamente */
                if (esProgresivo) {
                    
                    /* antes era regresivo, por tanto debe adelantar el curso */
                    if (this->getActual() != NULL) {

                        nuevoActual = this->getActual()->getSiguiente();
                        
                    } else {

                        /* como el actual es NULL se coloca en el principio */
                        nuevoActual = this->getLista()->getPrimero();
                    }
                    
                } else {
                    
                    /* antes era progresivo, por tanto debe atrasar el curso */
                    if (this->getActual() != NULL) {
                        
                        nuevoActual = this->getActual()->getAnterior();
                        
                    } else {
                        
                        /* como el actual es NULL se coloca en el final */
                        nuevoActual = this->getLista()->getUltimo();
                    }
                }
                
                /* finalmente cambia el estado de la iteración */
                this->setActual(nuevoActual);
                this->progresivo = esProgresivo;
            }
        }
        
};


#endif
