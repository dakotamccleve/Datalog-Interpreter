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

bool Tuple::operator< (const Tuple t) const {
    return tupleValues < t.tupleValues;
}

void Tuple::setRelationName(std::string name) {
    relationName = name;
}

void Tuple::setTupleValues(std::vector<std::string> tuples) {
    tupleValues = tuples;
}

std::string Tuple::getRelationName() {
    return relationName;
}

void Tuple::printTuples() {
    int j = 0;
    for (unsigned int i = 0; i < tupleValues.size(); i++) {
        if ((j%2 == 0)) {
            std::cout << "\n";
        }
        std::string output = tupleValues[i];
        std::cout << output;
        j++;
    }
    std::cout << "\n" << std::endl;
}

std::string Tuple::toString() {
    std::string str;
    str += "( ";
    for(std::string v : tupleValues) {
        str += v + ", ";
    }
    str += " )";
    return str;
}