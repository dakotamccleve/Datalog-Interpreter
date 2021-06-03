//
// Created by dakot on 5/25/2021.
//

#ifndef CS236_PROJECT_3_INTERPRETER_H
#define CS236_PROJECT_3_INTERPRETER_H

#include "Database.h"
#include "DatalogProgram.h"


class Interpreter {
public:
    explicit Interpreter(DatalogProgram dataprog);
    void createRelations(std::vector<Predicate*> schemes);
    void createTuples(std::vector<Predicate*> facts);
    Relation matchRelationFromQuery(Predicate* query);
    void evalQueries(std::vector<Predicate*> queries);

private:
    Database db;
    std::vector<Tuple> tuples;
    std::vector<Relation> relations;

};


#endif //CS236_PROJECT_3_INTERPRETER_H
