//
// Created by dakot on 5/4/2021.
//

#include "IDAutomaton.h"
#include <cctype>

void IDAutomaton::S0(const std::string &input) {
    if (isalpha(input.at(0))){
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string &input) {
    if (isalpha(input.at(index)) || isdigit(input.at(index))){
        inputRead++;
        index++;
        if(inputRead == (int)input.size()) {
            return;
        }
        else {S1(input);}
    }
}