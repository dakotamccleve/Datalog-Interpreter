//
// Created by dakot on 5/25/2021.
//

#ifndef CS236_PROJECT_3_RELATION_H
#define CS236_PROJECT_3_RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <set>
#include <string>

class Relation {
public:
    Relation(std::string tableName, std::vector<std::string> newHeaders);
    std::string toString();
    void addTuple(const Tuple& tuple);
    void select(int index, std::string value);
    void select(int index, int index2);
    void project();


    /*  std::string getName() {return name;}
    std::set<Tuple> getTuples() {return tupleSet;}
    Header getHeader() {return header;}
    */


private:
    std::string name;
    std::set<Tuple> tupleSet;
    std::vector<std::string> headers;


};


#endif //CS236_PROJECT_3_RELATION_H
