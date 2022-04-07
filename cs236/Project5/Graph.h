#pragma once

#include <map>
#include <sstream>
#include <stack>

#include "Node.h"

using namespace std;

class Graph
{
private:
    map<int, Node> nodes;
public:
    Graph(int s);

    void addEdge(int fromNodeID, int toNodeID)
    {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    string toString() 
    {
        stringstream out;


        for(auto& pair : nodes) {
            int nodeID = pair.first;
            Node node = pair.second;

            out << "R" << nodeID << ":" << node.toString() << endl;
        }


        return out.str();
    }

    Graph reverse()
    {
        Graph rev(nodes.size());

        for(auto& pair : nodes) {
            int toNode = pair.first;
            Node node = pair.second;
            for(auto& fromNode : node.getAdjNodes()) {
                rev.addEdge(fromNode, toNode);
            }
        }
        return rev;
    }

    stack<int> dfs(stack<int> s, int id) {
        //cout << "Visiting Node " << id << endl;
        if(nodes[id].isVisited()) {
            //cout << "Already Visited" << endl;
            return s;
        }
        nodes[id].visit(true);
        for (auto &adj : nodes[id].getAdjNodes())
        {
            s = dfs(s, adj);
        }
        s.push(id);
        return s;
    }

    int size() {
        return nodes.size();
    }
};

Graph::Graph(int s)
{
    for(int nodeID = 0; nodeID < s; nodeID++) {
        nodes[nodeID] = Node();
    }
}

