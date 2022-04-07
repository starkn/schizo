#pragma once

#include <vector>

#include "Predicate.h"

using namespace std;

class Rule
{
private:
    Predicate head;
    vector<Predicate> predList;
public:
    Rule(Predicate hPred);
    ~Rule();

    void addPredicate(Predicate p);

    int size();

    Predicate getHead();
    vector<Predicate> getPredicates();
    string toString();

    bool dependant();
};

Rule::Rule(Predicate hPred)
{
    this->head = hPred;
}

Rule::~Rule()
{
}

int Rule::size() 
{
    return predList.size();
}

void Rule::addPredicate(Predicate p)
{
    predList.push_back(p);
}

Predicate Rule::getHead()
{
    return head;
}

vector<Predicate> Rule::getPredicates()
{
    return predList;
}

string Rule::toString()
{
    stringstream rule;
    rule << head.toString() << " :- ";
    for (unsigned int i=0; i<predList.size(); i++)
    {
        rule << predList[i].toString();
        if(i != predList.size() -1)
            rule << ",";
    }

    return rule.str();
}

bool Rule::dependant()
{
    for (unsigned int i = 0; i < predList.size(); i++)
    {
        if(predList[i].ID == head.ID) {
            return true;        
        }
    }

    return false;
}