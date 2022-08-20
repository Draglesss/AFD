#include <iostream>
#include <string>
#include <vector>
#include "transitions.hpp"
#include <fstream>
#include <conio.h>
#include <regex>
#include <iomanip>
//#include <chrono>
#include <algorithm>
#pragma once
#pragma execution_character_set( "utf-8" )
#define colWidth 30
#define spcWidth 80
#define NC "\e[0m"
#define CAU "\e[33m"
#define ERR "\e[31m"
#define GRN "\e[32m"
using namespace std;

namespace output { //* decorative output functions for console 
    void printSpacing(int n = spcWidth) {
    for(int i = 0; i < n; i++) {
        std::cout << "-";
    }
    std::cout << endl;
    }
    void printInTable(const std::vector<string> str, const std::vector<string> value) {
        for(int i = 0; i < str.size(); i++) {
            std::cout << std::setprecision(0) << std::setw(colWidth) << value[i] << std::setprecision(4) << 
            std::setw(colWidth)<< str[i] << std::endl;
            std::cout << std::setprecision(0) << std::setw(16);
            printSpacing(50);
        }
    }
}
template <typename T> 
int size(const T* in) { //* return the size of a const char* * != string
    return sizeof(in) / sizeof(in[0]);
};
int size(const string& in) { //* return the size of a string
    return in.size();
}
template <typename T>
const std::string file_namesubstr(const T& __file_name) { //* return the extension of a file name
    return __file_name.substr(__file_name.find_last_of(".") + 1);
}

//* a DFA is composed of a list of transitions,
//* a list of states,
//* a list of final states,
//* an alphabet,
//* and a list of inputs

class AFD {
    int initialState;
    std::vector<transition> transitions;
    std::vector<char> alphabet;
    std::vector<int> finalStates;
    std::vector<int> states;
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
    AFD& set(const AFD afd) {
        initialState = afd.getInitialState();
        transitions = afd.getTransitions();
        states = afd.getStates();
        alphabet = afd.getAlphabet();
        finalStates = afd.getFinalStates();
        return *this;
    }
    AFD& operator&= (const AFD afd) {
        return this->set(afd);
    }
    bool operator== (const AFD& afd) const {
        return initialState == afd.getInitialState() and
                transitions == afd.getTransitions() and
                states == afd.getStates() and
                alphabet == afd.getAlphabet() and
                finalStates == afd.getFinalStates();
    }
    friend std::ostream& operator<< (std::ostream& os, const AFD& afd) {
        afd.print();
        return os;
    }
    bool isFinalState(const int state) const {
        return std::find(finalStates.begin(), finalStates.end(), state) != finalStates.end();
    }
    bool isValidSymbol(const char symbol) const {
        return std::find(alphabet.begin(), alphabet.end(), symbol) != alphabet.end();
    }
    bool isValidState(const int state) const {
        return std::find(states.begin(), states.end(), state) != states.end();
    }
    bool isAccessibleState(const int state) const {
        if(!isValidState(state))
            return false;
        int currentstate = initialState;
        for(int i = 0; i < transitions.size(); i++) {
            if(transitions[i].getState() == currentstate) {
                currentstate = transitions[i].getNextState();
            }
            if(currentstate == state) {
                return true;
            }
        }
        return false;
    }
    bool isValidTransition(const int state, const char symbol) const {
        //* using lambda function
        return std::find_if(transitions.begin(), transitions.end(), [state, symbol](const transition& t) {
            return t.getState() == state && t.getSymbol() == symbol;
        }) != transitions.end();
    }
    int getNextState(const int state, const char symbol) const {
        auto itemItr = std::find_if(transitions.begin(), transitions.end(), [state, symbol](const transition& t) {
            return t.getState() == state && t.getSymbol() == symbol;
        });
        if(itemItr != transitions.end())
            return itemItr->getNextState();
        return -1;
    }
    int getNextState(const transition& t) const {
        return t.getNextState();
    }
    private : bool checkTransitions(const transition& t) {
        return std::find_if(transitions.begin(), transitions.end(), [t](const transition& t2) {
            return t.getState() == t2.getState() && t.getSymbol() == t2.getSymbol();
        }) != transitions.end();
    }
    public :
    AFD addTransition(const int state, const char symbol, const int nextState) {
        if(checkTransitions(transition(state, symbol, nextState))) {
            cout << "Transition t("<< state << ", " << symbol <<") already exists" << endl;
            return *this;
        }
        transitions.push_back(transition(state, symbol, nextState));
        std::sort(transitions.begin(), transitions.end(), [](const transition& t1, const transition& t2) {
            return t1.getState() < t2.getState();
        });
        return *this;
    }
    AFD& addTransition(const transition& t) {
        addTransition(t.getState(), t.getSymbol(), t.getNextState());
        return *this;
    }
    AFD& addAlphabet(const char symbol) {
        alphabet.push_back(symbol);
        return *this;
    }
    AFD& addAlphabet(const vector<char> symbols) {
        for (int i = 0; i < symbols.size(); i++) {
            alphabet.push_back(symbols[i]);
        }
        return *this;
    }
    AFD& addFinalState(const int state) {
        finalStates.push_back(state);
        std::sort(finalStates.begin(), finalStates.end());
        return *this;
    }
    AFD& addState(const int state) {
        states.push_back(state);
        return *this;
    }
    AFD& setInitialState(const int state) {
        this->initialState = state;
        return *this;
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
            std::cout << "t = ( EMPTY )" << std::endl;
            return;
        }
        for (int i = 0; i < transitions.size(); i++) {
            std::cout << "t"<< i+1 << "("<< transitions[i].getState() << ", " << transitions[i].getSymbol() << ") = " 
            << transitions[i].getNextState() << std::endl;
        }
    }
    void printAlphabet() const {
        cout << "A = {";
        if(alphabet.size() == 0)
            std::cout << " EMPTY }" << std::endl;
        for (int i = 0; i < alphabet.size(); i++) {
            std::cout << alphabet[i];
            if (i != alphabet.size() - 1) {
                std::cout << ", ";
            }
            else
                std::cout << "}" << std::endl;
        }
    }
    void printFinalStates() const {
        std::cout << "F = {";
        if(finalStates.size() == 0) {
            std::cout << " EMPTY }" << std::endl;
        }
        for (int i = 0; i < finalStates.size(); i++) {
            std::cout << finalStates[i];
            if (i != finalStates.size() - 1)
                std::cout << ", ";
            else
                std::cout << "}" << std::endl;
        }
    }
    void printStates() const {
        std::cout << "E = {";
        if (states.size() == 0) {
            std::cout << " EMPTY }" << std::endl;
        }
        for (auto& state : states) {
            std::cout << state;
            if (state != states.back())
                std::cout << ", ";
            else
                std::cout << "}" << std::endl;
        }
    }
    void printInitialState() const {
        if (initialState == -2) 
            std::cout << "I = { EMPTY }" << std::endl;
        else
            std::cout << "I = {" << initialState << "}" << std::endl;
    }
    void print(const string& nom = "") const { //* print the afd with an optional name
        using namespace output;
        if(nom != "") std::cout << "AFD : " << nom << std::endl;
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
    void print(const char* nom) const {
        const string nomStr(nom);
        print(nomStr);
    }
    template <typename T>
    const bool accept(const T& input) const {
        const string inp(input);
        //chrono::steady_clock clock;
        //auto start = clock.now();
        int currentState = initialState;
        for (size_t i = 0; i < inp.size(); i++) {
            if(!isValidSymbol(inp[i])) {
                return false;
            }
            for (size_t j = 0; j < transitions.size(); j++) {
                if (transitions[j].getSymbol() == inp[i] and transitions[j].getState() == currentState) {
                        if(isFinalState(currentState)) {
                            std::cout << GRN"((" << currentState << "))" NC << " -- " << inp[i] << " --> ";
                        }
                        else
                            cout << "(" << currentState << ") -- " << inp[i] << " --> ";
                        if (isFinalState(transitions[j].getNextState())) {
                            std::cout << GRN "((" << transitions[j].getNextState() << "))" NC << std::endl;
                        } else {
                            std::cout << transitions[j].getNextState() << std::endl;
                        }
                        currentState = transitions[j].getNextState();
                        break;
                }
            }
        }
        //auto end = clock.now();
        //auto time_span = static_cast<chrono::duration<double>>(end - start);
        //cout<<"Operation took: "<<time_span.count()<<" seconds !!!";
        return isFinalState(currentState);
        //* accept() raw
        //* bool accept(const T& input) const {
        //* const string inp(input);
        //* int currentState = initialState;
        //* for (size_t i = 0; i < inp.size(); i++) {
        //*     if(!isValidChar(inp[i])) {
        //*         return false;
        //*     }
        //*    for (size_t j = 0; j < transitions.size(); j++) {
        //*        if (transitions[j].getSymbol() == inp[i] and transitions[j].getState() == currentState) {
        //*                 currentState = transitions[j].getNextState();
        //*                 break;
        //*         }
        //*     }
        //*  }
        //*     return isFinalState(currentState);
        //* }
    }
    bool isEmpty() const {
        return initialState == -2 and transitions.empty() and states.empty() and alphabet.empty() and finalStates.empty();
    }
    bool isNotEnough() const {
        return initialState == -2 or transitions.empty() or states.empty() or alphabet.empty() or finalStates.empty();
    }
    bool isCorrupted() const {
        return initialState == -1;
    }
    bool isHealthy() const {
        if (this->isCorrupted()) {
            std::cout << ERR "ERROR : Syntax error." NC << std::endl;
            return false;
        }
        else if (this->isEmpty()) {
            std::cout << ERR "ERROR : L'automate est vide." NC << std::endl;
            return false;
        }
        else if (this->isNotEnough()) {
            std::cout << ERR "ERROR : Il manque des informations." NC << std::endl;
            return false;
        }
        return true;
    }
    AFD& reset() {
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
        std::cout << "Le mot " << input << " : \n" << (accept(input) ? GRN "=> accepte" NC : ERR "=> refuse" NC )  << std::endl;
    }
    bool isValidInput(const string& input) const {
        for (int i = 0; i < input.size(); i++) {
            if(!isValidSymbol(input[i])) {
                return false;
            }
        }
        return true;
    }
    void consoleInput() const {
        std::string input;
        while (true) {
            std::cout << "Entrez un mot a tester : ";
            std::cin >> input;
            if(input == "exit")
                break;
            Try(input);
        }
    }
};

namespace AFD_fx {
    template <typename T>
    inline AFD read(const T& __file_name) {
        AFD afd;
        const std::string __file(__file_name);
        const std::string caution_message(CAU "CAUTION : AFD generated from \"" + __file + "\" is empty!" NC);
        const std::string ext = __file.substr(__file.find_last_of(".") + 1);
        if(!std::regex_match(ext, std::regex("(afd)|(txt)", std::regex_constants::icase)))
        {
            std::cout << ERR "ERROR : Le fichier n'est pas un fichier TXT ou AFD." NC << std::endl;
            std::cerr << caution_message << std::endl;
            throw new exception();
            return afd;
        }
        std::cout << " ----------------- Reading file " << __file << "... ----------------" << std::endl;
        ifstream file(__file); //* pointer to / opens the file so no need for .open()
        if(!file) {
            std::cout << ERR "ERROR : Le fichier n'existe pas." NC << std::endl;
            std::cerr << caution_message << std::endl;
            throw new exception();
            return afd;
        }
        if (!file.is_open()) {
            std::cout << ERR "ERROR : Erreur lors de l'ouverture du fichier." NC << std::endl;
            std::cerr << caution_message << std::endl;
            throw new exception();
            return afd.setInitialState(-2); //* return an empty afd
        }
        std::cout << GRN "SUCCESS : Fichier ouvert avec succes." NC << std::endl;
        std::string line;
        int state;
        char symbol, id;
        int nextState;
        std::vector<char> alphabet;
        transition t;
        int count = 1;
        while (getline(file, line)) {
            switch (line[0]) {
                case 'I' :
                    if(line.size() != 3 || isalpha(line[2])) {
                        std::cout << ERR "Erreur de syntax : " << count << " - l'etat initial (I)." NC << std::endl;
                        return afd.setInitialState(-1);
                    }
                    state = stoi(line.substr(2, line.size() - 2));
                    afd.setInitialState(state);
                    break;
                case 'A' :
                    for(int i = 2; i < line.size(); i = i + 2) {
                        if (!isalpha(line[i])) {
                                std::cout << ERR "Erreur de syntax : " << count << " - l'alphabet (A)." NC << std::endl;
                                return afd.setInitialState(-1);
                            }
                        alphabet.push_back(line[i]);
                    }
                    afd.addAlphabet(alphabet);
                    break;
                case 'F' :
                    for(int i = 2; i < line.size(); i=i+2) {
                            if (isalpha(line[i])) {
                                std::cout << ERR "Erreur de syntax : " << count << " - les états finaux (F)" NC << std::endl;
                                return afd.setInitialState(-1);
                            }
                            state = stoi(line.substr(i, 1));
                            afd.addFinalState(state);
                    }
                    break;
                case 'E' :
                    for(int i = 2; i < line.size(); i=i+2) {
                            if (isalpha(line[i])) {
                                std::cout << ERR "Erreur de syntax : " << count << " - les états (E)" NC << std::endl;
                                return afd.setInitialState(-1);
                            }
                            state = stoi(line.substr(i, 1));
                            afd.addState(state);
                    }
                    break;
                case 't' :
                    try {
                    state = stoi(line.substr(2, 1));
                    symbol = line[4];
                    nextState = stoi(line.substr(6, 1));
                    afd.addTransition(transition(state, symbol, nextState));
                    break;
                    } catch (exception& e) {
                        std::cout << ERR "Erreur de syntax : " << count << " - la transition (t)." NC << std::endl;
                        return afd.setInitialState(-1);
                    }
                default :
                    std::cout <<  ERR "Erreur de syntax : " << count << " - ligne non reconnue" NC << std::endl;
                    return afd.setInitialState(-1);
            }
            count++;
        }
        file.close();
        return afd;
    }
    void printProtocol() {
        using namespace output;
        printSpacing();
        std::cout << "Dans le fichier txt. Vous devez saisir en respectant ce protocol : \n";
        printSpacing();
        printInTable({"I", "A", "F", "E", "t"}, {"Initial state", "Alphabet", "Final states", "States", "Transitions"});
        printSpacing();
    }
    template <typename T>
    std::string mirror(const T& inp) {
        std::string input(inp), output;
        for (int i = input.size() - 1; i >= 0; i--) {
            output += input[i];
        }
        return output;
    }
    template <typename T>
    bool isPalindrome(const T& s) {
        return s == mirror(s);
    }
}