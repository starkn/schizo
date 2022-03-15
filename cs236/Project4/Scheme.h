#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "Tuple.h"
#include "Predicate.h"

using namespace std;

class Scheme : public vector<string>
{

private:
    vector<string> names;

public:
    Scheme(vector<string> names) : names(names) {}
    Scheme(Predicate scheme);

    unsigned size() const
    {
        return names.size();
    }

    const string &at(int index) const
    {
        return names.at(index);
    }

    string toString(const Tuple &tuple) const
    {
        stringstream out;
        for (unsigned i = 0; i < size(); i++)
        {
            if (i > 0)
                out << ", ";
            const string &name = at(i);
            const string &value = tuple.at(i);
            out << name << "=" << value;
        }
        return out.str();
    }

    void rename(vector<string> n) {
        names = n;
    }

    // TODO: add more delegation functions as needed
};

Scheme::Scheme(Predicate scheme)
{
    
}