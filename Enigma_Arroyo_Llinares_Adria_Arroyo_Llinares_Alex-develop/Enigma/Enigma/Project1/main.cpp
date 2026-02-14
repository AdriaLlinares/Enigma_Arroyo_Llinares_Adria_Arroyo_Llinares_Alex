#include <iostream>
#include "menu.h"
#include <windows.h>


int main() {

    int opcio = 0;

    while (opcio != 4) {

        mostrarMenu();
        std::cin >> opcio;

        switch (opcio) {
        case 1: opcionCifrar(); break;
        case 2: opcionDescifrar(); break;
        case 3: opcionEditar(); break;
        case 4: std::cout << "Chau!\n"; break;
        default:
            std::cout << "¡Opcio no valida!\n";
            // Lo que hace es limpiar el cin debido a que si no lo vaciamos se queda registrado el caracter invalido
            // y entra en un bucle infinito.
            std::cin.clear();
            std::cin.ignore(100, '\n');
            Sleep(3000);
            system("cls");
        }
    }

    return 0;
}
