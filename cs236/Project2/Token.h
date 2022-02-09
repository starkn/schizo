#pragma once

#include <sstream>
#include <string>

using namespace std;

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, E_O_F, MULTIPLY,
    ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED
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
            case PERIOD:
                return "PERIOD";
            case Q_MARK: 
                return "Q_MARK";
            case LEFT_PAREN: 
                return "LEFT_PAREN";
            case RIGHT_PAREN: 
                return "RIGHT_PAREN";
            case COLON: 
                return "COLON";
            case COLON_DASH: 
                return "COLON_DASH";
            case E_O_F:
                return "EOF";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES: 
                return "QUERIES";
            case ID:
                return "ID";
            case STRING:
                return "STRING";
            case COMMENT: 
                return "COMMENT";
            case UNDEFINED:
                return "UNDEFINED";
        }
        return "NULL";
    }

    public:
    Token(TokenType type, string value, int line)
     : type(type), value(value), line(line) { }

    Token() {
        type = UNDEFINED;
        value = "";
        line = 0;
    }

    bool isEOF() {
        if(type == E_O_F) {
            return true;
        }
        return false;
    }

    TokenType getType() const {
        return this->type;
    }

    string toString() {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    }

    string getValue() const {
        return this->value;
    }
};