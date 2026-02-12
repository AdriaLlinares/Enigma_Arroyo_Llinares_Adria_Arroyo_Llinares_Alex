#include "Utils.h"

std::string procesarTexto(std::string texto) {
	std::string resultado = "";
	
	for (int i = 0; i < texto.length(); i++) {
		char letra = texto[i];
		// Comprobar si la letra es minuscula
		if (letra >= 97 && letra <= 122) {
			resultado += char(letra - 32); // En caso de serlo se transforma a mayuscula
		
		}// Si es mayuscula se queda tal y como estaba
		else if (letra >= 65 && letra <= 90) {
			resultado += letra;
		}
	}
	return resultado;
}