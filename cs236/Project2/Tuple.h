#pragma once

#include <vector>
#include <string>

using namespace std;

class Tuple : public vector<string>
{

private:
    vector<string> values;

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

    bool operator<(const Tuple t) const
    {
        return values < t.values;
    }

    // TODO: add more delegation functions as needed
};