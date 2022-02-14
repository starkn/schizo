#include <vector>
#include <iostream>
#include <string>
#include <exception>

#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include "Token.h"

using namespace std;


class Parser
{
private:
    vector<Token> tokens;

    DatalogProgram data;

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

    string match(TokenType t, bool ret = false)
    {
        
        if(tokenType() == COMMENT)
        {
            advanceToken();
            return match(t, ret); 
        }
        else
        {
            string val;
            if (tokenType() == t)
            {
                if(ret)
                    val = tokens.at(0).getValue();

                advanceToken();
                return val;
            }
            else
            {
                //string msg = "Failure!\n ";
                //msg = msg + tokens.at(0).toString();
                throw exception();
            }
        }
    }

    Predicate scheme()
    {
        Predicate s = Predicate(match(ID, true));
        match(LEFT_PAREN);
        Parameter p = Parameter(match(ID, true));
        s.addParameter(p);
        idList(s);
        match(RIGHT_PAREN);
        return s;
    }

    Predicate fact()
    {
        Predicate f = Predicate(match(ID, true));
        match(LEFT_PAREN);
        string val = match(STRING, true);
        this->data.addDomain(val);
        Parameter p = Parameter(val);
        f.addParameter(p);
        stringList(f);
        match(RIGHT_PAREN);
        match(PERIOD);
        return f;
    }

    void schemes()
    {
        match(SCHEMES);
        match(COLON, true);
        this->data.addScheme(scheme());
        schemeList();
    }

    void schemeList()
    {
        if (tokenType() == ID)
        {
            this->data.addScheme(scheme());
            schemeList();
        }
        else
        {
            // lambda
        }
    }

    void idList(Predicate &pd)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            Parameter p = Parameter(match(ID, true));
            pd.addParameter(p);
            idList(pd);
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
        //this->data.addFact(fact());
        factList();
    }

    void factList()
    {
        if (tokenType() == ID)
        {
            this->data.addFact(fact());
            factList();
        }
        else
        {
            // lambda
        }
    }

    void stringList(Predicate &pd)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            string val = match(STRING, true);
            Parameter p = Parameter(val);
            this->data.addDomain(val);
            pd.addParameter(p);
            stringList(pd);
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
        //this->data.addRule(rule());
        ruleList();
    }

    void ruleList()
    {
        if (tokenType() == ID)
        {
            this->data.addRule(rule());
            ruleList();
        }
        else
        {
            // lambda
        }
    }

    Rule rule()
    {
        Predicate head = Predicate(headPredicate());
        Rule r = Rule(head);
        match(COLON_DASH);
        Predicate p = Predicate(pred());
        r.addPredicate(p);
        predicateList(r);
        match(PERIOD);
        return r;
    }

    Predicate headPredicate()
    {
        Predicate p = Predicate(match(ID, true));
        match(LEFT_PAREN);
        Parameter pm = Parameter(match(ID, true));
        p.addParameter(pm);
        idList(p);
        match(RIGHT_PAREN);
        return p;
    }

    Predicate pred()
    {
        Predicate pd = Predicate(match(ID, true));
        match(LEFT_PAREN);
        Parameter p = Parameter(parameter());
        pd.addParameter(p);
        parameterList(pd);
        match(RIGHT_PAREN);
        return pd;
    }

    void predicateList(Rule &r)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            r.addPredicate(pred());
            predicateList(r);
        }
        else
        {
            // lambda
        }
    }

    Parameter parameter()
    {
        if (tokenType() == STRING)
        {
            Parameter p = Parameter(match(STRING, true));
            return p;
        }
        else
        {
            Parameter p = Parameter(match(ID, true));
            return p;
        }
    }

    void parameterList(Predicate &pd)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            pd.addParameter(parameter());
            parameterList(pd);
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
        this->data.addQuery(query());
        queryList();
    }

    Predicate query()
    {
        Predicate p = Predicate(pred());
        match(Q_MARK);
        return p;
    }

    void queryList()
    {
        if (tokenType() == ID)
        {
            this->data.addQuery(query());
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
            cout << data.toString();
        }
        catch (...)
        {
            string msg = "Failure!\n  ";
            msg = msg + tokens.at(0).toString();
            cout << msg << endl;
        }

    }
};
