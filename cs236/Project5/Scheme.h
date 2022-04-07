#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include "Tuple.h"
#include "Predicate.h"

using namespace std;

class Scheme : public vector<string>
{

private:
    mutable vector<string> names;

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

    void erase(int i) {
        names.erase(names.begin() + i);
    }

    void move(int from, int to) {
        string temp = names.at(to);
        names.at(to) = names.at(from);
        names.at(from) = temp;
    }
    
    vector<string>::iterator end() {
        return names.end();
    }

    vector<string>::iterator begin() {
        return names.begin();
    }

    Scheme join(const Scheme &scheme) const {
        vector<string> n = names;
        for(unsigned int i = 0; i < scheme.size(); i++) {
            if (find(n.begin(), n.end(), scheme.at(i)) == n.end())
                n.push_back(scheme.at(i));
        }
        Scheme s = Scheme(n);
        return s;
    }

};