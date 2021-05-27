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
    std::string str;
    str += name + "( ";
    for (const std::string& h : headers) {
        str += h + ", ";
    }
    str +=")\n";
    for(Tuple t : tupleSet) {
        str += t.toString() + "\n";
    }
    return str;
}

std::string Relation::getName() {
    return name;
}

std::set<Tuple> Relation::getTuples() {
    return tupleSet;
}

Relation Relation::select(int index, std::string value) {

}
Relation select(int index, int index2);
Relation project(std::vector<int> indices);
Relation rename(std::vector<std::string> IDs);
int numOfTuples(std::vector<std::string> vars);
std::string tuplesResults(const std::vector<int>& indices, std::vector<std::string> vars, int num);