#include <iostream>
#include <fstream>
#include <string>

#include "Menu.h"
#include "Utils.h"
#include "Rotor.h"
#include "Enigma.h"

// Muestra el menú principal
void mostrarMenu() {
    std::cout << "\n¡AVISO!\n";
    std::cout << "La maquina enigma solo funciona con letras.\n";
    std::cout << "Los numeros, espacios o caracteres especiales seran eliminados automaticamente.\n";
    std::cout << "\n--- ENIGMA ---\n";
    std::cout << "1. Xifrar missatge\n";
    std::cout << "2. Desxifrar missatge\n";
    std::cout << "3. Editar rotors\n";
    std::cout << "4. Sortir\n";
    std::cout << "Selecciona una opcio: ";
}

// Función para cifrar
void opcionCifrar() {
    Rotor r1, r2, r3;

    // Cargar rotors
    bool ok1 = cargarRotor("Rotor1.txt", r1);
    bool ok2 = cargarRotor("Rotor2.txt", r2);
    bool ok3 = cargarRotor("Rotor3.txt", r3);

    if (!ok1) std::cout << "[ERROR] No se pudo cargar Rotor1.txt\n";
    if (!ok2) std::cout << "[ERROR] No se pudo cargar Rotor2.txt\n";
    if (!ok3) std::cout << "[ERROR] No se pudo cargar Rotor3.txt\n";
    if (!ok1 || !ok2 || !ok3) return;

    std::cout << "[OK] Rotors cargados correctamente\n";

    // Pedir posición inicial
    char l1, l2, l3;
    std::cout << "Posicio inicial (ex: A B C): ";
    std::cin >> l1 >> l2 >> l3;

    int pos1 = l1 - 'A';
    int pos2 = l2 - 'A';
    int pos3 = l3 - 'A';

    // Leer mensaje
    std::ifstream in("Missatge.txt");
    if (!in.is_open()) {
        std::cout << "[ERROR] No existe Missatge.txt\n";
        return;
    }

    std::string texto, linea;
    while (getline(in, linea))
        texto += linea;

    in.close();

    texto = procesarTexto(texto); // elimina caracteres inválidos

    // Cifrar
    std::string cifrado = cifrar(texto, r1, r2, r3, pos1, pos2, pos3);

    // Guardar en archivo con espacios cada 5 letras
    std::ofstream out("Xifrat.txt");
    for (int i = 0; i < cifrado.length(); i++) {
        out << cifrado[i];
        if ((i + 1) % 5 == 0)
            out << " ";
    }
    out.close();

    std::cout << "[OK] Missatge xifrat a Xifrat.txt\n";
}

// Función para descifrar
void opcionDescifrar() {
    Rotor r1, r2, r3;

    // Cargar rotors
    bool ok1 = cargarRotor("Rotor1.txt", r1);
    bool ok2 = cargarRotor("Rotor2.txt", r2);
    bool ok3 = cargarRotor("Rotor3.txt", r3);

	//Debug para comprovar si se han cargado correctamente los rotores
    if (!ok1) std::cout << "[ERROR] No se pudo cargar Rotor1.txt\n";
    if (!ok2) std::cout << "[ERROR] No se pudo cargar Rotor2.txt\n";
    if (!ok3) std::cout << "[ERROR] No se pudo cargar Rotor3.txt\n";
    if (!ok1 || !ok2 || !ok3) return;

    std::cout << "[OK] Rotors cargados correctamente\n";

    // Pedir posición inicial
    char l1, l2, l3;
    std::cout << "Posicio inicial (ex: A B C): ";
    std::cin >> l1 >> l2 >> l3;

    int pos1 = l1 - 'A';
    int pos2 = l2 - 'A';
    int pos3 = l3 - 'A';

    // Leer mensaje cifrado
    std::ifstream in("Xifrat.txt");
    if (!in.is_open()) {
        std::cout << "[ERROR] No existe Xifrat.txt\n";
        return;
    }

    std::string texto, linea;
    while (getline(in, linea))
        texto += linea;

    in.close();

    texto = procesarTexto(texto); // elimina espacios y caracteres inválidos

    // Descifrar
    std::string descifrado = descifrar(texto, r1, r2, r3, pos1, pos2, pos3);

    // Guardar resultado
    std::ofstream out("Desxifrat.txt");
    out << descifrado;
    out.close();

    std::cout << "[OK] Missatge desxifrat a Desxifrat.txt\n";
}

// Función para editar rotors
void opcionEditar() {
    int rotorNum;
    std::cout << "Quin rotor vols editar (1-3)? ";
    std::cin >> rotorNum;

    if (rotorNum < 1 || rotorNum > 3) {
        std::cout << "Rotor invalid.\n";
        return;
    }

    std::string nuevaPermutacion;
    std::cout << "Introdueix nova permutacio (26 lletres A-Z): ";
    std::cin >> nuevaPermutacion;

    if (!validarPermutacion(nuevaPermutacion)) {
        std::cout << "[ERROR] Permutacio invalida.\n";
        return;
    }

    std::string nombre = "Rotor" + std::to_string(rotorNum) + ".txt";

    std::ofstream out(nombre);
    out << nuevaPermutacion << "\nZ"; // notch por defecto
    out.close();

    std::cout << "[OK] Rotor actualitzat correctament.\n";
}
