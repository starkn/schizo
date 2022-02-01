#include <iostream>
#include <fstream>
#include "Token.h"
#include "Scanner.h"

using namespace std;

int main(int argc, char *argv[]) {
    //Token t = Token(COMMA, ",", 2);
    //cout << t.toString() << endl;

    //ofstream out("out.txt");
    ifstream in(argv[1]);

    //cout << argv[1] << endl;

    std::stringstream buffer;
    buffer << in.rdbuf();

    Token t;

    Scanner s = Scanner(buffer.str());
    while (!t.isEOF())
    {
        t = s.scanToken();
        cout << t.toString() << endl;
    }

    cout << "Total Tokens = " << s.tot_token << endl;

    return 0;
}