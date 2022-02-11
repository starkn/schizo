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

    string toString();
};

Rule::Rule(Predicate hPred)
{
    this->head = hPred;
}

Rule::~Rule()
{
}

void Rule::addPredicate(Predicate p)
{
    predList.push_back(p);
}

string Rule::toString()
{
    stringstream rule;
    rule << head.toString() << " :- ";
    for (Predicate pred : predList)
    {
        rule << ", " << pred.toString();
    }

    return rule.str();
}
