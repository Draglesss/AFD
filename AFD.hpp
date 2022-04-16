#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <cassert>
#pragma once
using namespace std;
//* a transition is composed of a state,
//* a symbol
//* and a next state
template <typename T> 
int size(T in) {
    return sizeof(in) / sizeof(in[0]);
};
class transition {
    int state;
    char symbol;
    int nextState;
public:
    transition(int state, char symbol, int nextState) {
        this->state = state;
        this->symbol = symbol;
        this->nextState = nextState;
    }
    transition() {
        this->state = 0;
        this->symbol = '\0';
        this->nextState = 0;
    }
    int getState() const {
        return state;
    }
    char getSymbol() const {
        return symbol;
    }
    int getNextState() const {
        return nextState;
    }
    void setState(int state) {
        this->state = state;
    }
    void setSymbol(char symbol) {
        this->symbol = symbol;
    }
    void setNextState(int nextState) {
        this->nextState = nextState;
    }
    void print() const {
        cout << "t" << "(" << state << "," << symbol << "," << nextState << ")" << endl;
    }
};

//* a DFA is composed of a list of transitions,
//* a list of states,
//* a list of final states,
//* an alphabet,
//* and a list of inputs

class AFD {
    int initialState;
    vector<transition> transitions;
    vector<char> alphabet;
    vector<int> finalStates;
    vector<int> states;
public:
    AFD() {
        initialState = -2;
    }
    AFD(const AFD& afd) {
        this->initialState = afd.initialState;
        this->transitions = afd.transitions;
        this->alphabet = afd.alphabet;
        this->finalStates = afd.finalStates;
        this->states = afd.states;
    }
    bool isFinalState(int state) const {
        for (int i = 0; i < finalStates.size(); i++) {
            if (finalStates[i] == state) { //* if the state is in the final states vector	
                return true;
            }
        }
        return false;
    }
    bool isValidInput(char symbol) const {
        for (int i = 0; i < alphabet.size(); i++) {
            if (alphabet[i] == symbol) {
                return true;
            }
        }
        return false;
    }
    bool isValidState(int state) const {
        for (int i = 0; i < states.size(); i++) {
            if (states[i] == state) {
                return true;
            }
        }
        return false;
    }
    bool isValidTransition(int state, char symbol) const {
        for (int i = 0; i < transitions.size(); i++) {
            if (transitions[i].getState() == state && transitions[i].getSymbol() == symbol) {
                return true;
            }
        }
        return false;
    }
    int getNextState(int state, char symbol) const {
        for (int i = 0; i < transitions.size(); i++) {
            if (transitions[i].getState() == state && transitions[i].getSymbol() == symbol) {
                return transitions[i].getNextState();
            }
        }
        return -1;
    }
    void addTransition(int state, char symbol, int nextState) {
        transitions.push_back(transition(state, symbol, nextState)); //* add a new transition to the transitions vector
    }
    void addTransition(transition t) {
        transitions.push_back(t);
    }
    void addAlphabet(char symbol) {
        alphabet.push_back(symbol); //* add a new symbol to the alphabet vector
    }
    void addAlphabet(vector<char> symbols) {
        for (int i = 0; i < symbols.size(); i++) {
            alphabet.push_back(symbols[i]);
        }
    }
    void addFinalState(int state) {
        finalStates.push_back(state); //* add a new final state to the final states vector
    }
    void addState(int state) {
        states.push_back(state); //* add a new state to the states vector	
    }
    void setInitialState(int state) {
        this->initialState = state; //* set the initial state
    }
    int getInitialState() const {
        return initialState;
    }
    vector<char> getAlphabet() const {
        return alphabet;
    }
    vector<int> getFinalStates() const {
        return finalStates;
    }
    vector<int> getStates() const {
        return states;
    }
    vector<transition> getTransitions() const {
        return transitions;
    }
    void printTransitions() const {
        for (int i = 0; i < transitions.size(); i++) {
            cout << "t"<< i+1 << "("<< transitions[i].getState() << "," << transitions[i].getSymbol() << ") = " << transitions[i].getNextState() << endl;
        }
    }
    void printAlphabet() const {
        cout << "A = {";
        for (int i = 0; i < alphabet.size(); i++) {
            cout << alphabet[i];
            if (i != alphabet.size() - 1) {
                cout << ", ";
            }
            if(i == alphabet.size() - 1) {
                cout << "}" << endl;
            }
        }
    }
    void printFinalStates() const {
        string temp;
        if (finalStates.size() == 1)
            temp = "}";
        else 
            temp = ", ";
        for (int i = 0; i < finalStates.size(); i++) {
            cout << "F = {" << finalStates[i] << temp << endl;
        }
        if (temp != "}")
            cout << "}" << endl;
    }
    void printStates() const {
        cout << "E = {";
        for (auto& state : states) {
            cout << state;
            if (state != states.back()) {
                cout << ", ";
            }
            if (state == states.back()) {
                cout << "}" << endl;
            }
        }
    }
    void printInitialState() const {
        cout << "I = {" << initialState << "}" << endl;
    }
    void print() const {
        cout << "AFD: " << endl;
        printInitialState();
        cout << "--------------------------" << endl;
        printAlphabet();
        cout << "--------------------------" << endl;
        printStates();
        cout << "--------------------------" << endl;
        printFinalStates();
        cout << "--------------------------" << endl;
        printTransitions();
        cout << "--------------------------" << endl;
    }
    bool accept(const char* input) const {
        int currentState = initialState;
        for (int i = 0; i < size(input); i++) {
            for (int j = 0; j < transitions.size(); j++) {
                if (transitions[j].getSymbol() == input[i] and transitions[j].getState() == currentState) {
                        cout << "(" << currentState << ") -- " << input[i] << " --> ";
                        if (isFinalState(transitions[j].getNextState())) {
                            cout << "((" << transitions[j].getNextState() << "))" << endl;
                        } else {
                            cout << transitions[j].getNextState() << endl;
                        }
                        currentState = transitions[j].getNextState();
                        break;
                }
            }
        }
        if(isFinalState(currentState)) {
            return true;
        }
        return false;
    }
    bool accept(const string& input) const {
       int currentState = initialState;
        for (int i = 0; i < input.size(); i++) {
            if(!isValidInput(input[i])) {
                return false;
            }
            for (int j = 0; j < transitions.size(); j++) {
                if (transitions[j].getSymbol() == input[i] and transitions[j].getState() == currentState) {
                        cout << "(" << currentState << ") -- " << input[i] << " --> ";
                        if (isFinalState(transitions[j].getNextState())) {
                            cout << "((" << transitions[j].getNextState() << "))" << endl;
                        } else {
                            cout << transitions[j].getNextState() << endl;
                        }
                        currentState = transitions[j].getNextState();
                        break;
                }
            }
        }
        if(isFinalState(currentState)) {
            return true;
        }
        return false;
    }
    bool isEmpty() const {
        return transitions.empty() and states.empty() and alphabet.empty() and finalStates.empty();
    }
    bool isNotEnough() const {
        return initialState == -2 or transitions.empty() or states.empty() or alphabet.empty() or finalStates.empty();
    }
    bool isCorrupted() const {
        return initialState == -1;
    }
    bool mechanic() const {
        if (this->isCorrupted()) {
            cout << "ERROR : syntax error" << endl;
            return false;
        }
        else if (this->isEmpty()) {
            cout << "ERROR : Le fichier est vide." << endl;
            return false;
        }
        else if (this->isNotEnough()) {
            cout << "ERROR : Il manque des informations." << endl;
            return false;
        }
        return true;
    }
    void reset() {
        initialState = -1;
        transitions.clear();
        states.clear();
        alphabet.clear();
        finalStates.clear();
    }
    template <typename T>
    void Try(T input)  const {
        cout << "Le mot " << input << " : \n" << (accept(input) ? "=> accepte" : "=> refuse") << endl;
    }
};
namespace AFD_fx {
    template <typename T>
    AFD read(const T& file_name) {
        AFD afd;
        ifstream file(file_name);
        if (!file.is_open()) {
            cout << "Erreur lors de l'ouverture du fichier." << endl;
            afd.setInitialState(-1);
            getch();
            exit(1);
        }
        else {
            cout << "Fichier ouvert avec succes." << endl;
        }
        string line;
        int state;
        char symbol, id;
        int nextState;
        vector<char> alphabet;
        transition t;
        while (getline(file, line)) {
            switch (line[0])
            {
            case 'I' :
                if(line.size() != 3) {
                    cout << "Erreur de syntax : l'etat initial." << endl;
                    return afd;
                }
                state = stoi(line.substr(2, line.size() - 2));
                afd.setInitialState(state);
                break;
            case 'A' :
                for(int i = 2; i < line.size(); i = i + 2) {
                    alphabet.push_back(line[i]);
                }
                afd.addAlphabet(alphabet);
                break;
            case 'F' :
                for(int i = 2; i < line.size(); i=i+2) {
                        state = stoi(line.substr(i, 1));
                        afd.addFinalState(state);
                }
                break;
            case 'E' :
                for(int i = 2; i < line.size(); i=i+2) {
                        state = stoi(line.substr(i, 1));
                        afd.addState(state);
                    }
                break;
            case 't' :
                state = stoi(line.substr(2, 1));
                symbol = line[4];
                nextState = stoi(line.substr(6, 1));
                t.setState(state);
                t.setSymbol(symbol);
                t.setNextState(nextState);
                afd.addTransition(t);
                break;
            default:
                cout << "Erreur de syntax : ligne non reconnue." << endl;
                return afd;
            }
        }
        file.close();
        return afd;
    }
    void printSpacing() {
        cout << "--------------------------------------------------------------------------------" << endl;
    }
    void printProtocol() {
        printSpacing();
        cout << "Dans le fichier txt. Vous devez saisir en respectant ce protocol : \n";
        printSpacing();
        cout << "Etat Initial => I,\n" <<"Transition => t,\n" << "Liste des Etats => E,\n" << "Liste d'etats finaux => F,\n" << "L'alphabet => A,\n";
        printSpacing();
        cout << "Veuillez entrer le nom du fichier a utiliser : ";
    }
}