/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
 * Comparadores.
 * 
 * Version: 1.0
 * Autor: Mariano Tugnarelli
 **/

#ifndef __COMPARADOR_H__
#define __COMPARADOR_H__

enum ResultadoComparacion {
    MENOR,
    IGUAL,
    MAYOR,
};

/**
 * Clase abstracta que encapsula la lógica de comparación utilizada para 
 * ordenar las estructuras de datos.
 * 
 */ 
template<class T> class Comparador {

    public:
        /**
         * post: devuelve  MAYOR, MENOR o IGUAL de acuerdo a la relación 
         *       existente entre elemento1 y elemento2.   
         * 
         * Método abstracto que deberá ser implementado por los descendientes
         * de Comparador especificando un comportamiento particular.  
         */
        virtual ResultadoComparacion comparar(T elemento1, T elemento2) = 0;
};

/**
 * Implementación del Comparador que utiliza los operadores "==", "<" y ">"
 * estableciendo un orden ascendente. 
 * 
 */
template<class T> class ComparadorSimpleAscendente : public Comparador<T> {
    
    public:
        virtual ResultadoComparacion comparar(T elemento1, T elemento2) {
            
            ResultadoComparacion resultado;
            
            if (elemento1 == elemento2) {
                
                resultado = IGUAL;
                
            } else if (elemento1 > elemento2) {
                
                resultado = MAYOR;
                
            } else {
                
                resultado = MENOR;
            }
            
            return resultado;
        }
};


/**
 * Implementación del Comparador que utiliza los operadores "==", "<" y ">"
 * estableciendo un orden descendente. 
 * 
 */
template<class T> class ComparadorSimpleDescendente : public Comparador<T> {
    
    public:
        virtual ResultadoComparacion comparar(T elemento1, T elemento2) {
            
            ResultadoComparacion resultado;
            
            if (elemento1 == elemento2) {
                
                resultado = IGUAL;
                
            } else if (elemento1 < elemento2) {
                
                resultado = MAYOR;
                
            } else {
                
                resultado = MENOR;
            }
            
            return resultado;
        }
};

/**
 * Implementación del Comparador cuyo comportamiento es nulo, al comparar
 * dos elementos cualesquiera devuelve IGUAL.
 * 
 */
template<class T> class ComparadorConstante : public Comparador<T> {
    
    public:
        virtual ResultadoComparacion comparar(T elemento1, T elemento2) {

            return IGUAL;  
        }

};

#endif
