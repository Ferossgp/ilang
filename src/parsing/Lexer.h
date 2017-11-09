#ifndef ILANG_LEXER_H
#define ILANG_LEXER_H

#include <string>
#include <map>

using std::string;
using std::map;

enum class Token {
    EOF_ = -1,
    VAR = -2,
    END = -3,
    IF = -4,
    THEN = -5,
    ELSE = -6,
    FOR = -7,
    WHILE = -8,
    LOOP = -9,
    IN = -10,
    REVERSE = -11,
    ROUTINE = -12,
    IS = -13,
    TYPE = -14,
    RECORD = -15
};

class Lexer {
    int current_token;
    string identifier;
    int integer_value;
    double real_value;
    map <char, int> op_priority;
    map <string, Token> keyword_map;

public:
    Lexer();
    Lexer(const Lexer &other);

    int current_token() const;
    string identifier() const;
    int  integer_value() const;
    double  real_value() const;

    void next();

    int token_pr();
    void add_op_pr(const char &op, const int priority);
    const map<char, int> op_priority() const;

};
#endif //ILANG_LEXER_H
