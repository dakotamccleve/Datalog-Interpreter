//
// Created by dakot on 5/15/2021.
//
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include "Token.h"
#include "DatalogProgram.h"

class Parser {
private:
    DatalogProgram datalog;
    int it = 0;

public:
    Parser();
    ~Parser();

    void Parse(std::vector<Token*> tokens);
    void datalogProgram(std::vector<Token*> tokens);
    void scheme(std::vector<Token*> tokens);
    void schemeList(std::vector<Token*> tokens);
    void idList(std::vector<Token*> tokens);
    void stringList(std::vector<Token*> tokens);
    void fact(std::vector<Token*> tokens);
    void factList(std::vector<Token*> tokens);
    void rule(std::vector<Token*> tokens);
    void ruleList(std::vector<Token*> tokens);
    void query(std::vector<Token*> tokens);
    void queryList(std::vector<Token*> tokens);
    Predicate* headPredicate(std::vector<Token*> tokens);
    Predicate * predicate(std::vector<Token*> tokens);
    std::vector<Predicate *> predicateList(std::vector<Token*> tokens);
    Parameter* parameter(std::vector<Token*> tokens);
    std::vector <Parameter*> parameterList(std::vector<Token*> tokens);
    void peekToken(std::vector<Token*> tokens, std::string checkStr);
    DatalogProgram getDatalogProgram() {
        return datalog;
    }

};
