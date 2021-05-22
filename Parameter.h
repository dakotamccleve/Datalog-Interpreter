//
// Created by dakot on 5/15/2021.
//

#pragma once
#include "Token.h"

class Parameter {
public:
    Parameter();
    ~Parameter();
    Parameter(Token* token) {
        this->token = token;
    }
    std::string toString();

private:
    Token* token;

};
