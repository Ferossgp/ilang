//
// Created by feross on 11/3/17.
//

#ifndef ILANG_PARSER_H
#define ILANG_PARSER_H

#include "../AST/node.h"
#include "../AST/prototype.h"
#include "../AST/routine.h"

#include "Lexer.h"

#include <memory>

class Parser {
    Lexer* const lexer;
    vector<pair<string, ASTNode>> NameTable;

    ASTNode *parse_expression();
    ASTNode *parse_primary();
    ASTNode *parse_if();
    ASTNode *parse_for();
    ASTNode *parse_while();
    ASTNode *parse_unary();
    ASTNode *parse_real();
    ASTNode *parse_integer();
    ASTNode *parse_boolean();
    ASTNode *parse_paren();
    ASTNode *parse_identifier();
    ASTNode *parse_var();
    ASTNode *parse_array();
    ASTNode *parse_record();
    ASTNode *parse_arg();
    ASTNode *parse_type();
    ASTNode *parse_types();
    ASTNode *parse_return();
    ASTNode *parse_assignment(string identifier_name);
    ASTNode *parse_binary_op_rhs(int priority, ASTNode *lhs);
    Prototype *parse_prototype();

    void addDecl(pair<string, ASTNode*> name_pair);
    ASTNode *findDecl(string name);
    void openScope();
    void closeScope();
public:
    Parser(Lexer* const lexer) : lexer(lexer) { }
    ~Parser();

    Prototype *parse_extern();
    Routine *parse_routine();
    Routine *parse_top_level_expression();
    void parse();
    void handleTopLevelExpression();
    void handleExtern();
    void handleRoutine();
    void handleVariable();
};

#endif //ILANG_PARSER_H
