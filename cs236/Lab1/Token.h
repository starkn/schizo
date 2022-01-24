#pragma once

#include <sstream>
#include <string>

using namespace std;

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
    ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOF, NULL
};

class Token {
    private:
    TokenType type;
    string value;
    int line;

    string typeName(TokenType type) const {
        switch (type) {
        case COMMA:
            return "COMMA";
        case STRING:
            return "STRING";
        }
        return "NULL";
    }

    public:
    Token(TokenType type, string value, int line)
     : type(type), value(value), line(line) { }

    Token() {
        type = NULL;
        value = NULL;
        line = 0;
    }

    bool isEOF() {
        if(type == EOF)
            return true;
        return false;
    }

    string toString() {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    }
};