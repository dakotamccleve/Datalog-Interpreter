//
// Created by dakot on 5/25/2021.
//

#include "Interpreter.h"


Interpreter::Interpreter(DatalogProgram dataprog, Database database) {
    program = dataprog;
    db = database;
}