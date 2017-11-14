#ifndef ILANG_LEXER_H
#define ILANG_LEXER_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

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
    RECORD = -15,
    RETURN = -16,
    ARRAY = -17,
    IDENTIFIER = -18,
    REAL = -19,
    INTEGER = -20,
};

// TODO: Implement enum also for operation chars

class Lexer {
    int current_token_;
    string identifier_;
    int integer_value_;
    double real_value_;
    unordered_map <char, int> op_priority_;
    unordered_map <string, Token> keyword_map_;

public:
    Lexer();
    Lexer(const Lexer &other);

    int current_token() const;
    string identifier() const;
    int  integer_value() const;
    double  real_value() const;

    void next();

    int token_priority();
    void add_op_priority(const char op, const int priority);
    const unordered_map<char, int> op_priority() const;

};
#endif //ILANG_LEXER_H
