#ifndef __CASILLERO_H__
#define __CASILLERO_H__

#include "Definiciones.h"
#include "Elemento.h"
#include "Hormiguero.h"
#include "Planta.h"

class Hormiga;

class Casillero {

	private:

		unsigned int NivelFeromona;

		Elemento* ElementoContenido;

	public:

		Casillero() {
			this->setElementoContenido(NULL);
			this->setNivelFeromona(0);
		}

		Casillero(Elemento* elemento) {
			this->setElementoContenido(elemento);
			this->setNivelFeromona(0);
		}

		~Casillero() {
			this->DestruirElemento();
		}

		void MoverHormiga(Casillero* ProximoCasilleroHormiga) {
			/* Dado un casillero transitable, si el casillero sobre el cual se invoca el metodo, contiene una hormiga,
			 * se remueve la hormiga de este casillero, se aumenta el nivel de feromonas del mismo, y se coloca la hormiga en el casillero transitable */
			if(( this->TenesHormiga() ) && ( ProximoCasilleroHormiga->SosTransitable() )) {
				Elemento* hormiga = this->RemoverElemento();
				ProximoCasilleroHormiga->setElementoContenido(hormiga);
				this->AumentarNivelFeromona();
			}
		}

		void AumentarNivelFeromona() {
			/* Aumenta en uno el nivel de feromona del casillero */
				this->setNivelFeromona( this->getNivelFeromona() + 1 );
		}

		/* Pre: El elemento retornado debe ser tomado por otro objeto para no perder la referencia y poder destruirlo luego */
		Elemento* getComida() {
			Elemento* Comida = NULL;

			/* Si el casillero contiene comida, segun el tipo, se obtiene el elemento correspondiente y se devuelve */
			if (this->TenesComida()) {
				/* El elemento contenido es una planta */
				if (this->TenesPlanta()) {
					/* Obtengo un puntero al objeto */
					Planta* planta = this->getPlanta();
					/* Corto una hoja de la planta y la devuelvo */
					Comida = planta->CortarHoja();
					/* Si ya no quedan hojas en la planta, la destruyo, eliminandola del terreno */
					if (!planta->HayHojas())
						this->DestruirElemento();
				}
				else
					/* El elemento contenido es una semilla, la remuevo del casillero y devuelvo el elemento */
					Comida = this->RemoverElemento();
			}
			/* Si el casillero no contiene comida, se retorna NULL */
			return Comida;
		}

		Hormiga* getHormiga() const {
			/* Si el casillero contiene un elemento hormiga, devuelve un puntero al objeto para poder invocar sus metodos especificos */
			if (this->TenesHormiga())
				return (Hormiga*)this->getElementoContenido();
			else
				return NULL;
		}

		Hormiguero* getHormiguero() const {
			/* Si el casillero contiene un elemento hormiguero, devuelve un puntero al objeto para poder invocar sus metodos especificos */
			if (this->TenesHormiguero())
				return (Hormiguero*)this->getElementoContenido();
			else
				return NULL;
		}

		bool SosTransitable() const {
			return (this->getElementoContenido() == NULL);
		}

		bool TenesHormiga() const {
			Elemento* elemento = this->getElementoContenido();
			if (elemento != NULL)
				return elemento->SosHormiga();
			else
				return false;
		}		

		bool TenesHormiguero() const {
			Elemento* elemento = this->getElementoContenido();
			if (elemento != NULL)
				return elemento->SosHormiguero();
			else
				return false;
		}

		bool TenesComida() const {
			if (this->getElementoContenido() != NULL)
				return (this->TenesPlanta() || this->TenesSemilla());
			else
				return false;
		}

		unsigned int getNivelFeromona() const {
			return this->NivelFeromona;
		}

		char getSalida() const {
			/* Devuelve el caracter de salida correspondiente al casillero, si el casillero contiene un elemento, le pregunta a este su salida */
			if (this->SosTransitable()) {
				if (this->getNivelFeromona() > 0)
					return SALIDA_CASILLERO_MARCADO;
				else
					return SALIDA_CASILLERO_TRANSITABLE;
			}
			else
				return this->getElementoContenido()->getSalida();
		}

	private:

		bool TenesPlanta() const {
			Elemento* elemento = this->getElementoContenido();
			if (elemento != NULL)
				return elemento->SosPlanta();
			else
				return false;
		}

		bool TenesSemilla() const {
			Elemento* elemento = this->getElementoContenido();
				if (elemento != NULL)
				return elemento->SosSemilla();
			else
				return false;
		}

		Elemento* getElementoContenido() const {
			return this->ElementoContenido;
		}

		Planta* getPlanta() const {
			/* Si el casillero contiene un elemento planta, devuelve un puntero a planta para poder invocar sus metodos especificos */
			if (this->TenesPlanta())
				return (Planta*)this->getElementoContenido();
			else
				return NULL;
		}

		/* Pre: El elemento retornado debe ser tomado por otro objeto para no perder la referencia y poder destruirlo luego */
		Elemento* RemoverElemento() {
			/* Devuelve el elemento contenido y setea el contenido del casillero en NULL */
			Elemento* elemento = this->getElementoContenido();
			this->setElementoContenido(NULL);
			return elemento;
		}

		void DestruirElemento() {
			/* Destruye el elemento contenido y setea el contenido en NULL */
			Elemento* elemento = this->getElementoContenido();
			if (elemento != NULL) {
				delete elemento;
				this->setElementoContenido(NULL);
			}
		}

		void setElementoContenido(Elemento* elemento) {
			this->ElementoContenido = elemento;
		}

		void setNivelFeromona(unsigned int nivelFeromona) {
			/* El nivel maximo de feromonas es 999 */
			if ((nivelFeromona >= 0) && (nivelFeromona < 1000))
				this->NivelFeromona = nivelFeromona;
		}

};

#endif /*__CASILLERO_H__*/
