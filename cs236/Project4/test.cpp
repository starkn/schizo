#include <iostream>
#include <vector>
#include <algorithm>
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"

using namespace std;

int main()
{
    Relation studentRelation("students", Scheme({"ID", "Name", "Major"}));

    vector<string> studentValues[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
        {"'32'", "'Geoffrey'", "'ME'"},
    };

    for (auto &value : studentValues)
        studentRelation.addTuple(Tuple(value));

    //studentRelation.join(studentRelation);

    Relation courseRelation("courses", Scheme({"ID", "Course", "Major"}));

    vector<string> courseValues[] = {
        {"'42'", "'CS 100'", "'EE'"},
        {"'32'", "'CS 232'", "'ME'"},
        {"'64'", "'CS 142'", "'CS'"}
    };

    vector<int> vec {1,3,5};

    for(int i = 0; i < 5; i++) {
        if(find(vec.begin(), vec.end(), i) == vec.end())
            vec.push_back(i);
    }

    for(int i = 0; i<vec.size(); i++) {
        cout << vec[i] << endl;
    }

    for (auto &value : courseValues)
        courseRelation.addTuple(Tuple(value));

    studentRelation.join(courseRelation);
}