#include <cstdlib>
#include <string>
#include <unordered_map>
#include <iostream>

#include "Lexer.h"

using std::string;
using std::unordered_map;

Lexer::Lexer(std::istream* inputStream) : inputStream(inputStream) {
    op_priority_['='] = 2;
    op_priority_['<'] = 10;
    op_priority_['>'] = 10;
    op_priority_['+'] = 20;
    op_priority_['-'] = 20;
    op_priority_['*'] = 240;
    op_priority_['/'] = 240;
    op_priority_['%'] = 240;

    keyword_map_["var"] = Token::VAR;
    keyword_map_["end"] = Token::END;
    keyword_map_["if"] = Token::IF;
    keyword_map_["then"] = Token::THEN;
    keyword_map_["else"] = Token::ELSE;
    keyword_map_["for"] = Token::FOR;
    keyword_map_["in"] = Token::IN;
    keyword_map_["reverse"] = Token::REVERSE;
    keyword_map_["routine"] = Token::ROUTINE;
    keyword_map_["is"] = Token::IS;
    keyword_map_["type"] = Token::TYPE;
    keyword_map_["record"] = Token::RECORD;
    keyword_map_["array"] = Token::ARRAY;
    keyword_map_["while"] = Token::WHILE;
    keyword_map_["loop"] = Token::LOOP;
    keyword_map_["return"] = Token::RETURN;
    keyword_map_["boolean"] = Token::BOOLEAN_TYPE;
    keyword_map_["integer"] = Token::INTEGER_TYPE;
    keyword_map_["real"] = Token::REAL_TYPE;
    keyword_map_["not"] = Token::NOT;
    keyword_map_["true"] = Token::TRUE_;
    keyword_map_["false"] = Token::FALSE_;    
}

void Lexer::next() {
    static int last_char = ' ';

    while (isspace(last_char)) {
        last_char = inputStream->get();
    }

    if (isalpha(last_char)) {
        identifier_ = last_char;
        while (isalnum((last_char = inputStream->get())) || last_char == '_') {
            identifier_ += last_char;
        }

        if (keyword_map_.count(identifier_) == 0 ) {
            current_token_ = (int)Token::IDENTIFIER;
            return;
        } else {
            current_token_ = (int)keyword_map_[identifier_];
            return;
        }
    }

    if (isdigit(last_char)) {
        string number_string;
        bool is_double = false;
        do {
            if (last_char == '.' && inputStream->peek() == '.') {
                inputStream->putback(last_char);
                break;
            }            
            if (last_char == '.') is_double = true;
            number_string += last_char;
            last_char = inputStream->get();
        } while ( isdigit(last_char) || last_char == '.' );

        if (is_double) {
            real_value_ = strtod(number_string.c_str(), 0);
            current_token_ = (int)Token::REAL;
        }else{
            integer_value_ = (int) strtod(number_string.c_str(), 0);
            current_token_ = (int)Token::INTEGER;
        }

        return;
    }
    if ( last_char == '.' && inputStream->peek() == '.'){
        current_token_ = (int)Token::RANGE;
        return;
    }
    if ( last_char == '#' ) {
        do {
            last_char = inputStream->get();
        } while ( last_char != EOF && last_char != '\n' && last_char != '\r' );

        if ( last_char != EOF ) {
            next();
            return;
        }
    }

    if ( last_char == EOF ) {
        current_token_ = (int)Token::EOF_;
        return;
    }

    current_token_ = last_char;
    last_char = inputStream->get();
}


int Lexer::current_token() const {
    return current_token_;
}

string Lexer::identifier() const { return identifier_; }

int Lexer::integer_value() const { return integer_value_; }

double Lexer::real_value() const { return real_value_; }

int Lexer::token_priority() {
    if (!isascii(current_token_) ) {
        return -1;
    }

    int priority = op_priority_[current_token_];
    if ( priority <= 0 ) {
        return -1;
    }

    return priority;
}

void Lexer::add_op_priority(const char op, const int priority) {
    op_priority_[op] = priority;
}

const unordered_map<char, int> Lexer::op_priority() const {
    return op_priority_;
}
