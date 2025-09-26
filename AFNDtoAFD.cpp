//
// Created by Elvis Adames and Priscila Ortega on 9/13/2025.
//

#include "AFNDtoAFD.h"
#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

void AFNDtoAFD::insertStatus() {
    cout << "\n--- INGRESE LOS ESTADOS DEL AFND ---\n";
    cout << "Ingrese los estados (numeros enteros). Ingrese -1 para terminar:\n";

    int status;
    while (true) {
        cout << "Estado: ";
        cin >> status;

        if (status == -1) break;

        // Verifica si el estado ya existe
        if (find(AFNDstatus.begin(), AFNDstatus.end(), status) != AFNDstatus.end()) {
            cout << "El estado " << status << " ya existe\n";
        } else {
            AFNDstatus.push_back(status);
            cout << "Estado " << status << " agregado.\n";
        }
    }

    if (AFNDstatus.empty()) {
        cout << "No se ingresaron estados válidos.\n";
        return;
    }

    // Ordenar estados para mejor presentación
    sort(AFNDstatus.begin(), AFNDstatus.end());

    cout << "Estados ingresados: {";
    for (int i = 0; i < AFNDstatus.size(); i++) {
        if (i > 0) cout << ", ";
        cout << AFNDstatus[i];
    }
    cout << "}\n";
}

void AFNDtoAFD::defineAlphabet() {
    cout << "\n--- DEFINIR ALFABETO ---\n";
    cout << "Ingrese los simbolos del alfabeto. Ingrese '!' para terminar:\n";
    cout << "Nota: Para epsilon use '#'\n";

    char symbol;
    while (true) {
        cout << "Simbolo: ";
        cin >> symbol;

        if (symbol == '!') break;

        if (find(alphabet.begin(), alphabet.end(), symbol) != alphabet.end()) {
            cout << "El simbolo '" << symbol << "' ya existe.\n";
        } else {
            alphabet.push_back(symbol);
            cout << "Simbolo '" << symbol << "' agregado.\n";
        }
    }

    if (alphabet.empty()) {
        cout << "No se definio ningun simbolo en el alfabeto.\n";
        return;
    }

    cout << "Alfabeto definido: {";
    for (int i = 0; i < alphabet.size(); i++) {
        if (i > 0) cout << ", ";
        cout << alphabet[i];
    }
    cout << "}\n";
}

void AFNDtoAFD::insertAFNDtransitions() {
    cout << "\n--- INGRESAR TRANSICIONES AFND ---\n";
    cout << "Formato: estado_actual símbolo estado_destino\n";
    cout << "Para epsilon use '#'\n";
    cout << "Ingrese -1 para terminar\n";

    int currentStatus, destinationState;
    char symbol;

    while (true) {
        cout << "Transicion: ";
        cin >> currentStatus;

        if (currentStatus == -1) break;

        cin >> symbol >> destinationState;

        // Validaciones necesarias
        if (find(AFNDstatus.begin(), AFNDstatus.end(), currentStatus) == AFNDstatus.end()) {
            cout << "Error: Estado actual " << currentStatus << " no existe.\n";
            continue;
        }

        if (symbol != '#' && find(alphabet.begin(), alphabet.end(), symbol) == alphabet.end()) {
            cout << "Error: Símbolo '" << symbol << "' no está en el alfabeto.\n";
            continue;
        }

        if (find(AFNDstatus.begin(), AFNDstatus.end(), destinationState) == AFNDstatus.end()) {
            cout << "Error: Estado destino " << destinationState << " no existe.\n";
            continue;
        }

        // Buscar transiciones existentes
        bool existingTransition = false;
        for (auto& trans : AFNDtable) {
            if (trans.status == currentStatus && trans.symbol == symbol) {
                trans.destination.insert(destinationState);
                existingTransition = true;
                cout << "Destino agregado a transición existente.\n";
                break;
            }
        }

        // Crear una nueva transición si no existe
        if (!existingTransition) {
            AFNDtransition newTrans;
            newTrans.status = currentStatus;
            newTrans.symbol = symbol;
            newTrans.destination.insert(destinationState);
            AFNDtable.push_back(newTrans);
            cout << "Nueva transicion creada.\n";
        }
    }

    showAFNDTable();
}

void AFNDtoAFD::defineInitialState() {
    cout << "\n--- DEFINIR ESTADO INICIAL ---\n";
    cout << "Estados disponibles: ";
    for (int state : AFNDstatus) {
        cout << state << " ";
    }
    cout << "\nIngrese el estado inicial: ";

    while (true) {
        cin >> initialState;
        if (find(AFNDstatus.begin(), AFNDstatus.end(), initialState) != AFNDstatus.end()) {
            cout << "Estado inicial definido: " << initialState << "\n";
            break;
        } else {
            cout << "Estado no válido. Ingrese un estado de la lista: ";
        }
    }
}

void AFNDtoAFD::defineFinalStates() {
    cout << "\n--- DEFINIR ESTADOS FINALES ---\n";
    cout << "Estados disponibles: ";
    for (int state : AFNDstatus) {
        cout << state << " ";
    }
    cout << "\nIngrese los estados finales (ingrese -1 para terminar):\n";

    int state;
    while (true) {
        cout << "Estado final: ";
        cin >> state;

        if (state == -1) break;

        if (find(AFNDstatus.begin(), AFNDstatus.end(), state) != AFNDstatus.end()) {
            finalStatesAFND.insert(state);
            cout << "Estado final " << state << " agregado.\n";
        } else {
            cout << "Estado no válido.\n";
        }
    }

    cout << "Estados finales: {";
    for (auto it = finalStatesAFND.begin(); it != finalStatesAFND.end(); ++it) {
        if (it != finalStatesAFND.begin()) cout << ", ";
        cout << *it;
    }
    cout << "}\n";
}

void AFNDtoAFD::showAFNDTable() {
    cout << "\n--- TABLA DE TRANSICIONES AFND ---\n";
    if (AFNDtable.empty()) {
        cout << "No hay transiciones definidas.\n";
        return;
    }

    for (const auto& trans : AFNDtable) {
        cout << "δ(" << trans.status << ", ";
        if (trans.symbol == '#') {
            cout << "ε";
        } else {
            cout << trans.symbol;
        }
        cout << ") = {";
        for (auto it = trans.destination.begin(); it != trans.destination.end(); it++) {
            if (it != trans.destination.begin()) cout << ", ";
            cout << *it;
        }
        cout << "}\n";
    }
}

bool AFNDtoAFD::validateAFND() {
    if (AFNDstatus.empty()) {
        cout << "Error: No se han definido estados.\n";
        return false;
    }
    if (alphabet.empty()) {
        cout << "Error: No se ha definido el alfabeto.\n";
        return false;
    }
    if (AFNDtable.empty()) {
        cout << "Error: No se han definido transiciones.\n";
        return false;
    }
    if (find(AFNDstatus.begin(), AFNDstatus.end(), initialState) == AFNDstatus.end()) {
        cout << "Error: No se ha definido un estado inicial valido.\n";
        return false;
    }
    return true;
}

set<int> AFNDtoAFD::EpsilonClosure(const set<int>& states) {
    set<int> closure = states;
    queue<int> processingQueue;

    // Agregar todos los estados iniciales a la cola
    for (int state : states) {
        processingQueue.push(state);
    }

    while (!processingQueue.empty()) {
        int currentState = processingQueue.front();
        processingQueue.pop();

        // Buscar transiciones epsilon desde el estado actual
        for (const auto& trans : AFNDtable) {
            if (trans.status == currentState && trans.symbol == '#') {
                for (int destination : trans.destination) {
                    if (closure.insert(destination).second) {
                        processingQueue.push(destination);
                    }
                }
            }
        }
    }
    return closure;
}

set<int> AFNDtoAFD::move(const set<int>& states, char symbol) {
    set<int> result;

    for (int state : states) {
        for (const auto& trans : AFNDtable) {
            if (trans.status == state && trans.symbol == symbol) {
                result.insert(trans.destination.begin(), trans.destination.end());
            }
        }
    }
    return result;
}

void AFNDtoAFD::transformToAFD() {
    cout << "\n--- CONVERSIÓN AFND a AFD ---\n";

    if (!validateAFND()) {
        return;
    }

    // Limpiar datos anteriores del AFD
    AFDstatus.clear();
    AFDtable.clear();
    finalStatesAFD.clear();

    // Estado inicial del AFD = clausura epsilon del estado inicial AFND
    set<int> q0 = EpsilonClosure({initialState});
    AFDstatus.push_back(q0);

    queue<set<int>> unprocessed;
    unprocessed.push(q0);

    cout << "Estado inicial AFD: " << stateSetToString(q0) << "\n";

    while (!unprocessed.empty()) {
        set<int> currentState = unprocessed.front();
        unprocessed.pop();

        cout << "Procesando estado: " << stateSetToString(currentState) << "\n";

        for (char symbol : alphabet) {
            if (symbol == '#') continue; // Saltar epsilon para AFD

            // Calcular move(currentState, symbol)
            set<int> moveResult = move(currentState, symbol);

            if (!moveResult.empty()) {
                // Calcular clausura epsilon del resultado del move
                set<int> newState = EpsilonClosure(moveResult);

                // Verificar si es un estado nuevo
                if (!existingStatusAFD(newState)) {
                    AFDstatus.push_back(newState);
                    unprocessed.push(newState);
                    cout << "  Nuevo estado encontrado: " << stateSetToString(newState)
                         << " con símbolo '" << symbol << "'\n";
                }

                // Agregar transición a la tabla AFD
                AFDtransition transAFD;
                transAFD.status = currentState;
                transAFD.symbol = symbol;
                transAFD.destination = newState;
                AFDtable.push_back(transAFD);
            }
        }
    }

    // Determinar estados finales del AFD
    determineFinalStatesAFD();

    cout << "\nConversión completada. Se generaron " << AFDstatus.size() << " estados AFD.\n";
}

void AFNDtoAFD::determineFinalStatesAFD() {
    for (const auto& afdState : AFDstatus) {
        // Un estado AFD es final si contiene al menos un estado final del AFND
        for (int afndFinalState : finalStatesAFND) {
            if (afdState.find(afndFinalState) != afdState.end()) {
                finalStatesAFD.insert(afdState);
                break;
            }
        }
    }
}

void AFNDtoAFD::showAFD() {
    cout << "\n--- AUTÓMATA FINITO DETERMINISTA (AFD) ---\n";

    if (AFDtable.empty()) {
        cout << "No hay AFD generado. Ejecute primero la conversión.\n";
        return;
    }

    // Mostrar componentes del AFD
    cout << "Estados: {";
    for (int i = 0; i < AFDstatus.size(); i++) {
        if (i > 0) cout << ", ";
        cout << stateSetToString(AFDstatus[i]);
    }
    cout << "}\n";

    cout << "Alfabeto: {";
    for (int i = 0; i < alphabet.size(); i++) {
        if (alphabet[i] != '#') {
            if (i > 0) cout << ", ";
            cout << alphabet[i];
        }
    }
    cout << "}\n";

    cout << "Estado inicial: " << stateSetToString(AFDstatus[0]) << "\n";

    cout << "Estados finales: {";
    for (auto it = finalStatesAFD.begin(); it != finalStatesAFD.end(); ++it) {
        if (it != finalStatesAFD.begin()) cout << ", ";
        cout << stateSetToString(*it);
    }
    cout << "}\n";

    cout << "\n--- TABLA DE TRANSICIONES AFD ---\n";

    // Encabezado
    cout << left << setw(15) << "Estado";
    for (char symbol : alphabet) {
        if (symbol != '#') {
            cout << setw(15) << symbol;
        }
    }
    cout << endl;

    cout << string(15 + alphabet.size() * 15, '-') << endl;

    // Para cada estado AFD, mostrar sus transiciones
    for (const auto& state : AFDstatus) {
        cout << left << setw(15) << stateSetToString(state);

        // Mostrar transiciones para cada símbolo
        for (char symbol : alphabet) {
            if (symbol == '#') continue;

            bool found = false;
            for (const auto& trans : AFDtable) {
                if (trans.status == state && trans.symbol == symbol) {
                    cout << setw(15) << stateSetToString(trans.destination);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << setw(15) << "-";
            }
        }
        cout << endl;
    }
}

bool AFNDtoAFD::existingStatusAFD(const set<int>& status) {
    for (const auto& existingState : AFDstatus) {
        if (existingState == status) {
            return true;
        }
    }
    return false;
}

string AFNDtoAFD::stateSetToString(const set<int>& stateSet) {
    string result = "{";
    for (auto it = stateSet.begin(); it != stateSet.end(); ++it) {
        if (it != stateSet.begin()) result += ",";
        result += to_string(*it);
    }
    result += "}";
    return result;
}