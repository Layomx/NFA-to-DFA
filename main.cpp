#include "AFNDtoAFD.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>

using namespace std;

void showMenu() {
    cout << "\n===============================================\n";
    cout << "          CONVERSOR AFND a AFD               \n";
    cout << "===============================================\n";
    cout << "1. Ingresar estados del AFND\n";
    cout << "2. Definir alfabeto\n";
    cout << "3. Definir estado inicial\n";
    cout << "4. Definir estados finales\n";
    cout << "5. Ingresar transiciones AFND\n";
    cout << "6. Mostrar AFND actual\n";
    cout << "7. Convertir a AFD\n";
    cout << "8. Mostrar AFD resultante\n";
    cout << "9. Salir\n";
    cout << "===============================================\n";
    cout << "Seleccione una opcion: ";
}

void showInstructions() {
    cout << "\n=== INSTRUCCIONES DE USO ===\n";
    cout << "1. Primero ingrese los estados del AFND\n";
    cout << "2. Defina el alfabeto (use '#' para epsilon)\n";
    cout << "3. Defina el estado inicial\n";
    cout << "4. Defina los estados finales\n";
    cout << "5. Ingrese las transiciones del AFND\n";
    cout << "6. Convierta a AFD\n";
    cout << "7. Visualice el resultado\n";
    cout << "\nEjemplo de alfabeto: {0, 1} o {a, b}\n";
    cout << "Para transiciones epsilon use el símbolo '#'\n";
    cout << "============================\n";
}

int main() {
    // Configura la consola para UTF-8
    // _setmode(_fileno(stdout), _O_U16TEXT);

    AFNDtoAFD conversor;
    int option;

    cout << "¡Bienvenido al Conversor AFND a AFD!\n";
    showInstructions();

    do {
        showMenu();
        cin >> option;

        switch (option) {
            case 1:
                conversor.insertStatus();
                break;
            case 2:
                conversor.defineAlphabet();
                break;
            case 3:
                conversor.defineInitialState();
                break;
            case 4:
                conversor.defineFinalStates();
                break;
            case 5:
                conversor.insertAFNDtransitions();
                break;
            case 6:
                conversor.showAFNDTable();
                break;
            case 7:
                conversor.transformToAFD();
                break;
            case 8:
                conversor.showAFD();
                break;
            case 9:
                cout << "\n¡Gracias por usar el conversor AFND a AFD!\n";
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "\nOpcion no válida. Por favor intente de nuevo.\n";
                break;
        }

        if (option != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (option != 9);

    return 0;
}