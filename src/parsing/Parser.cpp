#include "AST/ast.h"
#include "lexer.h"
#include "parser.h"
#include "errors.h"

#include <cstdio>

using std::move;
using std::swap;
using std::string;
using std::vector;
using std::make_pair;

Parser::Parser() : lexer(new Lexer()) {}

Parser::Parser(const Parser &other)
        : lexer(unique_ptr<Lexer>(other.lexer.get())) {}

Parser::Parser(Parser &&other) {
    lexer = move(other.lexer);
    other.lexer = nullptr;
}

Parser &Parser::operator = (Parser other) {
    swap(lexer, other.lexer);
    return *this;
}

Parser::~Parser() {
    lexer.reset();
}

ASTNode * Parser::parse_real() {
    ASTNode *result = new Real(lexer->number_value());
    lexer->next();
    return result;
}

ASTNode * Parser::parse_integer() {
    ASTNode *result = new Integer(lexer->number_value());
    lexer->next();
    return result;
}

ASTNode * Parser::parse_paren() {
    lexer->next();

    ASTNode *value = parse_expression();
    if ( !value ) {
        return 0;
    }
    if ( lexer->current_token() != ')' ) {
        return Error("expected ')'");
    }

    lexer->next();
    return value;
}

ASTNode * Parser::parse_identifier() {
    string identifier_name = lexer->identifier();

    lexer->next();

    if ( lexer->current_token() != '(' ) {
        return new VariableNode(identifier_name);
    }

    lexer->next();

    vector<*ASTNode> args;
    if ( lexer->current_token() != ')' ) {
        while (1) {
            ASTNode *arg = parse_expression();
            if ( !arg ) {
                return 0;
            }

            args.push_back(arg);

            if ( lexer->current_token() == ')' ) {
                break;
            }

            if ( lexer->current_token() != ',' ) {
                return Error("expected ')' or ',' in argument list");
            }

            lexer->next();
        }
    }

    lexer->next();

    return new RoutinCall(identifier_name, args);
}

ASTNode * Parser::parse_var() {
    lexer->next();

    pair<string, *ASTNode> var_name;

    if ( lexer->current_token() != (int)Token::IDENTIFIER ) {
        return Error("Expected identifier after var");
    }
    //TODO: parse ":"
    //TODO: parse type
    if ( lexer->current_token() != (int)Token::IS ) {
        return Error("Expected 'is' keyword after 'var'");
    }
    lexer->next();

    ASTNode *body = parse_expression();
    if ( body == 0 ) { return 0; }

    return new Var(var_name, body);
}

ASTNode * Parser::parse_type() {
    lexer->next();

    string id_name;

    if ( lexer->current_token() != (int)Token::IDENTIFIER ) {
        return Error("Expected identifier after 'type'");
    }
    id_name = lexer->curren_token();
    lexer->next();

    if ( lexer->current_token() != (int)Token::IS ) {
        return Error("Expected 'is' keyword after 'type'");
    }
    lexer->next();

    //TODO:parse type
}

ASTNode * Parser::parse_record() {
    lexer->next();
    vector<*ASTNode> vars_decl;

    while (lexer->current_token() == (int)Token::VAR) {
        vars_decl.push_back(parse_var());
    }

    if (lexer->current_token() != (int)Token::END){
        return Error("Expected 'end' at the end of the 'record' declaration");
    }

    lexer->next();
    return new Record(vars_decl);
}

ASTNode * Parser::parse_primary() {
    switch( lexer->current_token() ) {
        case (int)Token::IDENTIFIER:
            return parse_identifier();
        case (int)Token::INTEGER:
            return parse_integer();
        case (int)Token::REAL:
            return parse_real();
        case '(':
            return parse_paren();
        case (int)Token::IF:
            return parse_if();
        case (int)Token::FOR:
            return parse_for();
        case (int)Token::WHILE:
            return parse_while();
        case (int)Token::VAR:
            return parse_var();
        case (int)Token::RECORD:
            return parse_record();
        case (int)Token::TYPE:
            return parse_type();
        default:
            fprintf(stderr, "Unknown token '%c' when expecting an expression", (char) lexer->current_token());
            return 0;
    }
}

ASTNode * Parser::parse_binary_op_rhs(int expression_priority, ASTNode *LHS) {
    while (1) {
        int token_priority = lexer->token_priority();
        if ( token_priority < expression_priority ) {
            return LHS;
        }

        int binary_op = lexer->current_token();
        lexer->next();

        ASTNode *RHS = parse_unary();
        if ( !RHS ) { return 0; }

        int next_priority = lexer->token_priority();
        if ( token_priority < next_priority ) {
            RHS = parse_binary_op_rhs(token_priority + 1, RHS);
        }

        LHS = new Binary(binary_op, LHS, RHS);
    }
}

ASTNode * Parser::parse_unary() {
    if ( !isascii(lexer->current_token())
         || lexer->current_token() == '('
         || lexer->current_token() == ')' ) {
        return parse_primary();
    }

    int unary_op = lexer->current_token();
    lexer->next();

    if ( ASTNode *operand = parse_unary() ) {
        return new UnaryNode(unary_op, operand);
    }

    return 0;
}

ASTNode * Parser::parse_expression() {
    ASTNode *LHS = parse_unary();
    if ( !LHS ) { return 0; }

    return parse_binary_op_rhs(0, LHS);
}

Prototype * Parser::parse_prototype() {
    string func_name;

    if ( lexer->current_token() == (int)Token::IDENTIFIER ) {
        func_name = lexer->identifier();
        lexer->next();
    }

    if ( lexer->current_token() != '(' ) {
        return ErrorP("Expected '(' in prototype");
    }

    vector<string> arg_names;

    lexer->next();

    while ( lexer->current_token() == (int)Token::IDENTIFIER ) {
        arg_names.push_back(lexer->identifier());
        lexer->next();
    }

    if ( lexer->current_token() != ')' ) {
        return ErrorP("Expected ')' in prototype");
    }

    lexer->next();

    return new Prototype(func_name, arg_names);
}


//TODO: Parse return statement
Routine * Parser::parse_definition() {
    lexer->next();

    Prototype *proto = parse_prototype();

    if ( proto == 0 ) { return 0; }

    if ( ASTNode *expression = parse_expression() ) {

        return new Routine(proto, expression);
    }

    return 0;
}

Prototype * Parser::parse_extern() {
    lexer->next();

    return parse_prototype();
}

Routine * Parser::parse_top_level_expression() {
    if ( ASTNode *expression = parse_expression() ) {
        Prototype *proto = new Prototype("", vector<string>());
        return new Routine(proto, expression);
    }

    return 0;
}

ASTNode * Parser::parse_if() {
    lexer->next();

    ASTNode *condition = parse_expression();
    if ( ! condition ) { return 0; }

    if ( lexer->current_token() != (int)Token::THEN ) {
        return Error("expected 'then'");
    }

    lexer->next();

    ASTNode *then = parse_expression();
    if ( ! then ) { return 0; }

    if ( lexer->current_token() == (int)Token::ELSE ) {
        lexer->next();
        ASTNode *_else = parse_expression();
        if ( ! _else ) { return 0; }
        return new If(condition, then);
    }

    lexer->next();

    ASTNode *else_body = parse_expression();
    if ( ! else_body ) { return 0; }

    return new If(condition, then, else_body);
}

ASTNode * Parser::parse_for() {
    lexer->next();

    if ( lexer->current_token() != (int)Token::IDENTIFIER ) {
        return Error("expected identifier after 'for'");
    }

    string id_name = lexer->identifier();
    lexer->next();

    if ( lexer->current_token() != (int)Token::IN ||
            lexer->current_token() != (int)Token::REVERSE) {
        return Error("expected 'in' or 'reverse' after 'for'");
    }
    bool reverse = (lexer->current_toke() == (int)Token::REVERSE);
    lexer->next();

    ASTNode *start = parse_expression();
    if ( start == 0 ) { return 0; }

    if ( lexer->current_token() != '.' ||
            (lexer->next() && lexer->current_token() != '.')) {
        return Error("Expected '..' after for start value");
    }

    lexer->next();

    ASTNode *end = parse_expression();
    if ( end == 0 ) { return 0; }

    if (lexer->current_token() != (int)Token::LOOP) {
        return Error("Expected 'loop' after Range in 'for'");
    }

    lexer->next();

    ASTNode *body = parse_expression();
    if ( body == 0 ) { return 0; }

    if (lexer->current_token() != (int)Token::END){
        return Error("Expected 'end' at the end of the 'loop' body expression");
    }

    lexer->next();

    if (reverse){
        return new For(id_name, end, start, body);
    } else {
        return new For(id_name, start, end, body);
    }
}

ASTNode * Parser::parse_while() {
    lexer->next();

    ASTNode *expression = parse_expression();
    if ( body == 0 ) { return 0; }

    if (lexer->current_token() != (int)Token::LOOP) {
        return Error("Expected 'loop' after expression in 'while'");
    }

    lexer->next();

    ASTNode *body = parse_expression();
    if ( body == 0 ) { return 0; }

    if (lexer->current_token() != (int)Token::END){
        return Error("Expected 'end' at the end of the 'loop' body expression");
    }
    lexer->next();

    return new While(expression, body);
}

ASTNode * Parser::parse_array() {
    lexer->next();

    if (lexer->current_token() != '['){
        return Error("Expected '[' at the beginning of array expression");
    }
    lexer->next();

    ASTnode *expression = parse_expression();
    if (expression == 0) { return 0; }

    if (lexer->current_token() != ']'){
        return Error("Expected ']' at the end of the array expression");
    }
    lexer->next();
    //TODO: parse type
    ASTNode *type;

    return new Array(expression, type);
}