//
// Created by dakot on 5/15/2021.
//

#include "Rule.h"


std::string Rule::toString() {
    std::stringstream ss;
    for(unsigned int i = 0; i < this->predicateList.size(); i++) {
        ss << this->predicate->toString() << " :- ";
        for (unsigned int j = 0; j < predicateList.size(); j++) {
            ss << predicateList.at(j)->toString();
            if (j < predicateList.size() - 1) {
                ss << ',';
            }
        }

        ss << ".\n";
        return ss.str();
    }
    return "";
}