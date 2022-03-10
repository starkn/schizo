#pragma once

#include <string>
#include <sstream>
#include <vector>

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
    stringstream ss;
    ss << q.toString() << endl;

    for(auto param : q.paramList)
    {
        if(param.toString().at(0) == '\'') {
            //ss << param.toString() << endl;
        }
    }
    
    for (unsigned int i = 0; i < relations.size(); i++)
    {
        //cout << relations[i].toString() << endl;

        if (relations[i].getName() == q.ID)
        {
            Relation rel = relations[i].select(0, "'b'");
            ss << rel.toString();
        }
    }


    return ss.str();
}