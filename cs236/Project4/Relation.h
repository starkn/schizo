#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <map>
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
            return *this;
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

    void project(map<int, string> var) 
    {
        map<int, string>::iterator it;
        vector<int> pos;
        vector<string> names;
        for(it = var.begin(); it != var.end(); it++) {
            pos.push_back(it->first);
            names.push_back(it->second);
        }
        scheme.rename(names);
    }

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
	            const Tuple& leftTuple, const Tuple& rightTuple) 
    {
        bool join = false;
        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++)
        {
            const string &leftName = leftScheme.at(leftIndex);
            const string &leftValue = leftTuple.at(leftIndex);
            cout << "left name: " << leftName << " value: " << leftValue << endl;
            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++)
            {
                const string &rightName = rightScheme.at(rightIndex);
                const string &rightValue = rightTuple.at(rightIndex);
                cout << "right name: " << rightName << " value: " << rightValue << endl;
                if(rightValue == leftValue && rightName == leftName) {
                    join = true;
                }
            }
        }

        

        return join;
    }

    Relation join(const Relation &r)
    {
        const Scheme &leftScheme = scheme;
        for (const Tuple &leftTuple : tuples)
        {
            cout << "left tuple: " << leftScheme.toString(leftTuple) << endl;
            const Scheme &rightScheme = r.scheme;
            for (const Tuple &rightTuple : r.tuples)
            {
                cout << "right tuple: " << rightScheme.toString(rightTuple) << endl;
            }
        }
        
        return r;
    }
};