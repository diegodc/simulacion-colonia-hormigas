#ifndef __CONSTRUCTORTERRENO_H__
#define __CONSTRUCTORTERRENO_H__

#include "Casillero.h"
#include "Hormiga.h"
#include "Hormiguero.h"
#include "Lista.h"
#include "Piedra.h"
#include "Planta.h"
#include "Semilla.h"
#include "Terreno.h"

#include <string>

typedef Casillero*** Matriz;

/* ConstructorTerreno no tiene atributos, solo se encarga de contruir el terreno de acuerdo a la lista que proporciona la clase EntradaSalida */

class ConstructorTerreno {
	
	public:
		
		ConstructorTerreno() {
		}

		~ConstructorTerreno() {
		}

		/* Pre: FilasTerreno es la lista que proporciona la clase EntradaSalida.
		 *		Esta Lista contiene las cadenas extraidas del archivo terreno.
		 * Post: Instancia un objeto de la clase terreno y lo devuelve listo para la simulacion
		 */
		Terreno* ConstruirTerreno(Lista<std::string>* LineasTerreno) const {
			IteradorLista<std::string> iterador = LineasTerreno->iterador();

			/* El tama�o de la lista indica la cantidad de filas de la matriz */
			unsigned int Filas = LineasTerreno->tamanio();
			
			/* Tomo el numero de columnas de la matriz, (supongo que todas las lineas tiene igual largo
			 * Se toma el numero de columnas de la primer linea del archivo, si las lineas son diferentes
			 * luego en ConstruirLinea se "corrige" este problema */
			unsigned int Columnas = 0;
			if (iterador.tieneSiguiente())
				Columnas = iterador.get().length();

			/* Creo el Terreno */
			Terreno* terreno = new Terreno;
			terreno->setMatrizTerreno(this->ConstruirMatriz(Filas,Columnas));
			terreno->setDimensionFilas(Filas);
			terreno->setDimensionColumnas(Columnas);

			/* Completo la matriz */
			std::string LineaTerreno;
			unsigned int contadorFila = 0;
			bool HayHormiguero = false;

			while (iterador.tieneSiguiente()) {
				LineaTerreno = iterador.siguiente();
				this->ConstruirLinea(terreno, LineaTerreno, contadorFila, Columnas, HayHormiguero);
				contadorFila++;
			}
			/* Busca el hormiguero */
			terreno->BuscarHormiguero();

			/* Destruyo la lista */
			delete LineasTerreno;
			LineasTerreno = NULL;

			/* Devuelvo el terreno listo para la simulacion */
			return terreno;
		}

	private:

		/* Pre: Los valores de filas y columnas son los correctos para el terreno a construir
		 * Post: Crea una matriz de las dimensiones pasadas por parametro, lista para ser completada con los casilleros correspondientes al terreno
		 * */
		Matriz ConstruirMatriz(unsigned int filas, unsigned int columnas) const {
			Matriz matriz = new Casillero**[filas];

			for(unsigned int i = 0 ; i < filas ; i++)
				matriz[i] = new Casillero*[columnas];

			for (unsigned int i = 0 ; i < filas ; i++)
				for(unsigned int j = 0 ; j < columnas ; j++)
					matriz[i][j] = NULL;

			return matriz;
		}

		/* Pre: Matriz fue creada con ConstruirMatriz.
		 * Post: Instancia los casilleros correspondientes al terreno.
		 * 
		 * FilaAconstruir es la cadena con el detalle de los objetos a crear
		 * NumeroFila es el numero de fila de la matriz donde se crearan los objetos
		 * Columnas es la cantidad de columnas de la matriz
		 * HayHormiguero indica si ya se instancio un hormiguero, un ves creado el primer hormiguero, no se puede instanciar uno nuevo, asi logro que exista solo un hormiguero en el terreno 
		 */ 
		void ConstruirLinea(Terreno* terreno, std::string FilaAconstruir, unsigned int NumeroFila, unsigned int columnas, bool& HayHormiguero) const {

			char casillero;

			for(unsigned int posicion = 0; posicion < columnas ; posicion++) {

				/* Si la linea a contruir tiene un largo mayor a la cantidad de columnas, solo se toma en cuenta el largo de la cadena equivalente a la cantidad de columnas
				 * en caso que la linea sea menor a la cantidad de columnas, al pedirle a la columna una posicion que no existe, retornaria basura, para evitar esto, si la
				 * la linea es menor a las columnas, se completa con casilleros vacios */
				if (posicion < FilaAconstruir.length())
					casillero = FilaAconstruir[posicion];
				else
					casillero = '-';

				switch (casillero) {
					case '-': {
						terreno->setCasillero(new Casillero(),NumeroFila,posicion);
						break;
					}
					case 'H': {
						terreno->setCasillero(new Casillero(new Hormiga),NumeroFila,posicion);
						break;
					}
					case 'O': {
						if (!HayHormiguero) {
							terreno->setCasillero(new Casillero(new Hormiguero),NumeroFila,posicion);
							HayHormiguero = true;
						}
						else
							terreno->setCasillero(new Casillero(),NumeroFila,posicion);
						break;
					}
					case 'S': {
						terreno->setCasillero(new Casillero(new Semilla),NumeroFila,posicion);
						break;
					}
					case 'P': {
						terreno->setCasillero(new Casillero(new Piedra),NumeroFila,posicion);
						break;
					}
					case '1': {
						terreno->setCasillero(new Casillero(new Planta(1)),NumeroFila,posicion);
						break;
					}
					case '2': {
						terreno->setCasillero(new Casillero(new Planta(2)),NumeroFila,posicion);
						break;
					}
					case '3': {
						terreno->setCasillero(new Casillero(new Planta(3)),NumeroFila,posicion);
						break;
					}
					case '4': {
						terreno->setCasillero(new Casillero(new Planta(4)),NumeroFila,posicion);
						break;
					}
					case '5': {
						terreno->setCasillero(new Casillero(new Planta(5)),NumeroFila,posicion);
						break;
					}
					case '6': {
						terreno->setCasillero(new Casillero(new Planta(6)),NumeroFila,posicion);
						break;
					}
					case '7': {
						terreno->setCasillero(new Casillero(new Planta(7)),NumeroFila,posicion);
						break;
					}
					case '8': {
						terreno->setCasillero(new Casillero(new Planta(8)),NumeroFila,posicion);
						break;
					}
					case '9': {
						terreno->setCasillero(new Casillero(new Planta(9)),NumeroFila,posicion);
						break;
					}
					default: {
						terreno->setCasillero(new Casillero(),NumeroFila,posicion);
						break;
					}
				}
			}
		}

};

#endif /*__CONSTRUCTORTERRENO_H__*/
