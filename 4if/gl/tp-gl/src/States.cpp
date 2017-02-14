#include <stdexcept>

#include "Automaton.h"
#include "States.h"
#include "symbols/expressions/ExprNumber.h"
#include "symbols/Number.h"
#include "symbols/expressions/ExprPlus.h"
#include "symbols/expressions/ExprMult.h"

bool E0::transition(Automaton & automaton, Symbol * symbol) {
    switch (*symbol) {
        case Symbol::NUMBER:
            automaton.shift(symbol, new E3);
            break;
        case Symbol::PAROPEN:
            automaton.shift(symbol, new E2);
            break;
        case Symbol::EXPRESSION:
            automaton.shift(symbol, new E1);
            break;
        default:
            throw std::domain_error("Invalid symbol for E0");
    }
    return false;
}

bool E1::transition(Automaton & automaton, Symbol * symbol) {
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
            throw std::domain_error("Invalid symbol for E1");
    }
    return false;
}

bool E2::transition(Automaton & automaton, Symbol * symbol) {
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
            throw std::domain_error("Invalid symbol for E2");
    }
    return false;
}

bool E3::transition(Automaton & automaton, Symbol * symbol) {
    switch (*symbol) {
        case Symbol::PLUS:
        case Symbol::MULT:
        case Symbol::PARCLOSE:
        case Symbol::END:
            automaton.reduce(
                    1, new ExprNumber(
                            static_cast<Number *>(automaton.pop())->getValue()
                    ), symbol
            );
            break;
        default:
            throw std::domain_error("Invalid symbol for E3");
    }
    return false;
}

bool E4::transition(Automaton & automaton, Symbol * symbol) {
    switch (*symbol) {
        case Symbol::NUMBER:
            automaton.shift(symbol, new E3);
            break;
        case Symbol::PAROPEN:
            automaton.shift(symbol, new E2);
            break;
        case Symbol::EXPRESSION:
            automaton.shift(symbol, new E7);
            break;
        default:
            throw std::domain_error("Invalid symbol for E4");
    }
    return false;
}

bool E5::transition(Automaton & automaton, Symbol * symbol) {
    switch (*symbol) {
        case Symbol::NUMBER:
            automaton.shift(symbol, new E3);
            break;
        case Symbol::PAROPEN:
            automaton.shift(symbol, new E2);
            break;
        case Symbol::EXPRESSION:
            automaton.shift(symbol, new E8);
            break;
        default:
            throw std::domain_error("Invalid symbol for E5");
    }
    return false;
}

bool E6::transition(Automaton & automaton, Symbol * symbol) {
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
            throw std::domain_error("Invalid symbol for E6");
    }
    return false;
}

bool E7::transition(Automaton & automaton, Symbol * symbol) {
    switch (*symbol) {
        case Symbol::MULT:
            automaton.shift(symbol, new E5);
            break;
        case Symbol::PLUS:
        case Symbol::PARCLOSE:
        case Symbol::END:
        {
            ExprNumber * left = static_cast<ExprNumber *>(automaton.pop());
            Symbol * op = automaton.pop();
            ExprNumber * right = static_cast<ExprNumber *>(automaton.pop());
            if (*op == Symbol::PLUS)
            {
                automaton.reduce(3, new ExprPlus(left, right), symbol);
            }
            else if (*op == Symbol::MULT)
            {
                automaton.reduce(3, new ExprMult(left, right), symbol);
            }
            else
            {
                throw std::domain_error("Unexpected operator");
            }
            break;
        }
        default:
            throw std::domain_error("Invalid symbol for E7");
    }
    return false;
}

bool E8::transition(Automaton & automaton, Symbol * symbol) {
    switch (*symbol) {
        case Symbol::MULT:
        case Symbol::PLUS:
        case Symbol::PARCLOSE:
        case Symbol::END:
        {
            ExprNumber * left = static_cast<ExprNumber *>(automaton.pop());
            Symbol * op = automaton.pop();
            ExprNumber * right = static_cast<ExprNumber *>(automaton.pop());
            if (*op == Symbol::PLUS)
            {
                automaton.reduce(3, new ExprPlus(left, right), symbol);
            }
            else if (*op == Symbol::MULT)
            {
                automaton.reduce(3, new ExprMult(left, right), symbol);
            }
            else
            {
                delete op;
                throw std::domain_error("Unexpected operator");
            }
            delete op;
            break;
        }
        default:
            throw std::domain_error("Invalid symbol for E8");

    }
    return false;
}

bool E9::transition(Automaton & automaton, Symbol * symbol) {
    switch (*symbol) {
        case Symbol::MULT:
        case Symbol::PLUS:
        case Symbol::PARCLOSE:
        case Symbol::END:
        {
            automaton.popAndDestroy();
            Expression * expression = static_cast<Expression *>(automaton.pop());
            automaton.popAndDestroy();
            automaton.reduce(3, expression, symbol);
            break;
        }
        default:
            throw std::domain_error("Invalid symbol for E9");

    }
    return false;
}
