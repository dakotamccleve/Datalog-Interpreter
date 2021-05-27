//
// Created by dakot on 5/25/2021.
//

#ifndef CS236_PROJECT_3_RELATION_H
#define CS236_PROJECT_3_RELATION_H

#include "Tuple.h"
#include <set>
#include <string>
#include <sstream>

class Relation {
public:
    Relation() = default;
    Relation(std::string tableName, std::vector<std::string> newHeaders);
    std::string toString();
    void addTuple(const Tuple& tuple);
    std::string getName();
    std::set<Tuple> getTuples();
    Relation select(int index, std::string value);
    Relation select(int index, int index2);
    Relation project(std::vector<int> indices);
    Relation rename(std::vector<std::string> IDs);
    int numOfTuples(std::vector<std::string> vars);
    void presentTuples(std::vector<int> positions, std::vector<std::string> IDs, int number);


private:
    std::string name;
    std::set<Tuple> tupleSet = {};
    std::vector<std::string> headers ;


};


#endif //CS236_PROJECT_3_RELATION_H
