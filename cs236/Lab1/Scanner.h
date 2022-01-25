#pragma once

#include <string>
#include <string.h>
#include <cctype>
#include "Token.h"

class Scanner {
    private:
    string input;
    TokenType type;
    int size;
    

    public:
    Scanner(const string& input) : input(input) { }

    Token scanToken() {
        while (isspace(input.at(0)))
            input = input.substr(1);

        switch(input.at(0)){
            case ',':
                type = COMMA;
                size = 1;
                break;
            case '.':
                type = PERIOD;
                size = 1;
                break;
            case '?':
                type = Q_MARK;
                size = 1;
                break;
            case '(':
                type = LEFT_PAREN;
                size = 1;
                break;
            case ')':
                type = RIGHT_PAREN;
                size = 1;
                break;
            case ':':
                if(input.at(1) == '-'){
                    type = COLON_DASH;
                    size = 2;
                    break;
                }
                type = COLON;
                size = 1;
                break;
            case '\0':
                type = E_O_F;
                size = 1;
                break;
            case '*':
                type = MULTIPLY;
                size = 1;
                break;
            case '+':
                type = ADD;
                size = 1;
                break;
            case 'S':
                if(input.substr(0, 7).compare("Schemes") == 0){
                    type = SCHEMES;
                    size = 7;
                    break;
                }
            case 'F':
                if (input.substr(0, 5).compare("Facts") == 0)
                {
                    type = FACTS;
                    size = 5;
                    break;
                }
            case 'R':
                if (input.substr(0, 5).compare("Rules") == 0)
                {
                    type = RULES;
                    size = 5;
                    break;
                }
            case 'Q':
                if (input.substr(0, 7).compare("Queries") == 0)
                {
                    type = QUERIES;
                    size = 7;
                    break;
                }
            case '\'':
                size = 0;
                do {
                    size++;
                } while(input.at(size) != '\'');
                size++;
                type = STRING;
                break;
            case '#':
                type = COMMENT;
                size = 1;
                break;
            case 'A':
                type = ID;
                size = 1;
                break;
            default:
                type = UNDEFINED;
                size = 1;
                break;
        }

        string value = input.substr(0, size);
        input = input.substr(size);

        //Token t = (type, input, 1);

        return Token(type, value, 1);    
    }
};


