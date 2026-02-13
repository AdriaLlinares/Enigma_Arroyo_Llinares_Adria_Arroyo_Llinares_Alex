#include "Enigma.h"

void avanzarRotors(int& r1, int& r2, int& r3) {
    r1++;

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

    int index = (letra - 'A' + posicion) % 26;
    char letraCifrada = rotor.permutacion[index];

    int resultado = (letraCifrada - 'A' - posicion + 26) % 26;

    return char(resultado + 'A');
}

char pasarRotorInverso(char letra, const Rotor& rotor, int posicion) {

    int index = (letra - 'A' + posicion) % 26;

    int encontrado = rotor.permutacion.find(char(index + 'A'));

    int resultado = (encontrado - posicion + 26) % 26;

    return char(resultado + 'A');
}

std::string cifrar(const std::string& texto,
    Rotor& r1, Rotor& r2, Rotor& r3,
    int pos1, int pos2, int pos3) {

    std::string resultado = "";

    for (char c : texto) {

        avanzarRotors(pos1, pos2, pos3);

        c = pasarRotor(c, r1, pos1);
        c = pasarRotor(c, r2, pos2);
        c = pasarRotor(c, r3, pos3);

        resultado += c;
    }

    return resultado;
}

std::string descifrar(const std::string& texto,
    Rotor& r1, Rotor& r2, Rotor& r3,
    int pos1, int pos2, int pos3) {

    std::string resultado = "";

    for (char c : texto) {

        avanzarRotors(pos1, pos2, pos3);

        c = pasarRotorInverso(c, r3, pos3);
        c = pasarRotorInverso(c, r2, pos2);
        c = pasarRotorInverso(c, r1, pos1);

        resultado += c;
    }

    return resultado;
}
