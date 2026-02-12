#include <fstream>
#include  "Rotor.h"


bool cargarRotor(const std::string& nombreArchivo, Rotor& nuevoRotor) {

	std::ifstream archivo(nombreArchivo);

	// Comprobar si el archivo existe
	if (!archivo.is_open()) {
		return false;
	}

	// Leer permutacion 
	if (!(archivo >> nuevoRotor.permutacion)) {
		return false;
	}
	// Leer letra de giro
	if (!(archivo >> nuevoRotor.letraDeGiro)) {
		return false;
	}

	archivo.close();
	return true;
}