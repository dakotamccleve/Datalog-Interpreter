//
// Created by dakot on 5/4/2021.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string &input) {
    if (input[inputRead] == '#') {
        inputRead++;
        S1(input);
    }

    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string &input) {
    if (input[inputRead] == '|') {
        inputRead++;
        S2(input);
    }

    else while ( inputRead != (int)input.size() && input[inputRead] != '\n') {
        inputRead++;
    }

    if (input[inputRead] == '\n') {
        return;
    }

    if (inputRead == (int)input.size() ) {
        return;
    }
}

void CommentAutomaton::S2(const std::string &input) {
    while (inputRead != (int)input.size() && input[inputRead] != '|') {
        if(input[inputRead] == '\n') {
            this->newLines++;
        }
        inputRead++;
    }
    if (input[inputRead] == '|') {
        inputRead++;
        if (input[inputRead] == '#') {
            inputRead++;
            return;
        }
        else S2(input);
    }
    if (inputRead == (int)input.size() ) {
        type = UNDEFINED;
        return;
    }
}