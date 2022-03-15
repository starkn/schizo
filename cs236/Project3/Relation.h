#pragma once

#include <string>
#include <sstream>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation
{

private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation(const string &name, const Scheme &scheme)
        : name(name), scheme(scheme) {}

    void addTuple(const Tuple &tuple)
    {
        tuples.insert(tuple);
    }

    string toString() const
    {
        stringstream out;
        for (auto &tuple : tuples)
            out << "  " << scheme.toString(tuple) << endl;
        return out.str();
    }

    Relation select(map<int, string> con, map<int, string> var) const
    {
        Relation result(name, scheme);
        if(con.size() < 1) {
            result = *this;
            result = result.project(var, result);
            return result;
        }
        else {
            for (auto &tuple : tuples) {
                bool ret = true;
                map<int, string>::iterator it;
                for(it = con.begin(); it != con.end(); it++) {
                    if(tuple.at(it->first) != it->second)
                        ret = false;                   
                }
                if(ret)
                    result.addTuple(tuple);
            }
        }
        result = result.project(var, result);
        return result;
    }

    string getName() const
    {
        return name;
    }

    void setName(string n)
    {
        this->name = n;
    }

    int size() const 
    {
        return tuples.size();
    }

    Relation project(map<int, string> var, Relation rel) {
        map<int, string>::iterator it;
        vector<int> pos;
        vector<string> names;
        for(it = var.begin(); it != var.end(); it++) {
            pos.push_back(it->first);
            names.push_back(it->second);
        }

        Scheme s = Scheme(names);

        Relation r = Relation(rel.getName(), s);

        for (auto &tuple : tuples)
        {
            vector<string> current;
            for(int p : pos) {
                current.push_back(tuple.at(p));
            }
            r.addTuple(current);
        }
        return r;
    }
};