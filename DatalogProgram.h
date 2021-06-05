//
// Created by dakot on 5/15/2021.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Rule.h"


class DatalogProgram {
private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Rule*> rules;
    std::vector<Predicate*> queries;
    std::set<std::string> domain;

public:
    DatalogProgram(){};
    ~DatalogProgram(){};
    void addScheme(Predicate* scheme) {
        schemes.push_back(scheme);
    }
    void addFact(Predicate* fact) {
        facts.push_back(fact);
    }
    void addRule(Rule* rule) {
        rules.push_back(rule);
    }
    void addQuery(Predicate* query) {
        queries.push_back(query);
    }
    void addToDomain(std::string id) {
        domain.insert(id);
    }
    std::vector<Predicate*> getSchemes() {
        return schemes;
    }
    std::vector<Predicate*> getFacts() {
        return facts;
    }
    std::vector<Rule*> getRules() {
        return rules;
    }
    std::vector<Predicate*> getQueries() {
        return queries;
    }
    std::string toString();



};

