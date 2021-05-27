//
// Created by dakot on 5/25/2021.
//

#include "Relation.h"

Relation::Relation(std::string tableName, std::vector<std::string> newHeaders) {
    headers = std::move(newHeaders);
    name = std::move(tableName);
}

void Relation::addTuple(const Tuple &tuple) {
    tupleSet.insert(tuple);
}

std::string Relation::toString() {

}