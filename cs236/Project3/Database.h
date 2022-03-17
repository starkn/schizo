#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"

using namespace std;

class Database
{

private:
    vector<Scheme> schemes;
    vector<Relation> relations;

public:
    Database(vector<Predicate> s, vector<Predicate> f, vector<Rule> r, vector<Predicate> q);

    string printQueries();

    void parseSchemes(vector<Predicate> s);
    void fillRelations(vector<Predicate> f);
    string doQuery(Predicate q);
};

Database::Database(vector<Predicate> s, vector<Predicate> f, vector<Rule> r, vector<Predicate> q)
{
    parseSchemes(s);
    fillRelations(f);
}

string Database::printQueries()
{
    stringstream ss;
    for(auto r : relations)
        ss << r.toString() << endl;
    return ss.str();
}

void Database::parseSchemes(vector<Predicate> s)
{
    for (auto pr : s)
    {
        vector<string> strings;
        for (auto p : pr.paramList)
        {
            strings.push_back(p.toString());
        }
        Scheme scheme(strings);

        Relation relation(pr.ID, scheme);
        relations.push_back(relation);
    }
}

void Database::fillRelations(vector<Predicate> f)
{
    for (auto pr : f)
    {
        vector<string> strings;
        for (auto p : pr.paramList)
        {
            strings.push_back(p.toString());
        }
        Tuple tuple(strings);

        for(unsigned int i=0; i<relations.size(); i++) {
            if(relations[i].getName() == pr.ID) {
                relations[i].addTuple(tuple);
            }
        }
    }
}

string Database::doQuery(Predicate q)
{
    map<int, string> var;
    map<int, string> con;

    stringstream ss;
    ss << q.toString() << "? ";


    // Just initiating rel to an arbitrary relation object
    Relation rel = relations[0];

    // Sort Query params into maps of constants and variables
    for (unsigned int i = 0; i < q.paramList.size(); i++) {
        if(q.paramList[i].toString().at(0) == '\'') {
            con.insert(pair<int, string>(i, q.paramList[i].toString()));
        }
        else {
            var.insert(pair<int, string>(i, q.paramList[i].toString()));
        }
    }

    // Run query on every relation in the database
    for (unsigned int i = 0; i < relations.size(); i++) {
        if (relations[i].getName() == q.ID) {
            rel = relations[i].select(con, var);
            vector<int> toErase = rel.runVars(var);
            rel = rel.project(var, rel, toErase);
        }
    }
    // If there are no return relations output No
    if(rel.size() == 0) {
        ss << "No" << endl;
    }
    // If there are no variables there is no need to print the relation
    else if (var.size() == 0) {
        ss << "Yes(" << rel.size() << ")" << endl;  
    }
    // Print the variable values in a relations format
    else {
        ss << "Yes(" << rel.size() << ")" << endl;
        ss << rel.toString();
    }




    return ss.str();
}