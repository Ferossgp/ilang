#ifndef ILANG_PARSER_H
#define ILANG_PARSER_H

#include "../AST/node.h"
#include "../AST/prototype.h"
#include "../AST/routine.h"

#include "lexer.h"


class Parser {
    Parser(const Parser &other);
    Parser(Parser &&other);

    Parser &operator =(Parser other);

    ASTNode *parse_expression();
    ASTNode *parse_if();
    ASTNode *parse_for();
    ASTNode *parse_while();
    ASTNode *parse_unary();
    ASTNode *parse_real();
    ASTNode *parse_integer();
    ASTNode *parse_paren();
    ASTNode *parse_identifier();
    ASTNode *parse_var();
    ASTNode *parse_array();
    ASTNode *parse_record();
    ASTNode *parse_binary_op_rhs(int priority, ASTNode *lhs);
    Prototype *parse_prototype();

public:
    Parser();
    ~Parser();

    unique_ptr<Lexer> lexer;

    Prototype *parse_extern();
    Routine *parse_definition();
    Routine *parse_top_level_expression();
};

#endif //ILANG_PARSER_H
