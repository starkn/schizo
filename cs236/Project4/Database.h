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
    Database(vector<Predicate> s, vector<Predicate> f);
    Database();

    int size();

    string printQueries();

    void parseSchemes(vector<Predicate> s);
    void fillRelations(vector<Predicate> f);
    void joinRelations();

    Relation doQuery(Predicate q, bool quiet);
    string evalRule(Rule rule);
};

Database::Database(vector<Predicate> s, vector<Predicate> f)
{
    parseSchemes(s);
    fillRelations(f);
}

Database::Database() { }

int Database::size() {
    int size = 0;
    for(Relation relation : relations) {
        size += relation.size();
    }
    return size;
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

Relation Database::doQuery(Predicate q, bool quiet = false)
{
    map<int, string> var;
    map<int, string> con;

    stringstream ss;
    if(!quiet)
        cout << q.toString() << "? ";


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
    if(!quiet) {
        // If there are no return relations output No
        if(rel.size() == 0) {
            cout << "No" << endl;
        }
        // If there are no variables there is no need to print the relation
        else if (var.size() == 0) {
            cout << "Yes(" << rel.size() << ")" << endl;  
        }
        // Print the variable values in a relations format
        else {
            if(!quiet)
                cout << "Yes(" << rel.size() << ")" << endl;
            cout << rel.toString();
        }
    }

    return rel;
}

string Database::evalRule(Rule rule)
{
    stringstream out;

    vector<Relation> rs;

    cout << rule.toString() << "." << endl;

    for(auto pred : rule.getPredicates()) {
        rs.push_back(doQuery(pred, true));
    }
    
    if(rs.size() != 0) {
        for(unsigned int i = 1; i < rs.size(); i++) {
            rs[0].join(rs[i]);
        }



        for(auto &relation : relations) {
            if(rule.getHead().ID == relation.getName()) {
                Relation n(relation.getName(), relation.getScheme());
                rs[0].projectv2(rule, relation);
                for(auto & tuple : rs[0].getTuples()) {
                    if(relation.getTuples().count(tuple) == 0) {
                        n.addTuple(tuple);
                        relation.addTuple(tuple);
                    }
                }
                cout << n.toString();
                //relation.uni(rs[0]);
                //cout << relation.toString() << endl;
                break;
            }
        }
    }

    return out.str();
}