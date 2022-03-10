#include <iostream>
#include <fstream>
#include <vector>
#include "Parser.h"
#include "Token.h"
#include "Scanner.h"

using namespace std;

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);

    std::stringstream buffer;
    buffer << in.rdbuf();

    Token t;

    vector<Token> tokens;

    Scanner s = Scanner(buffer.str());
    while (!t.isEOF())
    {
        t = s.scanToken();
        tokens.push_back(t);
    }

    Parser p = Parser(tokens);
    p.datalogProgram();

    return 0;
}