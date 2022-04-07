#pragma once

#include <set>
#include <string>
#include <sstream>

using namespace std;

class Node
{
private:
    set<int> adjacentNodeIDs;
    bool visited;
public:
    Node(/* args */);

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    string toString() {
        stringstream out;
        for (auto& nodeID : adjacentNodeIDs) {
            out << "R" << nodeID << ",";
        }
        string s = out.str();
        if(s.size() > 1)
            s.pop_back();
        return s;
    }

    set<int> getAdjNodes() {
        return adjacentNodeIDs;
    }

    void visit(bool v = true) {
        visited = v;
    }

    bool isVisited() {
        return visited;
    }
};

Node::Node(/* args */)
{
    visited = false;
}
