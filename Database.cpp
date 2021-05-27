//
// Created by dakot on 5/25/2021.
//

#include "Database.h"


void Database::addRelation(std::string name, Relation relation) {
    tables.insert({name, relation});
}