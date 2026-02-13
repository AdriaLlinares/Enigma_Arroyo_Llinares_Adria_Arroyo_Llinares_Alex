#include <iostream>
#include "Menu.h"

int main() {

    int opcio = 0;

    while (opcio != 4) {

        mostrarMenu();
        std::cin >> opcio;

        switch (opcio) {
        case 1: opcionCifrar(); break;
        case 2: opcionDescifrar(); break;
        case 3: opcionEditar(); break;
        case 4: std::cout << "Chau\n"; break;
        default:
            std::cout << "Opcio no valida.\n";
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
    }

    return 0;
}
