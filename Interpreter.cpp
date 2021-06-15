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
    Graph graph;
    graph.createGraph(dataprog.getRules());
    graph.toString();
    graph.dfsForestPostOrder();
    graph.dfsForestSCC();
    evaluateRules(dataprog.getRules(), graph);
    std::cout << std::endl << "Query Evaluation" << std::endl;
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
    while((query->getName() != db.tables.at(query->getName()).getName()) || i == db.tables.size()) {
        i++;
    }
    if((query->getName() == db.tables.at(query->getName()).getName())) {
        return db.tables.at(query->getName());
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

void Interpreter::evaluateRules(std::vector<Rule*> rules, Graph graph) {
    std::cout << "Rule Evaluation" << std::endl;
    for(unsigned int b = 0; b < graph.scc.size(); b++) {
        std::vector<Rule*> sccRules;
        int passTimes = 0;
        bool keepGoing = true;
        std::cout << "SCC: ";
        unsigned int counter = 0;
        for (auto it : graph.scc.at(b)) {
            std::cout << "R" << it;
            sccRules.push_back(rules.at(it));
            counter++;
            if (counter < graph.scc.at(b).size()) {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
        while (keepGoing) {
            passTimes++;
            keepGoing = false;
            bool addedToDB = false;

            for (unsigned int i = 0; i < sccRules.size(); i++) {
                Relation returnRel;
                std::vector<Relation> intermedRels;
                std::vector<int> headPredIndices;
                std::vector<std::string> headPredsToRename;
                std::cout << sccRules.at(i)->toString();
                returnRel = evalPredicate(sccRules.at(i)->getPredicateList().at(0));
                for (unsigned int j = 1; j < sccRules.at(i)->getPredicateList().size(); j++) {
                    intermedRels.push_back(evalPredicate(sccRules.at(i)->getPredicateList().at(j)));
                }
                if (intermedRels.size() > 0) {
                    for (unsigned int j = 0; j < intermedRels.size(); j++) {
                        returnRel = returnRel.join(intermedRels.at(j));
                    }
                }
                for (unsigned int j = 0; j < sccRules.at(i)->getHeadPredicate()->getParameters().size(); j++) {
                    for (unsigned int k = 0; k < returnRel.getHeaders().size(); k++) {
                        if (returnRel.getHeaders().at(k) ==
                            sccRules.at(i)->getHeadPredicate()->getParameters().at(j)->getTokens().getData()) {
                            headPredIndices.push_back(k);
                            headPredsToRename.push_back(
                                    sccRules.at(i)->getHeadPredicate()->getParameters().at(j)->toString());
                        }
                    }
                }
                returnRel = returnRel.project(headPredIndices);
                returnRel = returnRel.rename(headPredsToRename);
                returnRel.setName(sccRules.at(i)->getHeadPredicate()->getName());

                if (db.tables.at(returnRel.getName()).unite(returnRel)) {
                    keepGoing = true;
                    addedToDB = true;
                }
                for(auto u : graph.scc.at(b)) {
                    if(graph.adjacencyList.at(u).empty()) {
                        keepGoing = false;
                    }
                    for(auto y : graph.adjacencyList.at(u)) {
                        if((y == u && addedToDB)) {
                            keepGoing = true;
                            break;
                        }
                        else {
                            keepGoing = false;
                        }
                    }
                }
                if(graph.scc.at(b).size() > 1 && addedToDB) {
                    keepGoing = true;
                }
            }
        }
        std::cout << passTimes << " passes: ";
        unsigned int whatever = 0;
        for (auto it : graph.scc.at(b)) {
            std::cout << "R" << it;
            whatever++;
            if (whatever < graph.scc.at(b).size()) {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }

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