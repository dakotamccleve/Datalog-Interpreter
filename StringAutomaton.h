//
// Created by dakot on 5/4/2021.
//

#ifndef CS236_PROJECT_1_STRINGAUTOMATON_H
#define CS236_PROJECT_1_STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton {
private:
    void S1(const std::string& input);
    void S2(const std::string& input);

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}

    void S0(const std::string& input);
    bool isApostrophe(const std::string input);
};


#endif //CS236_PROJECT_1_STRINGAUTOMATON_H
