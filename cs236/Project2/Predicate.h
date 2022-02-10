#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "Parameter.h"

using namespace std;

class Predicate
{
private:
    vector<Parameter> paramList;
    string ID;
public:
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
    pred << ID;
    for(Parameter param : paramList)
    {
        pred << ", " << param.toString();
    }
    return pred.str();
}
