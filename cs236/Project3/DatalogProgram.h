#pragma once

#include <vector>
#include <iostream>
//#include <sstream>
#include <string>

#include "Predicate.h"
#include "Rule.h"
#include "Database.h"

using namespace std;

class DatalogProgram
{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    vector<string> domains;
public:
    DatalogProgram(/* args */);
    ~DatalogProgram();

    void addScheme(Predicate scheme);
    void addFact(Predicate fact);
    void addRule(Rule rule);
    void addQuery(Predicate query);
    void addDomain(string domain);

    string toString();
    string doQueries();
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

void DatalogProgram::addDomain(string domain)
{   //bool add = true;
    if(domains.size() == 0)
    {
        domains.push_back(domain);
        return;
    }
    vector<string>::iterator iter = domains.begin();
    for(unsigned int i=0; i<=domains.size(); i++)
    {
        if (i == domains.size())
        {
            domains.insert(iter, domain);
            break;
        }

        if (domains[i] < domain)
        {
            iter++;
            continue;
        }
        if(domains[i] == domain)
            break;

        domains.insert(iter, domain);
        break;
    }
    //if(add)
      //  domains.push_back(domain);
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
    out << "Success!\n";
    out << "Schemes(" << schemes.size() << "):\n";
    for(Predicate scheme : schemes)
    {
        out << "  " << scheme.toString() << "\n";
    }
    out << "Facts(" << facts.size() << "):\n";
    for (Predicate fact : facts)
    {
        out << "  " << fact.toString() << ".\n";
    }
    out << "Rules(" << rules.size() << "):\n";
    for (Rule rule : rules)
    {
        out << "  " << rule.toString() << ".\n";
    }
    out << "Queries(" << queries.size() << "):\n";
    for (Predicate query : queries)
    {
        out << "  " << query.toString() << "?\n";
    }

    out << "Domain(" << domains.size() << "):\n";
    for (string domain : domains)
    {
        out << "  " << domain << "\n";
    }

    return out.str();
}

string DatalogProgram::doQueries()
{
    stringstream out;
    Database database(schemes, facts, rules, queries);
    
    for(auto query : queries)
        out << database.doQuery(query);

    return out.str();
}