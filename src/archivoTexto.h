#ifndef __ARCHIVOTEXTO_H__
#define __ARCHIVOTEXTO_H__

#include <fstream>

typedef struct {
                         std::fstream  archivo;
}ArchivoTexto;

void crear( ArchivoTexto &archivoTexto , std::string nombre );

void destruir( ArchivoTexto &archivoTexto );

void escribirCaracter(ArchivoTexto &archivoTexto, char Caracter);

void escribirCadena(ArchivoTexto &archivoTexto, std::string Cadena);

void bajarDeLinea( ArchivoTexto &archivoTexto );

void tabular( ArchivoTexto &archivoTexto );

bool leerLinea( ArchivoTexto &archivoTexto, std::string &Cadena );

void irAlComienzo( ArchivoTexto &archivoTexto );

void irAlFinal( ArchivoTexto &archivoTexto );

#endif
