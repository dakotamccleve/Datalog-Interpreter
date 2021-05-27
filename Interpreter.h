//
// Created by dakot on 5/25/2021.
//

#ifndef CS236_PROJECT_3_INTERPRETER_H
#define CS236_PROJECT_3_INTERPRETER_H

#include "Database.h"
#include "DatalogProgram.h"


class Interpreter {
public:
    Interpreter(DatalogProgram dataprog);
    void createRelations(std::vector<Predicate*> schemes);
    void createTuples(std::vector<Predicate*> facts);

private:
    Database db;
    DatalogProgram program;
    std::vector<Tuple> tuples;
    std::vector<Relation> relations;

};


#endif //CS236_PROJECT_3_INTERPRETER_H
