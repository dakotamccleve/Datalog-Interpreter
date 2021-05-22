//
// Created by dakot on 5/4/2021.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string &input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string &input) {
    while((input[index] != '\'' && inputRead < (int)input.length()) || isApostrophe(input)) {
        if (input[index] == '\n') {
            this->newLines++;
        }
        if (isApostrophe(input)) {
            inputRead++;
            index++;
        }
        inputRead++;
        index++;
        if (inputRead == (int) input.length()) {
            type = UNDEFINED;
            return;
        }
    }
    if(input[index] == '\'') {
        inputRead++;
        index++;
        return;
    }
}

bool StringAutomaton::isApostrophe(const std::string input) {
    if((int)input.size() > index+2) {
        if(input[index] == '\'' && input[index+1] == '\'') {
            return true;
        }
    }
    return false;
}
