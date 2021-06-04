//
// Created by dakot on 5/25/2021.
//

#include "Interpreter.h"


Interpreter::Interpreter(DatalogProgram dataprog) {
    createRelations(dataprog.getSchemes());
    createTuples(dataprog.getFacts());
    for(Relation r : relations) {
        db.addRelation(r.getName(), r);
    }
    evaluateRules(dataprog.getRules());
    std::cout << "Query Evaluation" << std::endl;
    evalQueries(dataprog.getQueries());
}

void Interpreter::createRelations(std::vector<Predicate*> schemes) {
    for(Predicate* s : schemes) {
        relations.push_back(Relation(s->getName(), s->getParamAsStr()));
    }
}

void Interpreter::createTuples(std::vector<Predicate*> facts) {
    for (Predicate* f : facts) {
        tuples.push_back(Tuple(f->getName(), f->getParamAsStr()));
    }
    unsigned int i = 0;
    for (Tuple t: tuples) {
        i = 0;
        while ((t.getRelationName() != relations[i].getName() || i == relations.size())) {
            i++;
        }
        if (t.getRelationName() == relations[i].getName()) {
            t.setRelationName(relations[i].getName());
            relations[i].addTuple(t);
        }
    }
}

Relation Interpreter::matchRelationFromQuery(Predicate* query) {
    unsigned int i = 0;
    while((query->getName() != relations[i].getName()) || i == relations.size()) {
        i++;
    }
    if(query->getName() == relations[i].getName()) {
        return relations[i];
    }
    else return {};
}

void Interpreter::evalQueries(std::vector<Predicate*> queries) {
    for(Predicate* q : queries) {
        std::vector<int> indices;
        Relation matchRel;
        std::vector<std::string> queryVars;
        matchRel = matchRelationFromQuery(q);
        std::vector<Parameter *> qParams = q->getParameters();
        int dupPos = 0;
        for (unsigned int i = 0; i < qParams.size(); i++) {
            std::string tType = qParams[i]->getTokens().getTokenType();
            std::string tData = qParams[i]->getTokens().getData();
            bool isDuplicateVar = false;
            if (tType == "STRING") {
                matchRel = matchRel.select(i, tData);
            }
            else if (tType == "ID") {
                for (unsigned int j = 0; j < queryVars.size(); j++) {
                    if (queryVars[j] == tData) {
                        isDuplicateVar = true;
                        dupPos = j;
                    }
                }
            }
            if(isDuplicateVar) {
                matchRel = matchRel.select(dupPos, i);
            }
            else {
                queryVars.push_back(tData);
                indices.push_back(i);
            }
        }
        matchRel = matchRel.project(indices);
        matchRel = matchRel.rename(queryVars);

        //Output queries below

        std::stringstream ss;
        for(unsigned int i = 0; i < qParams.size(); i++) {
            ss << qParams[i]->toString();
            if(i != (qParams.size() - 1)) {
                ss << ",";
            }
        }
        int num = matchRel.numOfTuples(queryVars);
        std::cout << matchRel.getName() << "(" << ss.str() << ")?";
        if(matchRel.getTuples().size() > 0) {
            std::cout << " Yes(" << num << ")" << std::endl;
        }
        else {
            std::cout << " No" << std::endl;
        }
        matchRel.presentTuples(indices, queryVars, num);
    }
}

std::string Interpreter::evaluateRules(std::vector<Rule*> rules) {
    Relation returnRel;
    std::vector<Relation> intermedRels;
    for(unsigned int i = 0; i < rules.size(); i++) {
        returnRel = evalPredicate(rules.at(i)->getPredicateList().at(0));
        for(unsigned int j =  1; j < rules.at(i)->getPredicateList().size(); j++) {
           intermedRels.push_back(evalPredicate(rules.at(i)->getPredicateList().at(j)));
        }
        if (intermedRels.size() > 0) {
            for (unsigned int j = 0; j < intermedRels.size(); j++) {
               returnRel = returnRel.join(intermedRels.at(j));
            }
        }
        std::cout << "RELACION: "<< returnRel.toString();
    }
    return "";
}

Relation Interpreter::evalPredicate(Predicate* queries) {
    Relation matchRel;
        std::vector<int> indices;
        std::vector<std::string> queryVars;
        matchRel = matchRelationFromQuery(queries);
        std::vector<Parameter *> qParams = queries->getParameters();
        int dupPos = 0;
        for (unsigned int i = 0; i < qParams.size(); i++) {
            std::string tType = qParams[i]->getTokens().getTokenType();
            std::string tData = qParams[i]->getTokens().getData();
            bool isDuplicateVar = false;
            if (tType == "STRING") {
                matchRel = matchRel.select(i, tData);
            } else if (tType == "ID") {
                for (unsigned int j = 0; j < queryVars.size(); j++) {
                    if (queryVars[j] == tData) {
                        isDuplicateVar = true;
                        dupPos = j;
                    }
                }
            }
            if (isDuplicateVar) {
                matchRel = matchRel.select(dupPos, i);
            } else {
                queryVars.push_back(tData);
                indices.push_back(i);
            }
        }
        matchRel = matchRel.project(indices);
        matchRel = matchRel.rename(queryVars);

    return matchRel;
}