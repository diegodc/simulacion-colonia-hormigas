#ifndef __TERRENO_H__
#define __TERRENO_H__

#include "Casillero.h"
#include "Hormiga.h"
#include "Hormiguero.h"
#include "Lista.h"

typedef Casillero*** Matriz;

class Terreno {

	private:

		Matriz MatrizTerreno;

		unsigned int DimensionFilas;

		unsigned int DimensionColumnas;

		Casillero* CasilleroHormiguero;

	public:

		Terreno() {
			/* Inicializo los valores */
			this->setDimensionFilas(0);
			this->setDimensionColumnas(0);
			this->setMatrizTerreno(NULL);
			this->setCasilleroHormiguero(NULL);
		}

		~Terreno() {
			this->DestruirObjetos();
			this->DestruirMatrizTerreno();
		}

		/* Pre: La lista retornada debera ser posteriormente detruida por otro objeto */
		Lista<Casillero*>* getHormigas() const {
			/* Creo una nueva lista */
			Lista<Casillero*>* hormigas = new Lista<Casillero*>;
			Casillero* casillero = NULL;

			/* Recorro el terreno y cuando encuentro una hormiga la agrego a la lista */
			for(unsigned int i = 0 ; i < this->getDimensionFilas() ; i++)
				for(unsigned int j = 0 ; j < this->getDimensionColumnas() ; j++) {
					casillero = this->getCasillero(i,j);
					if (casillero->TenesHormiga())
						hormigas->agregar(casillero);
				}
			return hormigas;
		}

		/* Pre: La lista retornada debera ser posteriormente detruida por otro objeto
		 * Post: Dado el casillero buscado, si este se encuentra en el terreno, se devuelve una lista con los casilleros contiguos al mismo */
		Lista<Casillero*>* getCasillerosContiguos(Casillero* casilleroBuscado) const {
			/* Creo una nueva lista */
			Lista<Casillero*>* CasillerosContiguos = new Lista<Casillero*>;

			/* Fila y Columna son las coordenas del casillero buscado */
			int fila;
			int columna;

			/* Tomo las Filas y Columnas Totales */
			int FilasTotales = this->getDimensionFilas();
			int ColumnasTotales = this->getDimensionColumnas();

			Casillero* casillero;
			bool encontrado = false;
			
			/* Recorro la matriz buscando el casillero */
			for(unsigned int i = 0 ; i < this->getDimensionFilas() ; i++)
				for(unsigned int j = 0 ; j < this->getDimensionColumnas() ; j++)
					if (this->getCasillero(i,j) == casilleroBuscado) {
						fila = i;
						columna = j;
						encontrado = true;
					}
			/* Si es encontro el casillero, recorro una sub-matriz de 3x3, comenzando en el casillero superior-izquierdo del buscado
			 * El casillero buscado es el casillero central de la sub-matriz, y no se agrega en la lista, de modo que en esta, solo quedan los casilleros aledaños */
			if (encontrado)
				for ( int x = fila -1 ; x < fila + 2 ; x++)
					for (int y = columna -1 ; y < columna + 2 ; y++)
						/* Solo tomo en cuenta las coordenadas que pertenecen a la matriz, de modo de no intentar extraer casilleros inexistentes */
						if (( x >= 0 ) && ( y >= 0 ) && ( x < FilasTotales ) && ( y < ColumnasTotales )) {
							casillero = this->getCasillero(x,y);
							if (casillero != casilleroBuscado)
								CasillerosContiguos->agregar(casillero);
						}
			return CasillerosContiguos;
		}

		Casillero* getCasilleroHormiguero() const {
			return this->CasilleroHormiguero;
		}

		unsigned int getDimensionFilas() const {
			return this->DimensionFilas;
		}

		unsigned int getDimensionColumnas() const {
			return this->DimensionColumnas;
		}

		char getSalida(unsigned int fila, unsigned int columna) const {
			/* Dada la coordenada, el terreno le pide al casillero correspondiente su salida */
			return this->getCasillero(fila,columna)->getSalida();
		}

	private:

		Matriz getMatrizTerreno() const {
			return this->MatrizTerreno;
		}

		Casillero* getCasillero(unsigned int fila, unsigned int columna) const {
			/* Dada la coordenada, se devuelve el casillero */
			if (( fila >= 0 ) && ( columna >= 0 ) && ( fila < this->getDimensionFilas() ) && ( columna < this->getDimensionColumnas() ))
				return this->getMatrizTerreno()[fila][columna];
			else
				/* Si el casillero no existe, retorna NULL */
				return NULL;
		}

		void BuscarHormiguero() {
			Casillero* hormiguero = NULL;
			/* Recorro la matriz buscando un hormiguero */
			for(unsigned int i = 0 ; i < this->getDimensionFilas() ; i++)
				for(unsigned int j = 0 ; j < this->getDimensionColumnas() ; j++) {
					hormiguero = this->getCasillero(i,j);
					/* Si lo encuentro, guardo el puntero */
					if (hormiguero->TenesHormiguero())
						this->setCasilleroHormiguero(hormiguero);
				}
		}

		void DestruirObjetos() {
			for (unsigned int i = 0; i < this->getDimensionFilas(); i++) 
				for (unsigned int j = 0; j < this->getDimensionColumnas(); j++)
					if (this->getCasillero(i,j) != NULL) {
						delete this->getCasillero(i,j);
						this->setCasillero(NULL,i,j);
					}
		}

		void DestruirMatrizTerreno() {
			for (unsigned int i = 0; i < this->getDimensionFilas(); i++)
				delete[] this->getMatrizTerreno()[i];

			delete[] this->getMatrizTerreno();

			this->setMatrizTerreno(NULL);
			this->setDimensionFilas(0);
			this->setDimensionColumnas(0);
		}

		void setMatrizTerreno(Matriz matrizTerreno) {
			this->MatrizTerreno = matrizTerreno;
		}

		void setCasillero(Casillero* casillero, unsigned int fila, unsigned int columna) {
			/* Pasados el puntero al casillero, y las coordenadas si estas son validas, se setea el casillero en la posicion */ 
			if (( fila >= 0 ) && ( columna >= 0 ) && ( fila < this->getDimensionFilas() ) && ( columna < this->getDimensionColumnas() ))
				this->getMatrizTerreno()[fila][columna] = casillero;
		}

		void setCasilleroHormiguero(Casillero* casilleroHormiguero) {
			this->CasilleroHormiguero = casilleroHormiguero;
		}

		void setDimensionFilas(unsigned int dimensionFilas) {
			if (dimensionFilas > 0)
				this->DimensionFilas = dimensionFilas;
			else
				this->DimensionFilas = 0;
		}

		void setDimensionColumnas(unsigned int dimensionColumnas) {
			if (dimensionColumnas > 0)
				this->DimensionColumnas = dimensionColumnas;
			else
				this->DimensionColumnas = 0;
		}

		/* La clase ConstructorTerreno tiene acceso a todos los metodos del Terreno, para asi poder contruirlo */
		friend class ConstructorTerreno;

};

#endif /*_TERRENO_H__*/
