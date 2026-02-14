#pragma once
#include <string>
struct Rotor {
	std::string permutacion; // 26 letras
	char letraDeGiro;	// letras de giro
};

bool cargarRotor(const std::string& nombreArchivo, Rotor& nuevoRotor);
bool validarPermutacion(const std::string& texto);
