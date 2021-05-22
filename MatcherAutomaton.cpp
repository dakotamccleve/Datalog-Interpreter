//
// Created by dakot on 5/3/2021.
//

#include "MatcherAutomaton.h"

void MatcherAutomaton::S0(const std::string &input) {
    bool isMatch = true;
    inputRead = 0;
    for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
        }
    }
    if(isMatch) {
        inputRead = (int)toMatch.size();
    }
}
