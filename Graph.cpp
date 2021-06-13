//
// Created by dakot on 6/11/2021.
//

#include "Graph.h"

void Graph::createGraph(std::vector<Rule*> rules) {
    for(unsigned int i = 0; i < rules.size(); i++) {
        adjacencyList[i];
        reverseList[i];
    }
    for(unsigned int i = 0; i < rules.size(); i++) {
        for(unsigned int j = 0; j < rules.at(i)->getPredicateList().size(); j++) {
            for(unsigned int k = 0; k < rules.size(); k++) {
                if (rules.at(i)->getPredicateList().at(j)->getName() == rules.at(k)->getHeadPredicate()->getName()) {
                    adjacencyList[i].insert(k);
                    reverseList[k].insert(i);
                }
            }
        }
    }
}

void Graph::toString() {
    std::cout << "Dependency Graph" << std::endl;
    for(auto it : adjacencyList) {
        int commaMarker = 0;
        std::cout << "R" << it.first << ":";
        for(auto i : it.second) {
            std::cout << "R" << i;
            commaMarker++;
            if(commaMarker != it.second.size())
                std::cout << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Graph::reverseToString() {
    std::cout << "Dependency Graph" << std::endl;
    for(auto it : reverseList) {
        int commaMarker = 0;
        std::cout << "R" << it.first << ":";
        for(auto i : it.second) {
            std::cout << "R" << i;
            commaMarker++;
            if(commaMarker != it.second.size())
                std::cout << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Graph::dfs() {

}

void Graph::dfsForestPostOrder() {

}

void Graph::dfsForestSCC() {

}

void Graph::addEdge(int i, int j) {

}