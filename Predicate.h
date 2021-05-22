//
// Created by dakot on 5/15/2021.
//

#pragma once

#include "Parameter.h"
#include <vector>
#include <sstream>

class Predicate {
public:
    Predicate(std::string name) {
        this->name = name;
    }
    void addParameter(Parameter* param) {
        parameters.push_back(param);
    }
    std::string toString();
private:
    std::string name;
    std::vector<Parameter*> parameters;
};

