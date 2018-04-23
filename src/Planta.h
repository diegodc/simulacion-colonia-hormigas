#ifndef __PLANTA_H__
#define __PLANTA_H__

#include "Elemento.h"
#include "Hoja.h"
#include "IntToChar.h"
#include "Lista.h"

class Planta : public Elemento {

	private:

		Lista<Elemento*>* Hojas;

	public:

		Planta(unsigned int cantidadHojas) {
			/* Creo una nueva lista */
			this->setHojas( new Lista<Elemento*> );
			/* Para la cantidad de hojas de la planta, voy creando nuevas instancias de hojas, y las agrego a la lista */
			if ((cantidadHojas > 0) && (cantidadHojas < 10)) {
				for (unsigned int i = 0 ; i < cantidadHojas ; i++)
					this->getHojas()->agregar(new Hoja);
			}
			else
				/* Si el valor de hojas pasado es menor a 1, o mayor a 9, se asigna 1 hoja como default */
				this->getHojas()->agregar(new Hoja);
		}

		virtual ~Planta() {
			/* Obtengo un iterador sobre la lista de hojas*/
			IteradorLista<Elemento*> iterador = this->getHojas()->iterador();

			/* Recorro la lista eliminando los nodos y destruyendo los objetos */
			while (iterador.tieneSiguiente())
				delete iterador.remover();
			/* Destruyo la lista */
			delete this->getHojas();
			this->setHojas(NULL);
		}

		/* Pre: El elemento retornado debe ser tomado por otro objeto para no perder la referencia y poder destruirlo luego */
		Elemento* CortarHoja() {
			/* Remuevo una hoja de la lista y la devuelvo */
			IteradorLista<Elemento*> iterador = this->getHojas()->iterador();
			if (iterador.tieneSiguiente())
				return iterador.remover();
			else
				/* Si la lista esta vacia, retorno NULL */
				return NULL;
		}

		bool HayHojas() const {
			return (this->getHojas()->tamanio() != 0);
		}

		virtual bool SosHoja() const {
			return false;
		}

		virtual bool SosHormiga() const {
			return false;
		}

		virtual bool SosHormiguero() const {
			return false;
		}

		virtual bool SosPlanta() const {
			return true;
		}

		virtual bool SosPiedra() const {
			return false;
		}

		virtual bool SosSemilla() const {
			return false;
		}

		virtual char getSalida() const {
			return IntToChar(this->getHojas()->tamanio());
		}

	private:
		
		void setHojas(Lista<Elemento*>* hojas) {
			this->Hojas = hojas;
		}

		Lista<Elemento*>* getHojas() const {
			return this->Hojas;
		}

};

#endif /*__PLANTA_H__*/
