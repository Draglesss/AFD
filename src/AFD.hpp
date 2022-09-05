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


namespace output { //* decorative output functions for console 
    using namespace std;
    void printSpacing(int n = spcWidth) {
        for(int i = 0; i < n; i++) {
            std::cout << "-";
        }
        std::cout << '\n';
    }
    void printInTable(const std::vector<string> str, const std::vector<string> value) {
        for(int i = 0; i < str.size(); i++) {
            std::cout << std::setprecision(0) << std::setw(colWidth) << value[i] << std::setprecision(4) << 
            std::setw(colWidth)<< str[i] << '\n';
            std::cout << std::setprecision(0) << std::setw(16);
            printSpacing(50);
        }
    }
}
template <typename T> 
int size(const T* in) { //* return the size of a const char* * != string
    return sizeof(in) / sizeof(in[0]);
}
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
    inline AFD() {
        initialState = -2; //* marking the afd as empty to be flagged in isEmpty()
    }
    inline AFD(const AFD& afd) {
        this->initialState = afd.initialState;
        this->transitions = afd.transitions;
        this->alphabet = afd.alphabet;
        this->finalStates = afd.finalStates;
        this->states = afd.states;
    }
    inline AFD& set(const AFD& afd) {
        initialState = afd.getInitialState();
        transitions = afd.getTransitions();
        states = afd.getStates();
        alphabet = afd.getAlphabet();
        finalStates = afd.getFinalStates();
        return *this;
    }
    inline AFD& operator&= (const AFD& afd) {
        return this->set(afd);
    }
    inline bool operator== (const AFD& afd) const {
        return initialState == afd.getInitialState() and
                transitions == afd.getTransitions() and
                states == afd.getStates() and
                alphabet == afd.getAlphabet() and
                finalStates == afd.getFinalStates();
    }
    inline friend std::ostream& operator<< (std::ostream& os, const AFD& afd) {
        afd.print();
        return os;
    }
    inline bool isFinalState(const int state) const {
        return std::find(finalStates.begin(), finalStates.end(), state) != finalStates.end();
    }
    inline bool isValidSymbol(const char symbol) const {
        return std::find(alphabet.begin(), alphabet.end(), symbol) != alphabet.end();
    }
    inline bool isValidState(const int state) const {
        return std::find(states.begin(), states.end(), state) != states.end();
    }
    inline bool isAccessibleState(const int state) const {
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
    inline bool isValidTransition(const transition& t) const {
        return std::find_if(transitions.begin(), transitions.end(), [&t](const transition& tr) {
            return tr == t;
        }) != transitions.end();
    }
    inline bool isValidTransition(const int state, const char symbol) const {
        return std::find_if(transitions.begin(), transitions.end(), [state, symbol](const transition& t) {
            return t.getState() == state && t.getSymbol() == symbol;
        }) != transitions.end();
    }
    public :
    /**
     * @brief add a transition to the transitions vector and sort it
     * @param t the transition to add
     * @return the current AFD object by reference
     */
    inline AFD& addTransition(const transition& t) {
        if(isValidTransition(t))
        {
            cout << "Transition t("<< t.getState() << ", " << t.getSymbol() <<") already exists" << '\n';
            return *this;
        }
        transitions.push_back(t);
        std::sort(transitions.begin(), transitions.end(), [](const transition& t1, const transition& t2) {
            return t1.getState() < t2.getState();
        });
        return *this;
    }
    /**
     * @brief add a symbol to the alphabet vector
     * @param symbol the symbol to add
     * @return the current AFD object by reference
     */
    inline AFD& addAlphabet(const char symbol) {
        alphabet.push_back(symbol);
        return *this;
    }
    /**
     * @brief add a char vector to the end of the alphabet vector
     * @param symbols char vector of symbols to add
     * @return the current AFD object by reference
     */
    inline AFD& addAlphabet(const vector<char> symbols) {
        alphabet.insert(alphabet.end(), symbols.begin(), symbols.end());
        return *this;
    }
    inline AFD& addFinalState(const int state) {
        finalStates.push_back(state);
        std::sort(finalStates.begin(), finalStates.end());
        return *this;
    }
    inline AFD& addState(const int state) {
        if (!isValidState(state)) 
        {
            states.push_back(state);
            std::sort(states.begin(), states.end());
        }
        return *this;
    }
    inline AFD& setInitialState(const int state) {
        initialState = state;
        return *this;
    }
    inline int getInitialState() const {
        return initialState;
    }
    inline vector<char> getAlphabet() const {
        return alphabet;
    }
    inline vector<int> getFinalStates() const {
        return finalStates;
    }
    inline vector<int> getStates() const {
        return states;
    }
    inline vector<transition> getTransitions() const {
        return transitions;
    }
    inline void printTransitions() const {
        if(transitions.size() == 0) {
            std::cout << "t = ( EMPTY )" << '\n';
            return;
        }
        for (int i = 0; i < transitions.size(); i++) {
            std::cout << "t"<< i+1 << "("<< transitions[i].getState() << ", " << transitions[i].getSymbol() << ") = " 
            << transitions[i].getNextState() << '\n';
        }
    }
    inline void printAlphabet() const {
        cout << "A = {";
        if(alphabet.size() == 0)
            std::cout << " EMPTY }" << '\n';
        for (int i = 0; i < alphabet.size(); i++) {
            std::cout << alphabet[i];
            if (i != alphabet.size() - 1)
                std::cout << ", ";
            else
                std::cout << "}" << '\n';
        }
    }
    inline void printFinalStates() const {
        std::cout << "F = {";
        if(finalStates.size() == 0)
            std::cout << " EMPTY }" << '\n';
        for (int i = 0; i < finalStates.size(); i++) {
            std::cout << finalStates[i];
            if (i != finalStates.size() - 1)
                std::cout << ", ";
            else
                std::cout << "}" << '\n';
        }
    }
    inline void printStates() const {
        std::cout << "E = {";
        if (states.size() == 0)
            std::cout << " EMPTY }" << '\n';
        for (auto& state : states) {
            std::cout << state;
            if (state != states.back())
                std::cout << ", ";
            else
                std::cout << "}" << '\n';
        }
    }
    inline void printInitialState() const {
        if (initialState == -2) 
            std::cout << "I = { EMPTY } (-2)" << '\n';
        else
            std::cout << "I = {" << initialState << "}" << '\n';
    }
    inline void print(const string& nom = "") const { //* print the afd with an optional name
        using namespace output;
        if(nom != "") std::cout << "AFD : " << nom << '\n';
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
    inline void print(const char* nom) const {
        const std::string nomStr(nom);
        print(nomStr);
    }
    //* determins whether or not a string is accepted by the afd
    //* and prints the path taken to parse the string
    //* @param __input the string to be tested
    //* @return true if the string is accepted, false otherwise
    template <typename T>
    inline const bool accept(const T& __input) const {
        const std::string input(__input);
        //chrono::steady_clock clock;
        //auto start = clock.now();
        int currentState = initialState;
        for (size_t i = 0; i < input.size(); i++) {
            if(!isValidSymbol(input[i])) {
                cerr << CAU << input[i] << " is an invalid symbol"  << NC << '\n';
                return false;
            }
            for (size_t j = 0; j < transitions.size(); j++) {
                if (transitions[j].getSymbol() == input[i] and transitions[j].getState() == currentState) {
                    if(isFinalState(currentState)) {
                        std::cout << GRN"((" << currentState << "))" NC << " -- " << input[i] << " --> ";
                    }
                    else
                        cout << "(" << currentState << ") -- " << input[i] << " --> ";
                    if (isFinalState(transitions[j].getNextState())) {
                        std::cout << GRN "((" << transitions[j].getNextState() << "))" NC << '\n';
                    } else {
                        std::cout << transitions[j].getNextState() << '\n';
                    }
                    currentState = transitions[j].getNextState();
                    break;
                }
            }
        }
        //auto end = clock.now();
        //auto time_span = static_cast<chrono::duration<double>>(end - start);
        //cout << "Operation took: " << time_span.count() << " seconds !!!" << '\n';

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
    inline bool isEmpty() const {
        return initialState == -2 and transitions.empty() and states.empty() and alphabet.empty() and finalStates.empty();
    }
    inline bool isNotEnough() const {
        return initialState == -2 or transitions.empty() or states.empty() or alphabet.empty() or finalStates.empty();
    }
    inline bool isCorrupted() const {
        return initialState == -1;
    }
    inline bool isHealthy() const {
        if (this->isCorrupted()) {
            //* corrupted afd meaning that the file reading was unsuccessful
            std::cerr << ERR "ERROR : Syntax error." NC << '\n';
            return false;
        }
        else if (this->isEmpty()) {
            //* empty afd
            std::cerr << ERR "ERROR : L'automate est vide." NC << '\n';
            return false;
        }
        else if (this->isNotEnough()) {
            //* more info is needed
            std::cerr << ERR "ERROR : Il manque des informations." NC << '\n';
            return false;
        }
        return true;
    }
    inline AFD& reset() {
        initialState = -2;
        transitions.clear();
        states.clear();
        alphabet.clear();
        finalStates.clear();
        return *this;
    }
    template <typename T>
    inline void Try(const T& __input)  const {
        std::string input(__input);
        output::printSpacing();
        std::cout << "Le mot " << input << " : \n" << (accept(input) ? GRN "=> accepte" NC : ERR "=> refuse" NC )  << '\n';
    }
    inline bool isValidInput(const std::string& input) const {
        for (int i = 0; i < input.size(); i++) {
            if(!isValidSymbol(input[i])) {
                return false;
            }
        }
        return true;
    }
    //* takes repeated input from console till the user enters exit
    inline void consoleInput() const {
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
    /**
    /* @brief loads an afd from a file into memory / afd object
    /* @param __file_name the name of the file to load
    /* @return the loaded afd if the file is valid, an empty afd with an initial state equal to -2 if the file requested failed to open, or -1 if afd stored in the file is flawed otherwise
    */
    template <typename T>
    inline AFD read(const T& __file_name) {
        AFD afd; //* afd to load
        const std::string __file(__file_name); //* file to load
        const std::string caution_message(CAU "CAUTION : AFD generated from \"" + __file + "\" is empty!" NC); 
        const std::string ext = __file.substr(__file.find_last_of(".") + 1); //* file extension
        if (!std::regex_match(ext, std::regex("(afd)|(txt)", std::regex_constants::icase))) 
        {
            std::cerr << ERR "ERROR : Le fichier n'est pas un fichier TXT ou AFD." NC << '\n';
            std::cerr << caution_message << '\n';
            return afd.setInitialState(-2);
        }
        ifstream file(__file); //* pointer to / opens the file so no need for .open()
        if (!file) { //* checking for file existence
            std::cerr << ERR "ERROR : Le fichier " + __file + " n'existe pas." NC << '\n';
            std::cerr << caution_message << '\n';
            return afd.setInitialState(-2);
        }
        std::cout << "--------------------- Reading " << __file << " ---------------------" << '\n';
        if (!file.is_open()) { //* error checking for file opening
            std::cerr << ERR "ERROR : Erreur lors de l'ouverture du fichier." NC << '\n';
            std::cerr << caution_message << '\n';
            return afd.setInitialState(-2); //* return an empty afd
        }
        std::cout << GRN "SUCCESS : Fichier ouvert avec succes." NC << '\n';
        std::string line;
        int state, count = 0;
        char symbol, id;
        int nextState;
        while (getline(file, line)) { //* reads each line of the file
            line.erase(line.find_last_not_of(" \n\r\t") + 1); //* removes trailing whitespaces
            count++;
            if (line.empty() || line[0] == '#') //* skips empty lines and comments
                continue;
            switch (line[0]) { //* checks the first character of the line
                case 'I' : //* initial state
                    if (isalpha(line[2])) {
                        std::cout << ERR "Erreur de syntax : " << count << " - l'etat initial (I)." NC << '\n';
                        return afd.setInitialState(-1); //* return a corrupted afd
                    }
                    state = stoi(line.substr(2, line.size() - 2));
                    afd.setInitialState(state);
                    break;
                case 'A' : //* alphabet
                    for (int i = 2; i < line.size(); i = i + 2) {
                        if (!isalpha(line[i])) {
                                std::cout << ERR "Erreur de syntax : " << count << " - l'alphabet (A)." NC << '\n';
                                return afd.setInitialState(-1);
                            }
                        afd.addAlphabet(line[i]);
                    }
                    break;
                case 'F' : //* final states
                    for (int i = 2; i < line.size(); i = i + 2) {
                            if (isalpha(line[i])) {
                                std::cout << ERR "Erreur de syntax : " << count << " - les etats finaux (F)." NC << '\n';
                                return afd.setInitialState(-1);
                            }
                            state = stoi(line.substr(i, 1));
                            afd.addFinalState(state);
                    }
                    break;
                case 'E' : //* states line
                    for (int i = 2; i < line.size(); i = i + 2) {
                            if (isalpha(line[i])) {
                                std::cout << ERR "Erreur de syntax : " << count << " - les états (E)." NC << '\n';
                                return afd.setInitialState(-1);
                            }
                            state = stoi(line.substr(i, 1));
                            afd.addState(state);
                    }
                    break;
                case 't' : //* transitions line
                    try {
                    state = stoi(line.substr(2, 1));
                    symbol = line[4];
                    nextState = stoi(line.substr(6, 1));
                    afd.addTransition(transition(state, symbol, nextState));
                    break;
                    } catch (exception& e) {
                        std::cout << ERR "Erreur de syntax : " << count << " - la transition (t)." NC << '\n';
                        return afd.setInitialState(-1);
                    }
                default :
                    std::cout <<  ERR "Erreur de syntax : " << count << " - ligne non reconnue" NC << '\n';
                    return afd.setInitialState(-1);
            }
        }
        file.close();
        return afd; //* return the loaded afd
    }
    inline void printProtocol() {
        using namespace output;
        printSpacing();
        std::cout << "Dans le fichier txt. Vous devez saisir en respectant ce protocol : \n";
        printSpacing();
        printInTable({"I", "A", "F", "E", "t"}, {"Initial state", "Alphabet", "Final states", "States", "Transitions"});
        printSpacing();
    }
    template <typename T>
    inline std::string mirror(const T& __input) {
        std::string input(__input);
        std::reverse(input.begin(), input.end());
        return input;
    }
    template <typename T>
    inline bool isPalindrome(const T& __input) {
        const std::string input(__input);
        return input == mirror(input);
    }
}