#include <stdexcept>

#include "Automaton.h"
#include "States.h"
#include "symbols/expressions/ExprPlus.h"

bool E0::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::NUMBER:
            automaton.shift(symbol, new E3);
        case Symbol::PAROPEN:
            automaton.shift(symbol, new E2);
            break;
        case Symbol::EXPRESSION:
            automaton.shift(symbol, new E1);
            break;
        default:
            throw new std::domain_error("Invalid symbol for E0");
    }
    return false;
}

bool E1::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::PLUS:
            automaton.shift(symbol, new E4);
            break;
        case Symbol::MULT:
            automaton.shift(symbol, new E5);
            break;
        case Symbol::END:
            return true;
        default:
            throw new std::domain_error("Invalid symbol for E1");
    }
    return false;
}

bool E2::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::NUMBER:
            automaton.shift(symbol, new E3);
            break;
        case Symbol::PAROPEN:
            automaton.shift(symbol, new E2);
            break;
        case Symbol::EXPRESSION:
            automaton.shift(symbol, new E6);
            break;
        default:
            throw new std::domain_error("Invalid symbol for E2");
    }
    return false;
}

bool E3::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::PLUS:
            automaton.reduce(1, symbol);
            break;
        case Symbol::MULT:
            break;
        case Symbol::EXPRESSION:
            break;
        default:
            throw new std::domain_error("Invalid symbol for E3");
    }
    return false;
}

bool E4::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::NUMBER:
            automaton.shift(symbol, new E3);
        case Symbol::PAROPEN:
            automaton.shift(symbol, new E2);
            break;
        case Symbol::EXPRESSION:
            automaton.shift(symbol, new E7);
            break;
        default:
            throw new std::domain_error("Invalid symbol for E4");
    }
    return false;
}

bool E5::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::NUMBER:
            automaton.shift(symbol, new E3);
        case Symbol::PAROPEN:
            automaton.shift(symbol, new E2);
            break;
        case Symbol::EXPRESSION:
            automaton.shift(symbol, new E8);
            break;
        default:
            throw new std::domain_error("Invalid symbol for E5");
    }
    return false;
}

bool E6::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::MULT:
            automaton.shift(symbol, new E5);
            break;
        case Symbol::PLUS:
            automaton.shift(symbol, new E4);
            break;
        case Symbol::PARCLOSE:
            automaton.shift(symbol, new E9);
            break;
        default:
            throw new std::domain_error("Invalid symbol for E6");
    }
    return false;
}

bool E7::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::MULT:
            automaton.shift(symbol, new E5);
            break;
        case Symbol::PLUS:
            break;
        case Symbol::PARCLOSE:
            break;
        case Symbol::END:
            break;
        default:
            throw new std::domain_error("Invalid symbol for E7");

    }
    return false;
}

bool E8::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::MULT:
            break;
        case Symbol::PLUS:
            break;
        case Symbol::PARCLOSE:
            break;
        case Symbol::END:
            break;
        default:
            throw new std::domain_error("Invalid symbol for E8");

    }
    return false;
}

bool E9::transition(Automaton & automaton, Symbol * symbol){
    switch (*symbol) {
        case Symbol::MULT:
            break;
        case Symbol::PLUS:
            break;
        case Symbol::PARCLOSE:
            break;
        case Symbol::END:
            break;
        default:
            throw new std::domain_error("Invalid symbol for E9");

    }
    return false;
}
