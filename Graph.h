//
// Created by dakot on 6/11/2021.
//

#ifndef CS236_PROJECT_5_GRAPH_H
#define CS236_PROJECT_5_GRAPH_H

#include "DatalogProgram.h"
#include "Database.h"
#include <map>
#include <set>
#include <stack>

class Graph {
public:
    Graph() {};
    void createGraph(std::vector<Rule*> rules);
    void dfs();
    void dfsForestSCC();
    void dfsForestPostOrder();
    void toString();
    void reverseToString();
    void addEdge(int i, int j);
    std::stack<int> topologicalSort; //postOrder reversal

private:
    std::map<int,std::set<int>> adjacencyList; //first int is rule index, set is all rules that rule index is adjacent to
    std::map<int,std::set<int>> reverseList;
};

//make two graph objects, a forward and a reverse graph.

/*
    Build the dependency graph and the reverse dependency graph.
    Run DFS-Forest on the reverse dependency graph to get the post-order.
    Use the post-order for a DFS-Forest on the forward dependency graph to find the strongly connected components (SCCs).
    Evaluate the rules in each component.
*/



#endif //CS236_PROJECT_5_GRAPH_H
