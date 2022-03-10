#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "Parameter.h"

using namespace std;

class Predicate
{
private:
public:
    vector<Parameter> paramList;
    string ID;
    Predicate();
    ~Predicate();

    Predicate(string id);

    void addParameter(Parameter p);

    string toString();
};

Predicate::Predicate()
{
    ID = "Undefined";
}

Predicate::~Predicate()
{
}

Predicate::Predicate(string id)
{
    this->ID = id;
}

void Predicate::addParameter(Parameter p)
{
    paramList.push_back(p);
}

string Predicate::toString()
{
    stringstream pred;
    pred << ID << "(";
    for(unsigned int i=0; i<paramList.size(); i++)
    {
        pred << paramList[i].toString();
        if(i != paramList.size() - 1)
            pred << ",";
    }
    pred << ")";
    return pred.str();
}
