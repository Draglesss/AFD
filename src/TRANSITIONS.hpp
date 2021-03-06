#include <iostream>
#include <string>
#pragma once

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
    friend std::ostream& operator<<(std::ostream& os, const transition& t) {
        os << "t(" << t.state << "," << t.symbol << "," << t.nextState << ")";
        return os;
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
        std::cout << "t" << "(" << this->state << "," << this->symbol << "," << this->nextState << ")" << std::endl;
    }
};
