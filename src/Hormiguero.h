#ifndef __HORMIGUERO_H__
#define __HORMIGUERO_H__

#include "Definiciones.h"
#include "Elemento.h"
#include "Lista.h"

class Hormiguero : public Elemento {

	private:

		Lista<Elemento*>* Almacen;

	public:
		
		Hormiguero() {
			/* Creo una nueva lista de elementos */
			this->setAlmacen( new Lista<Elemento*> );
		}

		virtual ~Hormiguero() {
			/* Destruyo los objetos guardados en la lista */
			this->DestruirComidaAlmacenada();

			/* Detruyo la lista */
			delete this->getAlmacen();
			this->setAlmacen(NULL);
		}

		void AlmacenarComida(Elemento* comida) {
			/* Si el elemento pasado es hoja o semilla, se almacena el elemento */
			this->Almacenar(comida);
		}

		unsigned int getSemillasAlmacenadas() const {
			/* Recorro la lista almacen y cuento la cantidad de semillas */
			IteradorLista<Elemento*> iterador = this->getAlmacen()->iterador();
			unsigned int cantidad = 0;

			while (iterador.tieneSiguiente()) {
				if (iterador.siguiente()->SosSemilla())
					cantidad++;
			}
			return cantidad;
		}

		unsigned int getHojasAlmacenadas() const {
			/* Recorro la lista almacen y cuento la cantidad de hojas */
			IteradorLista<Elemento*> iterador = this->getAlmacen()->iterador();
			unsigned int cantidad = 0;

			while (iterador.tieneSiguiente()) {
				if (iterador.siguiente()->SosHoja())
					cantidad++;
			}
			return cantidad;
		}

		virtual bool SosHoja() const {
			return false;
		}

		virtual bool SosHormiga() const {
			return false;
		}

		virtual bool SosHormiguero() const {
			return true;
		}

		virtual bool SosPlanta() const {
			return false;
		}

		virtual bool SosPiedra() const {
			return false;
		}

		virtual bool SosSemilla() const {
			return false;
		}

		virtual char getSalida() const {
			return SALIDA_HORMIGUERO;
		}		

	private:

		void Almacenar(Elemento* comida) {
			if (comida != NULL)
				if ((comida->SosHoja()) || (comida->SosSemilla()))
					this->getAlmacen()->agregar(comida);
		}

		void setAlmacen(Lista<Elemento*>* almacen) {
			this->Almacen = almacen;
		}

		Lista<Elemento*>* getAlmacen() const {
			return this->Almacen;
		}

		void DestruirComidaAlmacenada() {
			/* Obtengo un iterador sobre la lista de comida almacenda */
			IteradorLista<Elemento*> iterador = this->getAlmacen()->iterador();
			
			/* Recorro la lista eliminando los nodos y destruyendo los objetos */
			while (iterador.tieneSiguiente())
				delete iterador.remover();
		}

};

#endif /*__HORMIGUERO_H__*/
