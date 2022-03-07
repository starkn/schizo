#include <iostream>
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"

using namespace std;

int main()
{

    vector<string> names = {"ID", "Name", "Major"};

    Scheme scheme(names);

    Relation relation("student", scheme);

    vector<string> values[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'32'", "'Bob'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
        {"'16'", "'Jim'", "'EE'"},
    };

    for (auto &value : values)
    {
        Tuple tuple(value);
        cout << scheme.toString(tuple) << endl;
        relation.addTuple(tuple);
    }

    cout << "relation:" << endl;
    cout << relation.toString();

    Relation result = relation.select(2, "'CS'");

    cout << "select Major='CS' result:" << endl;
    cout << result.toString();
}