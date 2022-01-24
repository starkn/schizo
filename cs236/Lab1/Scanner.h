#pragma once

#include <string>
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
            case ',':
                type = COMMA;
                size = 1;
                break;
            case ',':
                type = COMMA;
                size = 1;
                break;
            case ',':
                type = COMMA;
                size = 1;
                break;
            case ',':
                type = COMMA;
                size = 1;
                break;
            case ',':
                type = COMMA;
                size = 1;
                break;
            case ',':
                type = COMMA;
                size = 1;
                break;
            
        }

        string value = input.substr(0, size);
        input = input.substr(size);

        //Token t = (type, input, 1);

        return Token(type, input, 1);    
    }
};


