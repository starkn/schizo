#include <iostream>
#include <fstream>
#include <vector>
#include "Parser.h"
#include "Token.h"
#include "Scanner.h"

using namespace std;

int main(int argc, char *argv[]) {
    /*ifstream in(argv[1]);

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
    */

    vector<Token> tokens = {
        Token(ID, "Ned", 2),
        Token(LEFT_PAREN, "(", 2),
        //Token(ID, "Ted", 2),
        Token(COMMA, ",", 2),
        Token(ID, "Zed", 2),
        Token(RIGHT_PAREN, ")", 2),
    };

    Parser p = Parser(tokens);
    p.scheme();

    return 0;
}