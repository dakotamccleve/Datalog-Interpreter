//
// Created by dakot on 5/25/2021.
//

#ifndef CS236_PROJECT_3_DATABASE_H
#define CS236_PROJECT_3_DATABASE_H

#include "Relation.h"
#include <map>

class Database {
public:
    void addRelation(std::string name, Relation relation);
    std::map<std::string, Relation> tables;
    void getRelations();

};


#endif //CS236_PROJECT_3_DATABASE_H
