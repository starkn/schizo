#pragma once

#include <vector>
#include <iostream>
//#include <sstream>
#include <string>
#include <variant>

#include "Predicate.h"
#include "Rule.h"
#include "Database.h"
#include "Graph.h"

using namespace std;

class DatalogProgram
{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    vector<string> domains;
    Database data;
public:
    DatalogProgram(/* args */);
    ~DatalogProgram();

    void addScheme(Predicate scheme);
    void addFact(Predicate fact);
    void addRule(Rule rule);
    void addQuery(Predicate query);
    void addDomain(string domain);
    void createDatabase();

    string toString();
    string doQueries();
    string evalRules();
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

void DatalogProgram::createDatabase()
{
    data = Database(schemes, facts);
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
    cout << "\nQuery Evaluation" << endl;

        for (auto query : queries)
    {
        data.doQuery(query);
    }

    return "";
}

string DatalogProgram::evalRules()
{  
    stringstream output;

    cout << "Dependency Graph" << endl;
    Graph graph = data.makeGraph(rules);
    cout << graph.toString() << endl;

    vector<set<int>> scc = data.makeSCC(graph);

    //cout << scc.size() << endl;

    cout << "Rule Evaluation" << endl;
    for(auto& nodes : scc) {
        stringstream out;
        cout << "SCC: ";

        vector<Rule> temp_rules;
            for (auto &n : nodes)
            {
                temp_rules.push_back(rules.at(n));

                out << "R" << n << ",";

            }
            string s = out.str();
            s.pop_back();
            cout << s << endl;
            if (temp_rules.size() == 1 && !temp_rules[0].dependant())
            {
                data.evalRule(temp_rules[0]);
                cout << "1 passes: " << s << endl;
            }
            else
            {

                int before = 0;
                int after = 1;
                int count = 0;
                out.clear();
                while (before != after)
                {
                    before = data.size();
                    for (auto rule : temp_rules)
                        out << data.evalRule(rule);
                    after = data.size();
                    count++;
                }
                cout << count << " passes: " << s << endl;
            }

    }

    return output.str();
}