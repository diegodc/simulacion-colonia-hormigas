#ifndef __HORMIGA_H__
#define __HORMIGA_H__

#include "Definiciones.h"
#include "Elemento.h"
#include "Casillero.h"
#include "Lista.h"

#include <stdlib.h>

class Hormiga : public Elemento {

	private:

		Elemento* CargaTransportada;

		Lista<Casillero*>* CasillerosRecorridos;

	public:

		Hormiga() {
			/* Inicialmente no transporta carga, se crea la lista de casilleros recorridos */
			this->setCargaTransportada(NULL);
			this->setCasillerosRecorridos(new Lista<Casillero*>);
		}

		virtual ~Hormiga() {
			/* Si la hormiga esta transportando carga, se detruye el objeto transportado */
			if (this->TransportasCarga()) {
				delete this->getCargaTransportada();
				this->setCargaTransportada(NULL);
			}
			/* Detruyo la lista de casilleros recorridos */
			delete this->getCasillerosRecorridos();
			this->setCasillerosRecorridos(NULL);
		}

		void LevantarCarga(Elemento* carga) {
			/* Dado un elemento, si este es hoja o semillas, la hormiga toma la carga y borra los casilleros recorridos */
			if ( !this->TransportasCarga() )
				if (carga != NULL)
					if ( carga->SosSemilla() || carga->SosHoja() ) {
						this->setCargaTransportada(carga);
						this->BorrarCasillerosRecorridos();
					}
		}
		/* Pre: El elemento retornado debe ser tomado por otro objeto para no perder la referencia y poder destruirlo luego */
		Elemento* DejarCarga() {
			/* Devuelve la carga que transporta la hormiga y borra los casilleros recorridos */
			Elemento* carga = this->getCargaTransportada();
			if (carga != NULL) {
				this->setCargaTransportada(NULL);
				this->BorrarCasillerosRecorridos();
			}
			return carga;
		}

		Casillero* Movete(Lista<Casillero*>* CasillerosContiguos, Casillero* Ubicacion) const {

			/* Casillero que la hormiga elige */
			Casillero* Destino = NULL;

			/* Si transporta carga, busca un hormiguero */
			if (this->TransportasCarga())
				Destino = this->IrHormiguero(CasillerosContiguos);
			/* Si no transporta carga, busca comida */
			else
				Destino = this->IrComida(CasillerosContiguos);

			/* Si no encontro hormiguero o comida, se mueve a un casillero libre */
			if (Destino == NULL)
				Destino = this->IrCasillero(CasillerosContiguos);

			/* Si destino es NULL, la hormiga no tiene destinos posibles, por lo tanto se mantiene en su lugar
			 * si tiene un destino posible, y este es un casillero transitable, marca la ubicacion actual como ya recorrida */  
			if (Destino != NULL) 
				if (Destino->SosTransitable())
						this->AgregarCasilleroRecorrido(Ubicacion);

			/* Destruyo la lista */
			delete CasillerosContiguos;
			CasillerosContiguos = NULL;

			/* Retorno el casillero elegido */
			return Destino;
		}

		virtual bool SosHoja() const {
			return false;
		}

		virtual bool SosHormiga() const {
			return true;
		}

		virtual bool SosHormiguero() const {
			return false;
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
			char salida;
			if ( this->TransportasCarga() ) {
				if ( this->getCargaTransportada()->SosSemilla() )
					salida = SALIDA_HORMIGA_CARGA_SEMILLA;
				else
					if ( this->getCargaTransportada()->SosHoja() )
						salida = SALIDA_HORMIGA_CARGA_HOJA;
			}
			else
				salida = SALIDA_HORMIGA;
			return salida;
		}

	private:

		void setCargaTransportada(Elemento* carga) {
			this->CargaTransportada = carga;
		}

		void setCasillerosRecorridos(Lista<Casillero*>* casilleros) {
			this->CasillerosRecorridos = casilleros;
		}

		void AgregarCasilleroRecorrido(Casillero* casillero) const {
			/* Agrega un casillero a la lista de recorridos */
			if (casillero != NULL)
				this->getCasillerosRecorridos()->agregar(casillero);
		}

		void BorrarCasillerosRecorridos() const {
			/* Remuevo todos los casilleros que la hormiga ya recorrio para que pueda volver por el camino marcado de feromonas */
			IteradorLista<Casillero*> iterador = this->getCasillerosRecorridos()->iterador();
			while (iterador.tieneSiguiente())
				iterador.remover();
		}

		bool RecorriCasillero(Casillero* casillero) const {
			/* Dado un casillero, la hormiga lo busca entre los que ya recorrio */
			bool resultado = false;
			if (this->getCasillerosRecorridos()->tamanio() != 0) {
				IteradorLista<Casillero*> iterador = this->getCasillerosRecorridos()->iterador();
				while (iterador.tieneSiguiente())
					if (casillero == iterador.siguiente())
						resultado = true;
			}
			return resultado;
		}

		bool TransportasCarga() const {
			return ( this->getCargaTransportada() != NULL);
		}

		Casillero* IrHormiguero(Lista<Casillero*>* CasillerosContiguos) const {
			IteradorLista<Casillero*> iterador = CasillerosContiguos->iterador();
			Casillero* Destino = NULL;
			Casillero* casillero;

			/* Recorro la lista buscando si hay un hormiguero */
			while (iterador.tieneSiguiente()) {
				casillero = iterador.siguiente();
				if (casillero->TenesHormiguero())
					Destino = casillero;
			}
			return Destino;
		}

		Casillero* IrComida(Lista<Casillero*>* CasillerosContiguos) const {
			/* Obtengo la lista de casilleros con comida */
			Lista<Casillero*>* CasillerosComida = this->getCasillerosComida(CasillerosContiguos);
			Casillero* Destino = NULL;

			/* Si hay casilleros con comida, se elige uno aleatoriamente */
			if (CasillerosComida->tamanio() != 0)
				Destino = this->getCasilleroAleatorio(CasillerosComida);

			/* Destruyo la lista creada */
			delete CasillerosComida;
			CasillerosComida = NULL;

			return Destino;
		}

		Casillero* IrCasillero(Lista<Casillero*>* CasillerosContiguos) const {
			/* Obtengo la lista de transitables, en base a la lista de casilleros contiguos */
			Lista<Casillero*>* CasillerosTransitables = this->getCasillerosTransitables(CasillerosContiguos);
			Lista<Casillero*>* CasillerosNoRecorridos = NULL;
			Casillero* Destino = NULL;

			/* Si existen casilleros transibles */
			if (CasillerosTransitables->tamanio() != 0) {

				/* Si solo hay un casillero transitable posible */
				if (CasillerosTransitables->tamanio() == 1)
					Destino = this->getCasilleroAleatorio(CasillerosTransitables);

				/* Hay mas de un casillero transitable posible */
				else {
					/* Obtengo la lista de casilleros no recorridos */
					CasillerosNoRecorridos = this->getCasillerosNoRecorridos(CasillerosTransitables);

					/* Si hay mas de un casillero posible, se elige aleatoriamente entre aquellos con mayor nivel de feromonas */
					if (CasillerosNoRecorridos->tamanio() > 1)
						Destino = this->IrCasilleroFeromona(CasillerosNoRecorridos);

					/* Hay solo un (o ningun) casillero que la hormiga no haya recorrido */
					else
						/* Hay solo uno */
						if (CasillerosNoRecorridos->tamanio() == 1)
							Destino = this->getCasilleroAleatorio(CasillerosNoRecorridos);

						/* No hay casilleros que la hormiga no haya recorrido */
						else
							/* Se elige un casillero aleatorio entre los transitables 
							 * No se tiene en cuenta el nivel de feromonas de los casilleros
							 * para evitar que la hormiga entre en un loop */
							Destino = this->getCasilleroAleatorio(CasillerosTransitables);
				}
			}
			/* Destruyo las listas */
			delete CasillerosTransitables;
			CasillerosTransitables = NULL;
			
			if (CasillerosNoRecorridos != NULL) {
				delete CasillerosNoRecorridos;
				CasillerosNoRecorridos = NULL;
			}
			return Destino;
		}

		Casillero* IrCasilleroFeromona(Lista<Casillero*>* CasillerosTransitables) const {
			IteradorLista<Casillero*> iterador = CasillerosTransitables->iterador();

			/* Creo una nueva lista para guardar los casilleros */
			Lista<Casillero*>* ListaCasilleros = new Lista<Casillero*>;
			unsigned int MaximoNivelFeromonas = 0;
			Casillero* Destino = NULL;
			Casillero* casillero;

			/* Recorro la lista y asigno el maximo nivel de feromonas de los casilleros */
			while ( iterador.tieneSiguiente() ) {
				casillero = iterador.siguiente();
					if ( casillero->getNivelFeromona() > MaximoNivelFeromonas )
						MaximoNivelFeromonas = casillero->getNivelFeromona();
			}

			/* Recorro la lista y agrego a la lista local los casilleros cuyo nivel del feromona es igual al maximo */
			iterador.primero();
			while ( iterador.tieneSiguiente() ) {
				casillero = iterador.siguiente();
				if ( casillero->getNivelFeromona() == MaximoNivelFeromonas )
					ListaCasilleros->agregar(casillero);
			}

			/* Tomo el casillero destino */
			if (ListaCasilleros->tamanio() != 0)
				Destino = this->getCasilleroAleatorio(ListaCasilleros);

			/* Destruyo la lista creada */
			delete ListaCasilleros;
			ListaCasilleros = NULL;

			return Destino;
		}

		Casillero* getCasilleroAleatorio(Lista<Casillero*>* ListaCasilleros) const {
			IteradorLista<Casillero*> iterador = ListaCasilleros->iterador();
			Casillero* CasilleroElegido = NULL;
			unsigned int PosicionIteradorLista;

			/* Dada una lista de casilleros, se devuelve un casillero tomado aleatoriamente de la lista */
			if (ListaCasilleros->tamanio() != 0) {
				/* Aleatoriamente elijo un posicion valida para la lista */
				srand ( time(NULL) );
				PosicionIteradorLista = rand() % ListaCasilleros->tamanio();

				/* Itero hasta la posicion aleatoria */
				for (unsigned int i = 0 ; i < PosicionIteradorLista ; i++)
					if (iterador.tieneSiguiente())
						iterador.siguiente();

				/* Tomo el casillero elegido */
				if ( iterador.tieneSiguiente() )
					CasilleroElegido = iterador.siguiente();
			}
			return CasilleroElegido;
		}

		Elemento* getCargaTransportada() const {
			return this->CargaTransportada;
		}

		Lista<Casillero*>* getCasillerosRecorridos() const {
			return this->CasillerosRecorridos;
		}

		/* Pre: La lista retornada debera ser posteriormente detruida por otro objeto */
		Lista<Casillero*>* getCasillerosComida(Lista<Casillero*>* CasillerosContiguos) const {
			/* Se crea una nueva lista, esta sera destruida por otro metodos que invoque al actual */
			Lista<Casillero*>* CasillerosComida = new Lista<Casillero*>;
			Casillero* casillero;

			/* Recorro la lista de contiguos y agrego a la lista local los casilleros que contienen comida */
			IteradorLista<Casillero*> iterador = CasillerosContiguos->iterador();
			while ( iterador.tieneSiguiente() ) {
				casillero = iterador.siguiente();
				if (casillero->TenesComida())
					CasillerosComida->agregar(casillero);
			}
			return CasillerosComida;
		}

		/* Pre: La lista retornada debera ser posteriormente detruida por otro objeto */
		Lista<Casillero*>* getCasillerosTransitables(Lista<Casillero*>* CasillerosContiguos) const {
			/* Se crea una nueva lista, esta sera destruida por otro metodos que invoque al actual */
			Lista<Casillero*>* CasillerosTransitables = new Lista<Casillero*>;
			Casillero* casillero;

			/* Recorro la lista de contiguos y agrego a la lista local los casilleros transitables*/
			IteradorLista<Casillero*> iterador = CasillerosContiguos->iterador();
			while ( iterador.tieneSiguiente() ) {
				casillero = iterador.siguiente();
				if (casillero->SosTransitable())
					CasillerosTransitables->agregar(casillero);	
			}
			return CasillerosTransitables;
		}

		/* Pre: La lista retornada debera ser posteriormente detruida por otro objeto */
		Lista<Casillero*>* getCasillerosNoRecorridos(Lista<Casillero*>* CasillerosTransitables) const {
			/* Se crea una nueva lista, esta sera destruida por otro metodos que invoque al actual */
			Lista<Casillero*>* CasillerosNoRecorridos = new Lista<Casillero*>;
			Casillero* casillero;

			/* Recorro la lista de transitables y agrego a la lista local aquellos casilleros en los cuales la hormiga no estuvo */
			IteradorLista<Casillero*> iterador = CasillerosTransitables->iterador();
			while ( iterador.tieneSiguiente() ) {
				casillero = iterador.siguiente();
				if (!this->RecorriCasillero(casillero))
					CasillerosNoRecorridos->agregar(casillero);	
			}
			return CasillerosNoRecorridos;
		}

};

#endif /*__HORMIGA_H__*/
