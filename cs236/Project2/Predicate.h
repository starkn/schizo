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
    Predicate(string id);
    ~Predicate();

    string toString();
};

Predicate::Predicate(string id)
{
    this->ID = id;
}

Predicate::~Predicate()
{
}

string Predicate::toString()
{
    stringstream pred;
    pred << ID;
    for(Parameter param : paramList)
    {
        pred << ", " << param;
    }
    return pred.str();
}
