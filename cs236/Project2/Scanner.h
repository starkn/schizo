#pragma once

#include <string>
#include <iostream>
#include <string.h>
#include <cctype>
//#include <ctype.h>
#include "Token.h"

using namespace std;

class Scanner {
    private:
    string input;
    TokenType type;
    int size;
    int line = 1;
    string temp;
    bool checkAlpha = false;

    

    public:
    Scanner(const string& input) : input(input) { }

    int tot_token = 0;

    Token scanToken() {

        while (input.size() > 0 && isspace(input.at(0))) {
            if (input.at(0) == '\n')
                line++;
            input = input.substr(1);
        }

        if (input.size() == 0)
        {
            type = E_O_F;
            size = 0;
            tot_token++;
            return Token(type, "", line);
        }

        temp = input;

        checkAlpha = false;

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
            case '*':
                type = MULTIPLY;
                size = 1;
                break;
            case '+':
                type = ADD;
                size = 1;
                break;
            case 'S':
                if (temp.substr(0, 7).compare("Schemes") == 0 && !isalnum(input.at(7)))
                {
                    type = SCHEMES;
                    size = 7;
                    break;
                }
                checkAlpha = true;
                break;
            case 'F':
                if (temp.substr(0, 5).compare("Facts") == 0 && !isalnum(input.at(5)))
                {
                    type = FACTS;
                    size = 5;
                    break;
                }
                checkAlpha = true;
                break;
            case 'R':
                if (temp.substr(0, 5).compare("Rules") == 0 && !isalnum(input.at(5)))
                {
                    type = RULES;
                    size = 5;
                    break;
                }
                checkAlpha = true;
                break;
            case 'Q':
                if (temp.substr(0, 7).compare("Queries") == 0 && !isalnum(input.at(7)))
                {
                    type = QUERIES;
                    size = 7;
                    break;
                }
                checkAlpha = true;
                break;
            case '\'':
                size = 0;
                type = STRING;
                do {
                    size++;
                    if (input.substr(size).size() < 1)
                    {
                        size--;
                        type = UNDEFINED;
                        break;
                    }
                    if (input.at(size) == '\'' && input.substr(size).size() > 1 ) 
                        if(input.at(size+1) == '\'') {
                            size += 2;
                        }
                } while(input.at(size) != '\'');
                size++;
                break;
            case '#':
                if(input.at(1) == '|') {
                    size = 1;
                    while (input.substr(size).size() > 1) {
                        size++;
                        if (input.substr(size).size() < 2)
                        {
                            size++;
                            type = UNDEFINED;
                            break;
                        }
                        if(input.at(size) == '|' && input.at(size+1) == '#') {
                            size+=2;
                            type = COMMENT;
                            break;
                        }

                    }
                    
                    break;
                }
                size = 1;
                while (input.substr(size).size() > 0 && input.at(size) != '\n')
                    size++;
                type = COMMENT;
                break;
            default:
                type = UNDEFINED;
                size = 1;
                checkAlpha = true;
                break;
        }

        if (checkAlpha && isalpha(input.at(0)))
        {
            size = 1;
            while (input.substr(size).size() > 0 && isalnum(input.at(size)))
                size++;
            type = ID;
        }

        string value = input.substr(0, size);
        input = input.substr(size);

        tot_token++;

        //Token t = (type, input, 1);

        int templine = line;

        for(long unsigned i=0; i < value.size(); i++) {
            if(value[i] == '\n') {
                line++;
                //value.replace(i, 1, " ");
            }
        }

        return Token(type, value, templine);    
    }
};


