//
// Created by Elvis Adames and Priscila Ortega on 9/13/2025.
//

#ifndef AFNDtoAFD_H
#define AFNDtoAFD_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

// Representación de estados o conjuntos de estados del AFD
typedef set<int> AFDstate;

// Tabla de transiciones del AFND
struct AFNDtransition {
    int status;
    char symbol;
    set<int> destination;
};

// Tabla de transiciones del AFD
struct AFDtransition {
    AFDstate status;
    char symbol;
    AFDstate destination;
};

class AFNDtoAFD {
private:
    vector<int> AFNDstatus;
    vector<char> alphabet;
    vector<AFNDtransition> AFNDtable;
    vector<AFDtransition> AFDtable;
    vector<AFDstate> AFDstatus;
    int initialState;
    set<int> finalStatesAFND;
    set<AFDstate> finalStatesAFD;

public:
    void insertStatus();
    void defineAlphabet();
    void insertAFNDtransitions();
    void defineInitialState();
    void defineFinalStates();
    void transformToAFD();
    void showAFD();
    void showAFNDTable();
    bool validateAFND();

private:
    set<int> EpsilonClosure(const set<int>& states);
    set<int> move(const set<int>& states, char symbol);
    bool existingStatusAFD(const set<int>& status);
    string stateSetToString(const set<int>& stateSet);
    void determineFinalStatesAFD();
};

#endif