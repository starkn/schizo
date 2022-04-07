#pragma once

#include <vector>
#include <string>

using namespace std;

class Tuple : public vector<string>
{

private:
    mutable vector<string> values;

public:
    Tuple(vector<string> values) : values(values) {}

    unsigned size() const
    {
        return values.size();
    }

    const string &at(int index) const
    {
        return values.at(index);
    }

    void erase(int i) const
    {
        values.erase(values.begin() + i);
    }

    void move(int from, int to) const {
        string temp = values.at(to);
        values.at(to) = values.at(from);
        values.at(from) = temp;
    }
    
    bool operator<(const Tuple t) const
    {
        return values < t.values;
    }

};