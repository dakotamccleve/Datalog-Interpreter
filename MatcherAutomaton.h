//
// Created by dakot on 5/3/2021.
//

#ifndef CS236_PROJECT_1_MATCHERAUTOMATON_H
#define CS236_PROJECT_1_MATCHERAUTOMATON_H

#include "Automaton.h"


class MatcherAutomaton : public Automaton
    {
    private:
        std::string toMatch;

    public:
        MatcherAutomaton(TokenType type, std::string toMatch) : Automaton(type) {
            this->toMatch = toMatch;
        }  // Call the base constructor

        void S0(const std::string& input);
};


#endif //CS236_PROJECT_1_MATCHERAUTOMATON_H
