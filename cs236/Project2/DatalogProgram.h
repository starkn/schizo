#pragma once

#include <vector>
#include <iostream>
//#include <sstream>
#include <string>

#include "Predicate.h"
#include "Rule.h"

using namespace std;

class DatalogProgram
{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
public:
    DatalogProgram(/* args */);
    ~DatalogProgram();

    void addScheme(Predicate scheme);
    void addFact(Predicate fact);
    void addRule(Rule rule);
    void addQuery(Predicate query);

    string toString();
};

DatalogProgram::DatalogProgram(/* args */)
{
}

DatalogProgram::~DatalogProgram()
{
}

void DatalogProgram::addScheme(Predicate scheme)
{
    schemes.push_back(scheme);
}

void DatalogProgram::addFact(Predicate fact)
{
    facts.push_back(fact);
}

void DatalogProgram::addRule(Rule rule)
{
    rules.push_back(rule);
}

void DatalogProgram::addQuery(Predicate query)
{
    queries.push_back(query);
}


string DatalogProgram::toString()
{
    stringstream out;
    out << "Success!!\n";
    out << "Schemes (" << schemes.size() << "):\n";
    for(Predicate scheme : schemes)
    {
        out << scheme.toString();
    }
    out << "Facts (" << facts.size() << "):\n";
    for (Predicate fact : facts)
    {
        out << fact.toString();
    }
    out << "Facts (" << facts.size() << "):\n";
    for (Predicate fact : facts)
    {
        out << fact.toString();
    }
    out << "Queries (" << queries.size() << "):\n";
    for (Predicate query : queries)
    {
        out << query.toString();
    }

    return out.str();
}