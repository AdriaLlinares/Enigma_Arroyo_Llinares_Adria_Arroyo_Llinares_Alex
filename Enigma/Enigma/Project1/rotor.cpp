#include <iostream>
#include <fstream>
#include  "Rotor.h"

bool validarPermutacion(const std::string& p) {
	if (p.length() != 26) return false;

	bool letras[26] = { false };

	for (char c : p) {
		if (c < 'A' || c > 'Z') return false;

		int index = c - 'A';
		if (letras[index]) return false; // repetida

		letras[index] = true;
	}
	return true;
}




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

	if (!validarPermutacion(nuevoRotor.permutacion)) {
		return false;
	}

	// Leer letra de giro
	if (!(archivo >> nuevoRotor.letraDeGiro)) {
		nuevoRotor.letraDeGiro = 'Z';
	}


	archivo.close();
	return true;
}


