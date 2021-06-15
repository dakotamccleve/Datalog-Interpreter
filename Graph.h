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
    void dfsPostOrder(int v);
    void dfsSCC(int v);
    void dfsForestPostOrder();
    void dfsForestSCC();
    void toString();
    void visitedToString();
    std::stack<int> postOrder; //postOrder reversal
    std::vector<std::set<int>> scc;
private:
    std::map<int,std::set<int>> adjacencyList; //first int is rule index, set is all rules that rule index is adjacent to
    std::map<int,std::set<int>> reverseList;
    std::map<int,bool> visited;
    std::set<int> local;
};


/* TODO:
    Run DFS-Forest on the reverse dependency graph to get the post-order.
    Use the post-order for a DFS-Forest on the forward dependency graph to find the strongly connected components (SCCs).
    Evaluate the rules in each component.
*/



#endif //CS236_PROJECT_5_GRAPH_H
