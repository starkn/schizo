#pragma once

#include <vector>
#include <iostream>
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

    string toString();
};

DatalogProgram::DatalogProgram(/* args */)
{
}

DatalogProgram::~DatalogProgram()
{
}
