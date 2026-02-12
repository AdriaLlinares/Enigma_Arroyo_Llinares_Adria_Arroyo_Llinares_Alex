#include <iostream>
#include <string>
#include "Utils.h"
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

int main() {
    std::string prueba = "Hola mundo 123!";
    std::string resultado = procesarTexto(prueba);
    std::cout << "Original: " << prueba << "\n";
    std::cout << "Nuevo: " << resultado;


    int opcio = 0;
    while (opcio != 4) {
        mostrarMenu();
        std::cin >> opcio;

        switch (opcio) {
        case 1:
            break; // funcio de xifrar
        case 2:
            break; // funcio de desxifrar
        case 3: 
            break; // funcio de editar
        case 4: 
            std::cout << "Chau\n"; 
            break;
        default: 
            std::cout << "Opcio no valida, intenta-ho de nou.\n";
            std::cin.clear();           /* Amb aquesta funcio el que faig es netejar el cin perque en cas de que el valor introduit no sigui un numero el programa 
            no entri a un bucle infinit */
            std::cin.ignore(100, '\n');            
            break;
        }
    }
    
    return 0;
}