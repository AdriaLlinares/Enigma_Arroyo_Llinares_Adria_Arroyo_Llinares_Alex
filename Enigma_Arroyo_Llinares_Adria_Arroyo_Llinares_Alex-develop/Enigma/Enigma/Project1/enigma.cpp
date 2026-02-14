#include "enigma.h"
// Esta funcion hace que las piezas giren
void avanzarRotors(int& r1, int& r2, int& r3) {
    r1++;
    // Esto lo que hace es que cuando el primer rotor se llene se introducira una letra en el segudno rotor y lo mismo con el tercero
    // hasta que esten todos llenos

    if (r1 == 26) {
        r1 = 0;
        r2++;

        if (r2 == 26) {
            r2 = 0;
            r3++;

            if (r3 == 26)
                r3 = 0;
        }
    }
}

char pasarRotor(char letra, const Rotor& rotor, int posicion) {

    // Calcula que letra esta reciviendo el conversor segun cuanto ha girado la letra.
    int index = (letra - 'A' + posicion) % 26;
    // Elije la letra que tiene escrita en esa posicion.
    char letraCifrada = rotor.permutacion[index];
    // Como el conversor sigue girando se tiene que ajustar la posicion.
    int resultado = (letraCifrada - 'A' - posicion + 26) % 26;

    return char(resultado + 'A');
}

char pasarRotorInverso(char letra, const Rotor& rotor, int posicion) {
    // Ajuste de entrada 
    int index = (letra - 'A' + posicion) % 26;
    // Busca quien tienne esa letra.
    int encontrado = rotor.permutacion.find(char(index + 'A'));
    // Ajusta la posicion
    int resultado = (encontrado - posicion + 26) % 26;

    return char(resultado + 'A');
}

std::string cifrar(const std::string& texto,Rotor& r1, Rotor& r2, Rotor& r3,int pos1, int pos2, int pos3) {

    std::string resultado = "";
    
    // Miramos el mensaje letra por letra
    for (char c : texto) {
        // Antes de cifrar los rotores giran
        avanzarRotors(pos1, pos2, pos3);

        // Entra en el 1 la salida del 1 entra al 2 y la salida del 2 al 3.
        c = pasarRotor(c, r1, pos1);
        c = pasarRotor(c, r2, pos2);
        c = pasarRotor(c, r3, pos3);

        // Se guarda la letra convertida en el resultado.
        resultado += c;
    }

    return resultado;
}

std::string descifrar(const std::string& texto,Rotor& r1, Rotor& r2, Rotor& r3,int pos1, int pos2, int pos3) {

    std::string resultado = "";

    // Miramos el mensaje letra por letra
    for (char c : texto) {

        // Lo mismo que antes pero al reves.
        avanzarRotors(pos1, pos2, pos3);

        c = pasarRotorInverso(c, r3, pos3);
        c = pasarRotorInverso(c, r2, pos2);
        c = pasarRotorInverso(c, r1, pos1);

        resultado += c;
    }

    return resultado;
}
