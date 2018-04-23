#ifndef __IOTERRENO_H__
#define __IOTERRENO_H__

#include "archivoTexto.h"
#include "Casillero.h"
#include "Configuracion.h"
#include "Hormiguero.h"
#include "IntToString.h"
#include "Lista.h"
#include "Terreno.h"

#include <string>
#include <iostream>

/* EntradaSalida maneja la entrada y salida de datos, desde y hacia los archivos */

class EntradaSalida {

	private:

		Configuracion* ConfiguracionSimulacion;

	public:

		EntradaSalida(std::string pathArchivoConfiguracion) {
			this->setConfiguracion(new Configuracion(pathArchivoConfiguracion));
		}

		~EntradaSalida() {
			delete this->getConfiguracion();
			this->setConfiguracion(NULL);
		}

		/* Extrae del archivo que contiene el diagrama del terreno, un lista de strings que representan las filas del terreno
		 * La lista es destruida por el metodo ConstruirTerreno de la clase ConstructorTerreno */
		Lista<std::string>* getLineasTerreno() const {
			Lista<std::string>* LineasTerreno = new Lista<std::string>;

			ArchivoTexto archivoTerreno;
			crear(archivoTerreno, this->getConfiguracion()->getPathArchivoTerreno());

			std::string Fila;

			while (leerLinea(archivoTerreno,Fila))
				LineasTerreno->agregar(Fila);

			destruir(archivoTerreno);

			return LineasTerreno; 
		}

		/* Dado el puntero al terreno, y el numero de ronda actual, escribe en el archivo resultado la informacion de la simulacion */
		void GuardarTerreno(const Terreno* terreno, unsigned int RondaNumero) const {
			ArchivoTexto archivoResultado;

			std::string ronda = IntToString(RondaNumero);
			std::string semillas;
			std::string hojas;

			if (terreno->getCasilleroHormiguero() != NULL) {
				semillas = IntToString(terreno->getCasilleroHormiguero()->getHormiguero()->getSemillasAlmacenadas());
				hojas = IntToString(terreno->getCasilleroHormiguero()->getHormiguero()->getHojasAlmacenadas());
			}
			else {
				semillas = "0";
				hojas = "0";
			}

			crear(archivoResultado, this->getConfiguracion()->getPathArchivoResultado());
			irAlFinal(archivoResultado);

			tabular(archivoResultado);
			escribirCadena(archivoResultado,"<ronda numero=");
			escribirCaracter(archivoResultado,'"');
			escribirCadena(archivoResultado,ronda);
			escribirCaracter(archivoResultado,'"');
			escribirCaracter(archivoResultado,'>');
			bajarDeLinea(archivoResultado);

			tabular(archivoResultado);
			tabular(archivoResultado);
			escribirCadena(archivoResultado,"<terreno>");
			bajarDeLinea(archivoResultado);

			for(unsigned int i = 0 ; i < terreno->getDimensionFilas() ; i++) {
				tabular(archivoResultado);
				tabular(archivoResultado);
				tabular(archivoResultado);
				for(unsigned int j = 0 ; j < terreno->getDimensionColumnas() ; j++) {
					escribirCaracter(archivoResultado,terreno->getSalida(i,j));
					escribirCaracter(archivoResultado,' ');
				}
				bajarDeLinea(archivoResultado);
			}

			tabular(archivoResultado);
			tabular(archivoResultado);
			escribirCadena(archivoResultado,"</terreno>");
			bajarDeLinea(archivoResultado);

			tabular(archivoResultado);
			tabular(archivoResultado);
			escribirCadena(archivoResultado,"<hormiguero>");
			bajarDeLinea(archivoResultado);

			tabular(archivoResultado);
			tabular(archivoResultado);
			tabular(archivoResultado);
			escribirCadena(archivoResultado,"<semillas>");
			escribirCadena(archivoResultado,semillas);
			escribirCadena(archivoResultado,"</semillas>");
			bajarDeLinea(archivoResultado);
			tabular(archivoResultado);
			tabular(archivoResultado);
			tabular(archivoResultado);
			escribirCadena(archivoResultado,"<hojas>");
			escribirCadena(archivoResultado,hojas);
			escribirCadena(archivoResultado,"</hojas>");
			bajarDeLinea(archivoResultado);

			tabular(archivoResultado);
			tabular(archivoResultado);
			escribirCadena(archivoResultado,"</hormiguero>");
			bajarDeLinea(archivoResultado);

			tabular(archivoResultado);
			escribirCadena(archivoResultado,"</ronda>");
			bajarDeLinea(archivoResultado);
			destruir(archivoResultado);
		}

		void ImprimirTerrenoConsola(const Terreno* terreno, unsigned int RondaNumero) {
			for(unsigned int n = 0 ; n < terreno->getDimensionColumnas() * 2 ; n++)
				std::cout << "-";
			std::cout << std::endl;

			std::cout << "Ronda: " << RondaNumero << std::endl;

			for(unsigned int n = 0 ; n < terreno->getDimensionColumnas() * 2 ; n++)
				std::cout << "-";
			std::cout << std::endl;

			for (unsigned int i = 0 ; i < terreno->getDimensionFilas() ; i++) {
				for(unsigned int j = 0 ; j < terreno->getDimensionColumnas() ; j++)
					std::cout << terreno->getSalida(i,j) << " ";
				std::cout << std::endl;
			}

			for(unsigned int n = 0 ; n < terreno->getDimensionColumnas() * 2 ; n++)
				std::cout << "-";
			std::cout << std::endl;

			if (terreno->getCasilleroHormiguero() != NULL) {
				Hormiguero* hormiguero = terreno->getCasilleroHormiguero()->getHormiguero();
				std::cout << "Semillas: " << hormiguero->getSemillasAlmacenadas() << " - Hojas: " << hormiguero->getHojasAlmacenadas() << std::endl;
			}

			for(unsigned int n = 0 ; n < terreno->getDimensionColumnas() * 2 ; n++)
				std::cout << "-";
			std::cout << std::endl;
		}

		/* Pre: El archivoResultado no existe o esta vacio
		 * Post: Escribe el encabezado del archivo resultado */
		void IniciarArchivoResultado() const {
			ArchivoTexto archivoResultado;
			crear(archivoResultado, this->getConfiguracion()->getPathArchivoResultado());
			escribirCadena(archivoResultado,"<simulacion>");
			bajarDeLinea(archivoResultado);
			destruir(archivoResultado);
		}

		/* Pre: Ya se han ejecutado todas las rondas, y en cada una de ellas se ha guardado el terreno
		 * Post: Escribe en el archivo resultado el comentario final */
		void FinalizarArchivoResultado() const {
			ArchivoTexto archivoResultado;
			crear(archivoResultado, this->getConfiguracion()->getPathArchivoResultado());
			irAlFinal(archivoResultado);
			escribirCadena(archivoResultado,"</simulacion>");
			destruir(archivoResultado);
		}

		unsigned int getNumeroRondas() const {
			return this->getConfiguracion()->getNumeroRondas();
		}

	private:

		void setConfiguracion(Configuracion* configuracion) {
			this->ConfiguracionSimulacion = configuracion;
		}

		Configuracion* getConfiguracion() const {
			return this->ConfiguracionSimulacion;
		}

};

#endif /*__IOTERRENO_H__*/
