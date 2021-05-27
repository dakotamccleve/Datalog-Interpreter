//
// Created by dakot on 5/25/2021.
//

#ifndef CS236_PROJECT_3_INTERPRETER_H
#define CS236_PROJECT_3_INTERPRETER_H

#include "Database.h"
#include "DatalogProgram.h"


class Interpreter {
public:
    Interpreter(DatalogProgram dataprog, Database database);

private:
    Database db;
    DatalogProgram program;

};


#endif //CS236_PROJECT_3_INTERPRETER_H
