//
// Created by dakot on 5/15/2021.
//

#pragma once
#include "Predicate.h"

class Rule {
private:
    std::string name;
    Predicate* predicate;
    std::vector<Predicate*> predicateList;
public:
    Rule(Predicate* predicate) {
        this->predicate = predicate;
    }
    Predicate* getHeadPredicate() {
        return this->predicate;
    }
    std::vector<Predicate*> getPredicateList() {
        return predicateList;
    }
    void addPredicate(Predicate* predicate) {
        predicateList.push_back(predicate);
    }
    std::string toString();

};
