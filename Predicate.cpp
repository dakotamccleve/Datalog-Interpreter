//
// Created by dakot on 5/15/2021.
//

#include "Predicate.h"

std::string Predicate::toString() {
    std::stringstream ss;
    ss << name << '(';
    for(unsigned int i = 0; i < parameters.size(); i++) {
        ss << parameters.at(i)->toString();
        if (i < parameters.size()-1) {
            ss << ',';
        }
    }
    ss << ")";
    return ss.str();
}