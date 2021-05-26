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
    Relation(std::string tableName, Header newHead) {header = newHead; name = tableName;}
    std::string toString();
    std::string getName() {return name;}
    std::set<Tuple> getTuples() {return tupleSet;}
    

private:
    std::string name;
    std::set<Tuple> tupleSet;
    Header header;


};


#endif //CS236_PROJECT_3_RELATION_H
