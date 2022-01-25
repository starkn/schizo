#include <iostream>
#include "Token.h"
#include "Scanner.h"

using namespace std;

int main() {
    //Token t = Token(COMMA, ",", 2);
    //cout << t.toString() << endl;

    Token t;

    Scanner s = Scanner(",,,.&.? Schemes Facts Queries Rules x'teststringgg please'");
    do {
        Token t = s.scanToken();
        cout << t.toString() << endl;
    } while(!t.isEOF());
}