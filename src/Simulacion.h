#ifndef __SIMULACION_H__
#define __SIMULACION_H__

#include "Casillero.h"
#include "ConstructorTerreno.h"
#include "EntradaSalida.h"
#include "Terreno.h"

#include <stdlib.h>
#include <string>

class Simulacion {

	private:

		Terreno* TerrenoSimulacion;

		EntradaSalida* EntradaSalidaSimulacion;

	public:

		Simulacion(std::string pathArchivoConfiguracion) {
			this->setEntradaSalidaSimulacion(new EntradaSalida(pathArchivoConfiguracion));
			this->setTerrenoSimulacion(NULL);
		}

		~Simulacion() {
			delete this->getTerrenoSimulacion();
			delete this->getEntradaSalidaSimulacion();
			this->setTerrenoSimulacion(NULL);
			this->setEntradaSalidaSimulacion(NULL);
		}

		void Ejecutar() {
			this->ConstruirTerrenoSimulacion();

			/* Obtengo el terreno */
			Terreno* TerrenoSimulacion = this->getTerrenoSimulacion();

			/* Inicio el archivo resultado */
			this->getEntradaSalidaSimulacion()->IniciarArchivoResultado();

			/* Imprimo en pantalla el terreno inicial */
			this->getEntradaSalidaSimulacion()->ImprimirTerrenoConsola(TerrenoSimulacion,0);
			/* Guardo en el archivo resultado el terreno inicial */
			this->getEntradaSalidaSimulacion()->GuardarTerreno(TerrenoSimulacion,0);

			for(unsigned int Ronda = 0 ; Ronda < this->getEntradaSalidaSimulacion()->getNumeroRondas() ; Ronda++)
				this->EjecutarRonda(Ronda + 1);

			/* Imprimo en pantalla el terreno final */
			this->getEntradaSalidaSimulacion()->ImprimirTerrenoConsola(TerrenoSimulacion,this->getEntradaSalidaSimulacion()->getNumeroRondas());

			/* Finalizo el archivo resultado */
			this->getEntradaSalidaSimulacion()->FinalizarArchivoResultado();
		}

	private:

		void setTerrenoSimulacion(Terreno* terrenoSimulacion) {
			this->TerrenoSimulacion = terrenoSimulacion;
		}

		void setEntradaSalidaSimulacion(EntradaSalida* entradaSalidaSimulacion) {
			this->EntradaSalidaSimulacion = entradaSalidaSimulacion;
		}

		Terreno* getTerrenoSimulacion() const {
			return this->TerrenoSimulacion;
		}

		EntradaSalida* getEntradaSalidaSimulacion() const {
			return this->EntradaSalidaSimulacion;
		}

		void ConstruirTerrenoSimulacion() {
			/* Instancio un constructor de terreno */
			ConstructorTerreno ConstructorTerrenoSimulacion;

			/* Obtengo la lista de lineas del terreno */
			Lista<std::string>* LineasTerreno = this->getEntradaSalidaSimulacion()->getLineasTerreno();

			/* Invoco al constructorTerreno y guardo el terreno creado */
			Terreno* terrenoSimulacion = ConstructorTerrenoSimulacion.ConstruirTerreno(LineasTerreno);
			this->setTerrenoSimulacion(terrenoSimulacion);
		}

		void EjecutarRonda(unsigned int NumeroRonda) const {
			/* Obtengo el terreno */
			Terreno* TerrenoSimulacion = this->getTerrenoSimulacion();

			/* Obtengo la lista de casilleros que contienen una hormiga */
			Lista<Casillero*>* HormigasTerreno = TerrenoSimulacion->getHormigas();

			unsigned int TamanioLista = HormigasTerreno->tamanio();

			Casillero* CasilleroHormigaActual;

			/* Para la cantidad de hormigas existentes */
			for(unsigned int i = 0 ; i < TamanioLista ; i++) {
				/* Tomo un casillero aleatorio de la lista */
				CasilleroHormigaActual = this->getCasilleroHormigaAleatorio(HormigasTerreno);
				this->EjecutarInteracciones(CasilleroHormigaActual);
			}
			/* Guardo el terreno en el archivo resultado */
			this->getEntradaSalidaSimulacion()->GuardarTerreno(TerrenoSimulacion,NumeroRonda);

			/* Destruyo la lista de hormigas */
			delete HormigasTerreno;
			HormigasTerreno = NULL;
		}

		void EjecutarInteracciones(Casillero* CasilleroHormigaActual) const {
			/* Obtengo el terreno */
			Terreno* TerrenoSimulacion = this->getTerrenoSimulacion();
			
			/* Casillero Destino de la hormiga */
			Casillero* CasilleroDestino = NULL;
			
			/* Obtengo la hormiga */
			Hormiga* HormigaActual = CasilleroHormigaActual->getHormiga();

			/* Pido al terreno los casilleros contiguos al casillero donde se encuentra la hormiga */
			Lista<Casillero*>* CasillerosContiguos = TerrenoSimulacion->getCasillerosContiguos(CasilleroHormigaActual);

			/* Le pido a la hormiga que elija un casillero y le paso el casillero donde se encuentra */
			CasilleroDestino = HormigaActual->Movete(CasillerosContiguos, CasilleroHormigaActual);

			/* Si el casillero no es NULL, la hormiga puede realizar una accion */
			if (CasilleroDestino != NULL) {
				/* Si el destino es un casillero transitable, muevo a la hormiga a ese casillero */
				if (CasilleroDestino->SosTransitable())
					CasilleroHormigaActual->MoverHormiga(CasilleroDestino);
				else {
					/* Si el destino es un hormiguero, la hormiga tiene carga, obtengo el hormiguero y deposito la carga */
					if (CasilleroDestino->TenesHormiguero()) {
						Hormiguero* HormigueroDestino = CasilleroDestino->getHormiguero();
						Elemento* CargaTransportada = HormigaActual->DejarCarga();
						HormigueroDestino->AlmacenarComida(CargaTransportada);
					}
					else
						/* El casillero destino contiene comida, le pido al casillero la comida, y se la entrego a la hormiga */
						if(CasilleroDestino->TenesComida()) {
							Elemento* Comida = CasilleroDestino->getComida();
							HormigaActual->LevantarCarga(Comida);
						}
				}
			}
		}

		Casillero* getCasilleroHormigaAleatorio(Lista<Casillero*>* ListaHormigas) const {
			IteradorLista<Casillero*> iterador = ListaHormigas->iterador();
			Casillero* CasilleroHormiga = NULL;
			unsigned int TamanioLista = ListaHormigas->tamanio();
			unsigned int PosicionIteradorLista;

			/* Dada una lista de casilleros, se devuelve un casillero tomado aleatoriamente de la lista
			 * el casillero es removido de la lista */
			if (TamanioLista != 0) {
				/* Aleatoriamente elijo un posicion valida para la lista */
				srand ( time(NULL) );
				PosicionIteradorLista = rand() % TamanioLista;

				/* Itero hasta la posicion aleatoria */
				for (unsigned int i = 0 ; i < PosicionIteradorLista ; i++)
					if (iterador.tieneSiguiente())
						iterador.siguiente();

				/* Remuevo el casillero elegido y lo retorno */
				if ( iterador.tieneSiguiente() )
					CasilleroHormiga = iterador.remover();
			}
			return CasilleroHormiga;
		}

};

#endif /*__SIMULACION_H__*/
