#include <vector>
#include <iostream>
#include "Token.h"

using namespace std;

class Parser {
    private:
    vector<Token> tokens;

    public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }

    TokenType tokenType() const
    {
        return tokens.at(0).getType();
    }

    void advanceToken()
    {
        tokens.erase(tokens.begin());
    }

    void throwError()
    {
        cout << "error" << endl;
    }

    void match(TokenType t)
    {
        cout << "match: " << t << endl;
        if (tokenType() == t)
            advanceToken();
        else
            throwError();
    }

    void idList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            match(ID);
            idList();
        }
        else
        {
            // lambda
        }
    }

    void scheme()
    {
        if (tokenType() == ID)
        {
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
        }
        else
        {
            throwError();
        }
    }
};
