#include <vector>
#include <iostream>
#include "Token.h"

using namespace std;

class Parser
{
private:
    vector<Token> tokens;

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
        if (tokenType() == t)
        {
            advanceToken();
        }
        else
        {
            string msg = "Failure!\n ";
            msg = msg + tokens.at(0).toString();
            throw msg;
        }
    }

    void schemes()
    {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
    }

    void schemeList()
    {
        if (tokenType() == ID)
        {
            scheme();
            schemeList();
        }
        else
        {
            // lambda
        }
    }

    void scheme()
    {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
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

    void facts()
    {
        match(FACTS);
        match(COLON);
        factList();
    }

    void factList()
    {
        if (tokenType() == ID)
        {
            fact();
            factList();
        }
        else
        {
            // lambda
        }
    }

    void fact()
    {
        match(ID);
        match(LEFT_PAREN);
        match(STRING);
        stringList();
        match(RIGHT_PAREN);
        match(PERIOD);
    }

    void stringList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            match(STRING);
            stringList();
        }
        else
        {
            // lambda
        }
    }

    void rules()
    {
        match(RULES);
        match(COLON);
        ruleList();
    }

    void ruleList()
    {
        if (tokenType() == ID)
        {
            rule();
            ruleList();
        }
        else
        {
            // lambda
        }
    }

    void rule()
    {
        headPredicate();
        match(COLON_DASH);
        predicate();
        predicateList();
        match(PERIOD);
    }

    void headPredicate()
    {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
    }

    void predicate()
    {
        match(ID);
        match(LEFT_PAREN);
        parameter();
        parameterList();
        match(RIGHT_PAREN);
    }

    void predicateList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            predicate();
            predicateList();
        }
        else
        {
            // lambda
        }
    }

    void parameter()
    {
        if (tokenType() == STRING)
        {
            match(STRING);
        }
        else
        {
            match(ID);
        }
    }

    void parameterList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            parameter();
            parameterList();
        }
        else
        {
            // lambda
        }
    }

    void queries()
    {
        match(QUERIES);
        match(COLON);
        query();
        queryList();
    }

    void query()
    {
        predicate();
        match(Q_MARK);
    }

    void queryList()
    {
        if (tokenType() == ID)
        {
            query();
            queryList();
        }
        else
        {
            // lambda
        }
    }

    void iseof()
    {
        match(E_O_F);
    }

public:
    Parser(const vector<Token> &tokens) : tokens(tokens) {}

    void datalogProgram()
    {
        try
        {
            this->schemes();
            this->facts();
            this->rules();
            this->queries();
            this->iseof();
        }
        catch (string msg)
        {
            cerr << msg << endl;
        }
    }
};
