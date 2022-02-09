#pragma once

#include <string>

using namespace std;

class Parameter
{
private:
    string value;
public:
    Parameter(string val);
    ~Parameter();

    string toString();
};

Parameter::Parameter(string val)
{
    this->value = val;
}

Parameter::~Parameter()
{
}

string Parameter::toString()
{
    return this->value;
}
