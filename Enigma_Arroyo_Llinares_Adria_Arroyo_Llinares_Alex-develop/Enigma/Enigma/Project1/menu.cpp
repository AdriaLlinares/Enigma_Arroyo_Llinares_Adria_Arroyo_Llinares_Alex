#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#include "menu.h"
#include "utils.h"
#include "rotor.h"
#include "enigma.h"

// Muestra el menu principal
void mostrarMenu() {
    std::cout << "\n¡AVISO!\n";
    std::cout << "La maquina enigma solo funciona con letras.\n";
    std::cout << "Los numeros, espacios o caracteres especiales seran eliminados automaticamente.\n";
    std::cout << "\n--- ENIGMA ---\n";
    std::cout << "1. Cifrar mensaje\n";
    std::cout << "2. Descifrar mensaje\n";
    std::cout << "3. Editar rotores\n";
    std::cout << "4. Salir\n";
    std::cout << "Selecciona una opcion: ";
}

// Funcion para cifrar
void opcionCifrar() {
    Rotor r1, r2, r3;

    // Cargar rotores
    bool okR1 = cargarRotor("Rotor1.txt", r1);
    bool okR2 = cargarRotor("Rotor2.txt", r2);
    bool okR3 = cargarRotor("Rotor3.txt", r3);

    //Debug para comprovar si se han cargado correctamente los rotores
    if (!okR1) {
        std::cout << "[ERROR] No se pudo cargar Rotor1.txt\n";
        return;
    }
    if (!okR2) {
        std::cout << "[ERROR] No se pudo cargar Rotor2.txt\n";
        return;
    }
    if (!okR3) {
        std::cout << "[ERROR] No se pudo cargar Rotor3.txt\n";
        return;
    }

    std::cout << "Rotores cargados correctamente\n";

    // Pedir posicion inicial
    char letra1, letra2, letra3;
    std::cout << "Posicion inicial (ej: A B C): ";
    std::cin >> letra1 >> letra2 >> letra3;

    int pos1 = letra1 - 'A';
    int pos2 = letra2 - 'A';
    int pos3 = letra3 - 'A';
   
    // Leer mensaje
    std::string texto, linea;
    std::ifstream archivoMensaje("Missatge.txt");
    if (!archivoMensaje.is_open()) {
        // Si el archivo no existe se crea.
        std::cout << "El archivo \"Missatge.txt\" no existe o esta vacio.\n";
        std::cout << "Escribe el mensaje que deseas cifrar: ";
        std::cin.ignore();
        getline(std::cin, texto);
        std::ofstream crearArchivo("Missatge.txt");
        crearArchivo << texto;
        crearArchivo.close();
        std::cout << "Archivo \"Missatge.txt\" creado correctamente\n";
    }
    else {
        // Si existe lo leemos
        while (getline(archivoMensaje, linea)) {
            texto += linea;
        }
        archivoMensaje.close();
    }

    texto = procesarTexto(texto); // Elimina caracteres invalidos

    // Cifrado
    std::string cifrado = cifrar(texto, r1, r2, r3, pos1, pos2, pos3);

    // Guardar en archivo con espacios cada 5 letras
    std::ofstream archivoCifrado("Xifrat.txt");
    for (int i = 0; i < cifrado.length(); i++) {
        archivoCifrado << cifrado[i];
        if ((i + 1) % 5 == 0)
            archivoCifrado << " ";
    }
    archivoCifrado.close();

    std::cout << "¡Mensaje cifrado en \"Xifrat.txt\"!\n";

    Sleep(3500);
    system("cls");

}

// Funcion para descifrar
void opcionDescifrar() {
    Rotor r1, r2, r3;

    // Cargar rotores
    bool okR1 = cargarRotor("Rotor1.txt", r1);
    bool okR2 = cargarRotor("Rotor2.txt", r2);
    bool okR3 = cargarRotor("Rotor3.txt", r3);

	//Debug para comprovar si se han cargado correctamente los rotores
    if (!okR1){
        std::cout << "[ERROR] No se pudo cargar Rotor1.txt\n";
        return;
    }
    if (!okR2){
        std::cout << "[ERROR] No se pudo cargar Rotor2.txt\n";
        return;
    }
    if (!okR3){ 
        std::cout << "[ERROR] No se pudo cargar Rotor3.txt\n"; 
        return;
    }

    std::cout << "Rotores cargados correctamente\n";

    // Pedir posicion inicial
    char letra1, letra2, letra3;
    std::cout << "Posicio inicial (ex: A B C): ";
    std::cin >> letra1 >> letra2 >> letra3;

    int pos1 = letra1 - 'A';
    int pos2 = letra2 - 'A';
    int pos3 = letra3 - 'A';
    
    // Leer mensaje cifrado
    std::string texto, linea;
    std::ifstream mesnajeCifrado("Xifrat.txt");
    if (!mesnajeCifrado.is_open()) {
        // Si no existe se cifra el mensaje en texto claro para poder descifrarlo
        std::string mensaje;
        std::cout << "El archivo \"Xifrat.txt\" no existe o esta vacio.\n";
        std::cout << "Escribe el mensaje en texto claro que quieres cifrar: ";
        std::cin.ignore();
        getline(std::cin, mensaje);
        std::cout << "¡Mensaje creado con exito!\n";
        std::cout << "Cifrando mensaje...\n";
        std::string procesado = procesarTexto(mensaje);
        std::string cifrado = cifrar(procesado, r1, r2, r3, pos1, pos2, pos3);
        std::ofstream crearArchivo("Xifrat.txt");
        // Se hacen espacios cada 5 lineas para que sea mas legible
        for (int i = 0; i < (int)cifrado.length(); i++) {
            crearArchivo << cifrado[i];
            if ((i + 1) % 5 == 0) crearArchivo << " ";
        }
        crearArchivo.close();
        texto = cifrado;
        std::cout << "¡Mensaje cifrado!\n";
    }
    else {
        while (getline(mesnajeCifrado, linea)) {
            texto += linea;
        }
        mesnajeCifrado.close();
    }
    texto = procesarTexto(texto); // Elimina espacios y caracteres invalidos

    // Descifrar
    std::string descifrado = descifrar(texto, r1, r2, r3, pos1, pos2, pos3);

    // Guardar resultado
    std::ofstream mensajeDescifrado("Desxifrat.txt");
    mensajeDescifrado << descifrado;
    mensajeDescifrado.close();

    std::cout << "Mensaje descifrado guardado en \"Desxifrat.txt\"\n";
    Sleep(3500);
    system("cls");
}

// Funcion para editar rotors
void opcionEditar() {
    int rotorNum;
    std::cout << "Quin rotor vols editar (1-3)? ";
    std::cin >> rotorNum;

    if (rotorNum < 1 || rotorNum > 3) {
        std::cout << "¡Rotor invalido!\n";
        return;
    }

    std::string nuevaPermutacion;
    std::cout << "Introduce la nueva permutacion (26 letras: A-Z): ";
    std::cin >> nuevaPermutacion;

    if (!validarPermutacion(nuevaPermutacion)) {
        std::cout << "[ERROR] ¡Permutacion invalida!\n";
        return;
    }

    std::string nombre = "Rotor" + std::to_string(rotorNum) + ".txt";

    std::ofstream nuevoRotor(nombre);
    nuevoRotor << nuevaPermutacion << "\n"; // notch por defecto
    nuevoRotor.close();

    std::cout << "Rotor actualizado correctamente.\n";
    Sleep(3000);
    system("cls");
}
