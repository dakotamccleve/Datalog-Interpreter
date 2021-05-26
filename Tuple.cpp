//
// Created by dakot on 5/25/2021.
//

#include "Tuple.h"

Tuple::Tuple(std::string name, std::vector<std::string> values) {
    relationName = name;
    tupleValues = values;
}

void Tuple::addValue(std::string value) {
    tupleValues.push_back(value);
}

std::vector<std::string> Tuple::getValues() {
    return tupleValues;
}

bool Tuple::operator< (const Tuple & other) const {
    //TODO: BUILD LESS THAN OPERATOR
}