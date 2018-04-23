/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
 * 
 * Version: 1.0
 * Autor: Mariano Tugnarelli
 **/

#ifndef __ELEMENTO_INEXISTENTE_EXCEPTION_H__
#define __ELEMENTO_INEXISTENTE_EXCEPTION_H__

#include <string>

/**
 * Excepción provocada cuando se intenta acceder a un elemento que no existe
 * en la lista.
 * 
 */ 
class ElementoInexistenteException {
    
    private:
        std::string mensaje;
    
    public:
        ElementoInexistenteException(std::string mensaje) {
            
            this->setMensaje(mensaje);
        }
        
        virtual ~ElementoInexistenteException() {
            
        }

        std::string getMensaje() {
            
            return this->mensaje;
        }
        
    protected:
        
        void setMensaje(std::string mensaje) {
            
            this->mensaje = mensaje;
        }
};

#endif
