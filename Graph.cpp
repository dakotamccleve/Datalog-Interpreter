//
// Created by dakot on 6/11/2021.
//

#include "Graph.h"

void Graph::createGraph(std::vector<Rule*> rules) {
    for(unsigned int i = 0; i < rules.size(); i++) {
        adjacencyList[i];
        visited[i];
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
        unsigned int commaMarker = 0;
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

void Graph::dfsPostOrder(int v) {
    visited.at(v) = 1;
    for(auto i : reverseList[v]) {
        if(!visited.at(i)) {
            dfsPostOrder(i);
        }
    }
    postOrder.push(v);
}

void Graph::dfsForestPostOrder() {
    for(auto i : reverseList) {
        if(!visited.at(i.first)) {
            dfsPostOrder(i.first);
        }
    }
    for(unsigned int i = 0; i < visited.size(); i++) {
    visited.at(i) = 0;
    }
}

void Graph::dfsForestSCC() {
    while(!postOrder.empty()) {
        if(!visited.at(postOrder.top())) {
            dfsSCC(postOrder.top());
        }
        if(!local.empty()) {
            scc.push_back(local);
            local.clear();
        }
        postOrder.pop();
    }
}

void Graph::dfsSCC(int v) {
    if(!visited[v]) {
        visited.at(v) = 1;
        local.insert(v);
        for (auto i : adjacencyList[v]) {
            if(!visited[i]) {
                dfsSCC(i);
            }
        }
    }
}

std::map<int,std::set<int>> Graph::getAdjList() {
    return adjacencyList;
}