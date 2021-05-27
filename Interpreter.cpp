//
// Created by dakot on 5/25/2021.
//

#include "Interpreter.h"


Interpreter::Interpreter(DatalogProgram dataprog) {
    /* TODO: createRelations
     * TODO: createTuples
     * TODO: addRelation
     * TODO: evalQueries
     */
}

void createRelations(std::vector<Predicate*> schemes);
void createTuples(std::vector<Predicate*> facts);
Relation matchRelationFromQuery(Predicate* query);
void evalQueries(std::vector<Predicate*> queries);