#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#pragma once
#pragma execution_character_set( "utf-8" )
#define colWidth 30
#define spcWidth 80
using namespace std;
namespace output { //* decorative output functions for console 
    void printSpacing(int n = spcWidth) {
    for(int i = 0; i < n; i++) {
        cout << "-";
    }
    cout << endl;
    }
    void printInTable(const vector<string> str, const vector<string> value) {
        for(int i = 0; i < str.size(); i++) {
            cout << setprecision(0) << setw(colWidth) << value[i] << setprecision(4) << 
            setw(colWidth)<< str[i] << endl;
            cout << setprecision(0) << setw(16);
            printSpacing(50);
        }
    }
}
namespace useful {
    template <typename T, typename U>
    bool equal(const vector<T>& a, const vector<U>& b) {
        return std::equal(a.begin(), a.end(), b.begin());
    }
    int size(const char* in) { //* return the size of a const char* * != string
        return sizeof(in) / sizeof(in[0]);
    };
}
//* a transition is composed of a state,
//* a symbol
//* and a next state
class transition {
    int state;
    char symbol;
    int nextState;
public:
    transition(int state, char symbol, int nextState) :
    state(state),
    symbol(symbol),
    nextState(nextState)
    {}
    transition() :
    state(0),
    symbol('\0'),
    nextState(0)
    {}
    bool operator==(const transition& t) const {
        return state == t.state && symbol == t.symbol && nextState == t.nextState;
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
        cout << "t" << "(" << this->state << "," << this->symbol << "," << this->nextState << ")" << endl;
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
    public :
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
    AFD setAFD(const AFD afd) {
        initialState = afd.getInitialState();
        transitions = afd.getTransitions();
        states = afd.getStates();
        alphabet = afd.getAlphabet();
        finalStates = afd.getFinalStates();
        return *this;
    }
    AFD operator&=(const AFD afd) {
        return setAFD(afd);
    }
    bool operator==(const AFD& afd) const {
        return initialState == afd.getInitialState() and
                transitions == afd.getTransitions() and
                states == afd.getStates() and
                alphabet == afd.getAlphabet() and
                finalStates == afd.getFinalStates();
    }
    bool isFinalState(const int state) const {
        auto itemItr = find(finalStates.begin(), finalStates.end(), state);
        return itemItr != finalStates.end();
    }
    bool isValidChar(const char symbol) const {
        auto itemItr = find(alphabet.begin(), alphabet.end(), symbol);
        return itemItr != alphabet.end();
    }
    bool isValidState(const int state) const {
        auto itemItr = find(states.begin(), states.end(), state);
        return itemItr != states.end();
    }
    bool isValidTransition(const int state, const char symbol) const {
        //* using lambda function
        auto itemItr = find_if(transitions.begin(), transitions.end(), [state, symbol](const transition& t) {
            return t.getState() == state && t.getSymbol() == symbol;
        });
        return itemItr != transitions.end();
    }
    int getNextState(const int state, const char symbol) const {
        auto itemItr = find_if(transitions.begin(), transitions.end(), [state, symbol](const transition& t) {
            return t.getState() == state && t.getSymbol() == symbol;
        });
        if(itemItr != transitions.end())
            return itemItr->getNextState();
        return -1;
    }
    private : bool checkTransitions(const transition& t) {
        auto itemItr = find_if(transitions.begin(), transitions.end(), [t](const transition& t2) {
            return t.getState() == t2.getState() && t.getSymbol() == t2.getSymbol();
        });
        if (itemItr != transitions.end())
            return true;
        return false;
    }
    public :
    void addTransition(const int state, const char symbol, const int nextState) {//* add a new transition to afd's transitions vector
        if(checkTransitions(transition(state, symbol, nextState))) {
            cout << "Transition t("<< state << ", " << symbol <<") already exists" << endl;
            return;
        }
        transitions.push_back(transition(state, symbol, nextState));
        sort(transitions.begin(), transitions.end(), [](const transition& t1, const transition& t2) {
            return t1.getState() < t2.getState();
        });
    }
    void addTransition(const transition& t) {
        addTransition(t.getState(), t.getSymbol(), t.getNextState());
    }
    void addAlphabet(const char symbol) {
        alphabet.push_back(symbol); //* add a new symbol to the alphabet vector
    }
    void addAlphabet(const vector<char> symbols) {
        for (int i = 0; i < symbols.size(); i++) {
            alphabet.push_back(symbols[i]);
        }
    }
    void addFinalState(const int state) {
        finalStates.push_back(state); //* add a new final state to the final states vector
    }
    void addState(const int state) {
        states.push_back(state); //* add a new state to the states vector	
    }
    void setInitialState(const int state) {
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
        if(transitions.size() == 0) {
            cout << "t = ( EMPTY )" << endl;
            return;
        }
        for (int i = 0; i < transitions.size(); i++) {
            cout << "t"<< i+1 << "("<< transitions[i].getState() << ", " << transitions[i].getSymbol() << ") = " << transitions[i].getNextState() << endl;
        }
    }
    void printAlphabet() const {
        cout << "A = {";
        if(alphabet.size() == 0)
            cout << " EMPTY }" << endl;
        for (int i = 0; i < alphabet.size(); i++) {
            cout << alphabet[i];
            if (i != alphabet.size() - 1) {
                cout << ", ";
            }
            if (i == alphabet.size() - 1) {
                cout << "}" << endl;
            }
        }
    }
    void printFinalStates() const {
        cout << "F = {";
        if(finalStates.size() == 0) {
            cout << " EMPTY }" << endl;
        }
        for (int i = 0; i < finalStates.size(); i++) {
            cout << finalStates[i];
            if (i != finalStates.size() - 1) {
                cout << ", ";
            }
            if (i == finalStates.size() - 1) {
                cout << "}" << endl;
            }
        }
    }
    void printStates() const {
        cout << "E = {";
        if (states.size() == 0) {
            cout << " EMPTY }" << endl;
        }
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
        if (initialState == -2) 
            cout << "I = { EMPTY }" << endl;
        else 
            cout << "I = {" << initialState << "}" << endl;
    }
    void print(const string nom = "") const {
        using namespace output;
        cout << "AFD: " << nom << endl;
        printInitialState();
        printSpacing();
        printAlphabet();
        printSpacing();
        printStates();
        printSpacing();
        printFinalStates();
        printSpacing();
        printTransitions();
        printSpacing();
    }
    template <typename T>
    bool accept(const T& input) const {
        const string inp(input);
        int currentState = initialState;
        for (size_t i = 0; i < inp.size(); i++) {
            if(!isValidChar(inp[i])) {
                return false;
            }
            for (size_t j = 0; j < transitions.size(); j++) {
                if (transitions[j].getSymbol() == inp[i] and transitions[j].getState() == currentState) {
                        if(isFinalState(currentState)) {
                            cout << "((" << currentState << ")) -- " << inp[i] << " --> ";
                        }
                        else
                            cout << "(" << currentState << ") -- " << inp[i] << " --> ";
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
        return isFinalState(currentState);
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
    bool isHealthy() const {
        if (this->isCorrupted()) {
            cout << "ERROR : Syntax error" << endl;
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
    AFD reset() {
        initialState = -2;
        transitions.clear();
        states.clear();
        alphabet.clear();
        finalStates.clear();
        return *this;
    }
    template <typename T>
    void Try(const T& input)  const {
        output::printSpacing();
        cout << "Le mot " << input << " : \n" << (accept(input) ? "=> accepte" : "=> refuse") << endl;
    }
    bool isValidInput(const string& input) const {
        for (int i = 0; i < input.size(); i++) {
            if(!isValidChar(input[i])) {
                return false;
            }
        }
        return true;
    }
    void inputFromUser() const {
        string input;
        while (true) {
            cout << "Entrez un mot a tester : ";
            cin >> input;
            if(input == "exit")
                break;
            Try(input);
        }
    }
};
namespace AFD_fx {
    template <typename T>
    AFD read(const T& file_name) {
        AFD afd;
        ifstream file(file_name);
        if (!file.is_open()) {
            cout << "ERROR : Erreur lors de l'ouverture du fichier." << endl;
            afd.setInitialState(-1);
            return afd; 
        }
        else {
            cout << "SUCCESS : Fichier ouvert avec succes." << endl;
        }
        string line;
        int state;
        char symbol, id;
        int nextState;
        vector<char> alphabet;
        transition t;
        int count = 1;
        while (getline(file, line)) {
            switch (line[0]) {
                case 'I' :
                    if(line.size() != 3 || isalpha(line[2])) {
                        cout << "Erreur de syntax : " << count << " - l'etat initial." << endl;
                        afd.setInitialState(-1);
                        return afd;
                    }
                    state = stoi(line.substr(2, line.size() - 2));
                    afd.setInitialState(state);
                    break;
                case 'A' :
                    for(int i = 2; i < line.size(); i = i + 2) {
                        if (!isalpha(line[i])) {
                                cout << "Erreur de syntax : " << count << " - l'alphabet. (A)" << endl;
                                afd.setInitialState(-1);
                                return afd;
                            }
                        alphabet.push_back(line[i]);
                    }
                    afd.addAlphabet(alphabet);
                    break;
                case 'F' :
                    for(int i = 2; i < line.size(); i=i+2) {
                            if (isalpha(line[i])) {
                                cout << "Erreur de syntax : " << count << " - les états finaux (F)" << endl;
                                afd.setInitialState(-1);
                                return afd;
                            }
                            state = stoi(line.substr(i, 1));
                            afd.addFinalState(state);
                    }
                    break;
                case 'E' :
                    for(int i = 2; i < line.size(); i=i+2) {
                            if (isalpha(line[i])) {
                                cout << "Erreur de syntax : " << count << " - les états (E)" << endl;
                                afd.setInitialState(-1);
                                return afd;
                            }
                            state = stoi(line.substr(i, 1));
                            afd.addState(state);
                    }
                    break;
                case 't' :
                    state = stoi(line.substr(2, 1));
                    symbol = line[4];
                    nextState = stoi(line.substr(6, 1));
                    t = transition(state, symbol, nextState);
                    afd.addTransition(t);
                    break;
                default :
                    cout << "Erreur de syntax : " << count << " - ligne non reconnue" << endl;
                    return afd;
            }
            count++;
        }
        file.close();
        return afd;
    }
    void printProtocol() {
        using namespace output;
        printSpacing();
        cout << "Dans le fichier txt. Vous devez saisir en respectant ce protocol : \n";
        printSpacing();
        printInTable({"I", "A", "F", "E", "t"}, {"Initial state", "Alphabet", "Final states", "States", "Transitions"});
        printSpacing();
        cout << "Veuillez entrer le nom du fichier a utiliser : ";
    }
    template <typename T>
    string mirror(T input) {
        string output(input);
        for (int i = input.size() - 1; i >= 0; i--) {
            output += input[i];
        }
        return output;
    }
    void printSize(const string& input) {
        cout << "La taille de "<< input << " est de " << input.size() << " caracteres." << endl;
    }
    bool isPalindrome(const string& s) {
        for (int i = 0; i < s.size() / 2; i++) {
            if (s[i] != s[s.size() - i - 1]) {
                return false;
            }
        }
        return true;
    }
}

