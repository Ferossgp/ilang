#include <cstdlib>
#include <string>
#include <map>

#include "lexer.h"

using std::string;
using std::unordered_map;

Lexer::Lexer() {
    op_priority['='] = 2;
    op_priority['<'] = 10;
    op_priority['>'] = 10;
    op_priority['+'] = 20;
    op_priority['-'] = 20;
    op_priority['*'] = 240;

    keyword_map["var"] = Token::VAR;
    keyword_map["end"] = Token::END;
    keyword_map["if"] = Token::IF;
    keyword_map["then"] = Token::THEN;
    keyword_map["else"] = Token::ELSE;
    keyword_map["for"] = Token::FOR;
    keyword_map["in"] = Token::IN;
    keyword_map["reverse"] = Token::REVERSE;
    keyword_map["routine"] = Token::ROUTINE;
    keyword_map["is"] = Token::IS;
    keyword_map["type"] = Token::TYPE;
    keyword_map["record"] = Token::RECORD;
    keyword_map["array"] = Token::ARRAY;
    keyword_map["while"] = Token::WHILE;
    keyword_map["loop"] = Token::LOOP;
    keyyword_map["return"] = Token::RETURN;
}

void Lexer::next() {
    static int last_char = ' ';

    while (isspace(last_char)) {
        last_char = getchar();
    }

    if (isalpha(last_char)) {
        identifier = last_char;
        while (isalnum((last_char = getchar()))) {
            identifier += last_char;
        }

        if (keyword_map.count(identifier) == 0 ) {
            current_token = (int)Token::IDENTIFIER;
            return;
        } else {
            current_token = (int)keyword_map[identifier];
            return;
        }
    }

    if (isdigit(last_char)) {
        string number_string;
        bool is_double = false;
        do {
            if (last_char == '.') is_double = true;
            number_string += last_char;
            last_char = getchar();
        } while ( isdigit(last_char) || last_char == '.' );

        if (is_double) {
            real_value = strtod(number_string.c_str(), 0);
            current_token = (int)Token::REAL;
        }else{
            integer_value = (int) strtol(number_string.c_str(), 0);
            current_token = (int)Token::INTEGER;
        }

        return;
    }

    if ( last_char == '#' ) {
        do {
            last_char = getchar();
        } while ( last_char != EOF && last_char != '\n' && last_char != '\r' );

        if ( last_char != EOF ) {
            next();
            return;
        }
    }

    if ( last_char == EOF ) {
        current_token_ = (int)Token::_EOF;
        return;
    }

    current_token_ = last_char;
    last_char = getchar();
}


int Lexer::current_token() const { return current_token; }

const string Lexer::identifier() const { return identifier; }

double Lexer::number_value() const { return number; }

int Lexer::token_priority() {
    if (!isascii(current_token) ) {
        return -1;
    }

    int priority = op_priority[current_token];
    if ( priority <= 0 ) {
        return -1;
    }

    return priority;
}

void Lexer::add_op_priority(const char op, const int priority) {
    op_priority[op] = priority;
}

const unordered_map<char, int> Lexer::op_priority() const {
    return op_priority;
}