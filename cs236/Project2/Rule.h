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
    Rule(/* args */);
    ~Rule();

    string toString();
};

Rule::Rule(/* args */)
{
}

Rule::~Rule()
{
}
