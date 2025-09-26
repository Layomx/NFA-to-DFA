# NFA to DFA Converter

A C++ program for converting a Nondeterministic Finite Automaton (NFA, or "AFND" in Spanish) to a Deterministic Finite Automaton (DFA, or "AFD" in Spanish).

Variable names are in English. The project is organized into the following files:
- `AFNDtoAFD.cpp`
- `AFNDtoAFD.h`
- `main.cpp`

**Note:**  
- **AFND** stands for "Autómata Finito No Determinista" (Nondeterministic Finite Automaton).  
- **AFD** stands for "Autómata Finito Determinista" (Deterministic Finite Automaton).

---
## File Overview

### AFNDtoAFD.h

The main header file. It declares the `AFNDtoAFD` class and supporting data structures, providing the interface for converting an NFA to a DFA.

**Main components:**
- Typedefs and structs for representing states and transitions.
- The `AFNDtoAFD` class, which encapsulates the conversion logic.

**Purpose:**  
Defines the data structures and main class for the converter. Implementation is provided in `AFNDtoAFD.cpp`.

---

### AFNDtoAFD.cpp

Implements the logic for converting an NFA to a DFA. Provides an interactive console interface for defining the NFA, performing the conversion, and displaying the resulting DFA.

**Main functionalities:**
- `insertStatus()`: Input the set of NFA states.
- `defineAlphabet()`: Define the alphabet (set of symbols). Use `#` for epsilon transitions.
- `insertAFNDtransitions()`: Input the NFA transition table, including epsilon transitions.
- `defineInitialState()`: Set the initial state of the NFA.
- `defineFinalStates()`: Specify the set of final (accepting) states for the NFA.
- `showAFNDTable()`: Display the NFA transition table.
- `validateAFND()`: Check if the NFA is well defined.
- `EpsilonClosure(const set<int>& states)`: Compute the epsilon-closure of a set of states.
- `move(const set<int>& states, char symbol)`: Compute the set of states reachable via a specific symbol.
- `transformToAFD()`: Perform the subset construction algorithm to convert the NFA (with epsilon transitions) to a DFA.
- `determineFinalStatesAFD()`: Determine which DFA states are accepting, based on the original NFA's accepting states.
- `showAFD()`: Display the DFA's states, alphabet, initial state, final states, and transition table.
- `existingStatusAFD(const set<int>& status)`: Check if a DFA state (set of NFA states) already exists.
- `stateSetToString(const set<int>& stateSet)`: Utility function to convert a set of states to a string representation.

**Usage:**  
This file is designed for interactive use. You can modify or extend it for your own learning or to improve its functionality. This project was originally developed for a university course on formal languages, compilers, and automata, so while it may not be fully robust, it implements the core logic effectively.

---

### main.cpp

The entry point and user interface for the converter program. Provides a text-based menu that allows users to interactively define an NFA, perform the conversion, and display the resulting DFA.

**Main functionalities:**
- `showMenu()`: Display the main menu with options for each step of the conversion process.
- `showInstructions()`: Print instructions to guide the user through defining the automaton and using the converter.
- `main()`: The program's entry point. Initializes an `AFNDtoAFD` object, shows instructions, and repeatedly displays the menu and processes user input, calling the appropriate methods based on the user's choices.

---

## Compile
You can compile and run this project using any standard C++ compilter. Below are some instructions for compiling with g++ from the terminal.
1. Open a terminal
- Windows: Use Command Prompt, PowerShell or Windows Terminal. If you don't have `g++`, install MinGW or use WSL.
- Linux/macOS: Open your preferred terminal.
2. Navigate to the project directory
```cd path/to/NFA-to-DFA```
3. Compile the project
Run the following command to compile all `.cpp` fles and produce an executable named `nfa_to_da`: g++ -std=c++11 -o nfa_to_dfa main.cpp AFNDtoAFD.cpp
In Windows you should use `nfa_to_dfa.exe` as output name
4. Run the program
- Windows: nfa_to_dfa.exe
- Linux/macOS: ./nfa_to_dfa

Notes
- Make sure you have g++ installed. You can check by running g++ --version.
- If you use another compiler (like MSVC or Clang), adjust the command accordingly.
- If you use VS Code, you can also use the built-in terminal and tasks to automate compilation.

---

## Misc

This project was developed as a mini-project for my university course "Lenguajes Formales, Compiladores y Autómatas."  
I hope this implementation can help other students in similar courses, or anyone interested in automata theory.  
Feel free to use, modify, or extend this project for your own educational purposes or as a reference for your own implementations of this task.

---