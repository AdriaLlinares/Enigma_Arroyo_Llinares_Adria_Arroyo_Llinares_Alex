#include <iostream>
#include <fstream>
#include  "rotor.h"

bool validarPermutacion(const std::string& texto) {
	// Comprovamos si hay exactamente 26 letras.
	if (texto.length() != 26) {
		return false;
	}
	// Se crea una lista de 26 espacios que por decirlo de una manera no estan usados.
	bool letras[26] = { false };

	// Mirar uno por uno las letras del texto.
	for (int i = 0; i < 26; i++) {
		char letraActual = texto[i];
		// Se comprueba que la letra sea mayuscula.
		if (letraActual < 'A' || letraActual > 'Z') {
			return false;
		}
		// Convertimos la letra en un numero.
		int posicion = letraActual - 'A';

		// Comprovar si se estaba repitiendo la letra.
		if (letras[posicion] == true) {
			return false;
		}
		// Si no estaba devolvemos true a la posicionn de esa letra.
		letras[posicion] = true;
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


