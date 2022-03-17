#pragma once

#include <string>
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
            // If there are no constants, skip straight to runVars()
            result = *this;
            return result;
        }
        else {
            for (auto &tuple : tuples) {
                // Check every tuple in the relation
                bool ret = true;
                map<int, string>::iterator it;
                for(it = con.begin(); it != con.end(); it++) {
                    // If the value at the index is not equal, don't return
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

    void eraseColumn(int i) {
        scheme.erase(i);
        for (auto &tuple : tuples)
        {
            tuple.erase(i);
        }
    }

    /**
     * @brief
     * Takes a map of variables and renames the columns of a relation
     * toErase Vector then removes repeated columns
     * Does not modify relation in, returns new relation
     * 
     * @param var - Map of Variables and indices
     * @param rel - Current Relation (maybe reduntant, but it works right now)
     * @param toErase - Vector with indices for repeating columns
     * @return Relation 
     */

    Relation project(map<int, string> var, Relation rel, vector<int> toErase) {
        map<int, string>::iterator it;
        vector<int> pos;
        vector<string> names;

        for(it = var.begin(); it != var.end(); it++) {
            // Collect the variable names and corresponding indices from the query
            pos.push_back(it->first);
            names.push_back(it->second);
        }

        Scheme s = Scheme(names);

        Relation r = Relation(rel.getName(), s);

        for (auto &tuple : tuples)
        {
            // Only add tuple columns that correspond with variable columns
            vector<string> current;
            for(int p : pos) {
                current.push_back(tuple.at(p));
            }
            r.addTuple(current);
        }


        // Remove repeating columns
        if (toErase.size() > 0)
        {
            for (int i = toErase.size() - 1; i >= 0; i--) {
                r.eraseColumn(toErase.at(i));
            }
        }
        return r;
    }

    /**
     * @brief 
     * Takes the variables listed in the query and runs through all of them
     * Returns a vector containing indices that are repeated variables i.e. they shouldn't be returned in the final output
     * 
     * @param var - Map of variables and indices
     * @return vector<int> - Indices of repeated variables
     */

    vector<int> runVars(map<int, string> &var) {
        map<int, string>:: iterator it;
        vector<int> toErase;

        for(it = var.begin(); it != var.end(); it++) {
            // If variable has already been checked, no need to check again
            if(it->second == "")
                continue;

            vector<int> pos;

            map<int, string>::iterator itt = it;
            itt++;

            for (map<int, string>::iterator it2 = itt; it2 != var.end(); it2++)
            {
                if(it->second == it2->second) {
                    // Add Columns that have the same variable name
                    if(pos.size() == 0)
                        pos.push_back(it->first);
                    pos.push_back(it2->first);
                    it2->second = ""; 
                }
            }

            // Go back to the beginning to check the columns
            set<Tuple>::iterator it = tuples.begin();

            while(it != tuples.end()) {
                bool move = true;

                // Iterate through columns of the same variable, and check them against the first value
                for(unsigned int i = 0; i < pos.size(); i++) {
                    if((*it).at(pos[0]) != (*it).at(pos[i])) {
                        it = tuples.erase(it);
                        move = false;
                        break;
                    }
                }

                if(move) {
                    // Only move iterators if we didn't erase the current value
                    it++;
                }
            }

            // If there are any matching tuples, add repeating columns to be deleted
            if (tuples.size() > 0) {
                for (unsigned int i = 1; i < pos.size(); i++) {
                    toErase.push_back(pos.at(i));
                }
            }
        }
        return toErase;
    }
};