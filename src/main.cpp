#include "Definiciones.h"
#include "Simulacion.h"

#include "archivoTexto.h"

#include <stdlib.h>

int main(int argc, char **argv) {

	Simulacion SimulacionHormigas("configuracion.txt");

	SimulacionHormigas.Ejecutar();

	return 0;
}
