#include <iostream>
#include <string>
#pragma once

 /** 
  * @param state The current state of the FSM
  / @param symbol The symbol to be read
  / @param nextState The next state of the FSM
 */
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
    transition setState(int state) {
        this->state = state;
        return *this;
    }
    transition setSymbol(char symbol) {
        this->symbol = symbol;
        return *this;
    }
    transition setNextState(int nextState) {
        this->nextState = nextState;
        return *this;
    }
    transition print() const {
        std::cout << *this << std::endl;
        return *this;
    }
};
