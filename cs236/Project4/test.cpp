#include <iostream>
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
    };

    for (auto &value : studentValues)
        studentRelation.addTuple(Tuple(value));

    //studentRelation.join(studentRelation);

    Relation courseRelation("courses", Scheme({"ID", "Course"}));

    vector<string> courseValues[] = {
        {"'42'", "'CS 100'"},
        {"'32'", "'CS 232'"},
    };

    for (auto &value : courseValues)
        courseRelation.addTuple(Tuple(value));

    studentRelation.join(courseRelation);
}