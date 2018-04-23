#ifndef __CONFIGURACION_H__
#define __CONFIGURACION_H__

#include "archivoTexto.h"
#include <stdlib.h>

/* Configuracion, extrae y guarda los datos provistos por el archivo de configuracion */

class Configuracion {

	private:

		unsigned int NumeroRondas;

		std::string PathArchivoTerreno;

		std::string PathArchivoResultado;

	public:

		/* Post: Extrae los parametros del archivo */
		Configuracion(std::string pathArchivoConfiguracion) {
			this->ExtraerDatos(pathArchivoConfiguracion);
		}

		~Configuracion() {
		}

		unsigned int getNumeroRondas() const {
			return this->NumeroRondas;
		}

		std::string getPathArchivoTerreno() const {
			return this->PathArchivoTerreno;
		}

		std::string getPathArchivoResultado() const {
			return this->PathArchivoResultado;
		}		

	private:

		/* Post: Extraido el numero de rondas de la simulacion, se guarda el valor
		 * 		Si el valor es negativo, se le asigna 0 */
		void setCantidadRondas(unsigned int numeroRondas) {
			if (numeroRondas < 0)
				this->NumeroRondas = 0;
			else
				this->NumeroRondas = numeroRondas;
		}

		void setPathArchivoTerreno(std::string path) {
			this->PathArchivoTerreno = path;
		}

		void setPathArchivoResultado(std::string path) {
			this->PathArchivoResultado = path;
		}

		void ExtraerDatos(std::string pathArchivoConfiguracion) {
			ArchivoTexto archivoConfiguracion;
			
			std::string pathArchivoTerreno;
			std::string pathArchivoResultado;
			std::string numeroRondasStr;
			std::string cadenaLeida;
			
			int numeroRondas;

			crear(archivoConfiguracion,pathArchivoConfiguracion);

			while ( leerLinea(archivoConfiguracion,cadenaLeida) ) {
				if ( cadenaLeida.find(RONDAS) != std::string::npos )
					numeroRondasStr = cadenaLeida.erase( 0 , cadenaLeida.find('=')+1 );
				else {
					if ( cadenaLeida.find(TERRENO) != std::string::npos )
						pathArchivoTerreno = cadenaLeida.erase( 0 , cadenaLeida.find('=')+1 );
					else
						if ( cadenaLeida.find(RESULTADO) != std::string::npos )
							pathArchivoResultado = cadenaLeida.erase( 0 , cadenaLeida.find('=')+1 );
				}
			}

			destruir(archivoConfiguracion);

			numeroRondas = atoi(numeroRondasStr.c_str());

			this->setCantidadRondas(numeroRondas);
			this->setPathArchivoTerreno(pathArchivoTerreno);
			this->setPathArchivoResultado(pathArchivoResultado);
		}

};

#endif /*__CONFIGURACION_H__*/
