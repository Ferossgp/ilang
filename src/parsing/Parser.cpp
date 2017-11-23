#include "../AST/ast.h"
#include "Lexer.h"
#include "Parser.h"
#include "Errors.h"
#include "Errors.cpp"
#include <cstdio>
#include <memory>

using std::move;
using std::swap;
using std::string;
using std::vector;
using std::make_pair;
using std::unique_ptr;

//TODO: Create types (Builtin, Array, Record)
//TODO: Print ast

Parser::~Parser() {}

ASTNode * Parser::parse_real() {
    ASTNode *result = new Real(lexer->real_value());
    lexer->next();
    return result;
}

ASTNode * Parser::parse_integer() {
    ASTNode *result = new Integer(lexer->integer_value());
    lexer->next();
    return result;
}

ASTNode * Parser::parse_boolean() {
    ASTNode *result = new Boolean(lexer->boolean_value());
    lexer->next();
    return result;
}

ASTNode * Parser::parse_return() {
    lexer->next();
    ASTNode *ret = parse_expression();

    return Return(ret);
}

ASTNode * Parser::parse_paren() {
    lexer->next();

    ASTNode *value = parse_expression();
    if ( !value ) {
        return nullptr;
    }
    if ( lexer->current_token() != ')' ) {
        return Error("expected ')'");
    }

    lexer->next();
    return value;
}

ASTNode * Parser::parse_types() {
    if (lexer->current_token() == (int)Token::INTEGER_TYPE) {
        lexer->next();
        return new Integer();
    }

    if (lexer->current_token() == (int)Token::REAL_TYPE) {
        lexer->next();
        return new Real();
    }

    if (lexer->current_token() == (int)Token::BOOLEAN_TYPE) {
        lexer->next();
        return new Boolean();
    }
    // Check if current_token is in table

    if(lexer->current_token() == (int)Token::IDENTIFIER) {
        ASTNode *type = findDecl(lexer->identifier());
        lexer->next();
        return type;
    }

    return nullptr;
}
ASTNode * Parser::parse_assignment(string identifier_name) {
    ASTNode *assignee = findDecl(identifier_name);
    if(!assignee){
        return nullptr;
    }
    // Array assign
    if ( lexer->current_token() == '[') {
        lexer->next();
        ASTNode *pos = parse_expression();

        if ( lexer->current_token() != ']' ) {
            return Error("expected ']' in array assignment");
        }
        lexer->next();
        if ( lexer->current_token() == ':' ){
            lexer->next();
            if (lexer->current_token() == '=') {
                ASTNode *value = parse_expression();
                return ArrayAssign(assignee, pos, value);
            }
            return Error("Unknown ':' at this possition");
        }
        // Skip this node, non-sens empty assign;
        return nullptr;
    }
    // Record Assign
    if ( lexer->current_token() == '.'){
        lexer->next();
        if (lexer->current_token() != (int) Token::IDENTIFIER ) {
            return Error("expected identifier after '.'");
        }
        string ref_name = lexer->identifier();
        lexer->next();
        if ( lexer->current_token() == ':' ){
            lexer->next();
            if (lexer->current_token() == '=') {
                ASTNode *value = parse_expression();
                return RecordAssign(assignee, ref_name, value);
            }
            return Error("Unknown ':' at this possition");
        }
        // Skip this node, non-sens empty assign;
        return nullptr;
    }
    // Variable Assign
    if ( lexer->current_token() != '('){
        lexer->next();
        if ( lexer->current_token() == ':' ){
            lexer->next();
            if (lexer->current_token() == '=') {
                ASTNode *value = parse_expression();
                return Variable(assignee, value);
            }
            return Error("Unknown ':' at this possition");
        }
        // Skip this node, non-sens empty assign;
        return nullptr;
    }
    return nullptr;
}

/// Returns Variable or RoutineCall
ASTNode * Parser::parse_identifier() {
    string identifier_name = lexer->identifier();

    if ( lexer->current_token() != '(' ) {
        return parse_assignment(identifier_name);
    }

    lexer->next();

    vector<ASTNode*> args;

    while ( lexer->current_token() != ')' ) {
        ASTNode *arg = parse_expression();
        if ( !arg ) {
            return nullptr;
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

    lexer->next();

    return new RoutineCall(identifier_name, args);
}

ASTNode * Parser::parse_var() {
    lexer->next();

    if ( lexer->current_token() != (int)Token::IDENTIFIER ) {
        return Error("Expected identifier after var");
    }
    string name = lexer->identifier();
    lexer->next();
    ASTNode *type;

    if ( lexer->current_token() == ':') {
        lexer->next();
        type = parse_types();
    }

    if ( lexer->current_token() == (int)Token::IS) {
        lexer->next();
        ASTNode *expression = parse_expression();

        if (type){
            ASTNode *var = new Var(make_pair(name, type), expression);
            addDecl(make_pair(name, var));
            return var;
        }
        ASTNode *var = new Var(make_pair(name, nullptr), expression);
        addDecl(make_pair(name, var));
        return var;
    }

    if (!type){
        return Error("Expected 'is' or ':' keyword after 'var'");
    }

    ASTNode *var = new Var(make_pair(name, type), nullptr);
    addDecl(make_pair(name, var));
    return var;
}

ASTNode * Parser::parse_type() {
    lexer->next();

    string id_name;

    if ( lexer->current_token() != (int)Token::IDENTIFIER ) {
        return Error("Expected identifier after 'type'");
    }
    id_name = lexer->current_token();
    lexer->next();

    if ( lexer->current_token() != (int)Token::IS ) {
        return Error("Expected 'is' keyword after 'type'");
    }
    lexer->next();

    ASTNode *type = parse_types();

    if (!type) {
        if(lexer->current_token() == (int)Token::ARRAY){
            type = parse_array();
        } else if (lexer->current_token() == (int)Token::RECORD) {
            type = parse_record();
        }
    }

    if (!type) {
        return Error("Expected valid type after 'is'");
    }

    ASTNode *type_decl  = new TypeDecl(id_name, type);
    addDecl(make_pair(id_name, type_decl));
    return type_decl;
}

ASTNode * Parser::parse_record() {
    lexer->next();
    vector<ASTNode*> vars_decl;
    openScope();
    while (lexer->current_token() == (int)Token::VAR) {
        vars_decl.push_back(parse_var());
    }

    if (lexer->current_token() != (int)Token::END){
        return Error("Expected 'end' at the end of the 'record' declaration");
    }

    lexer->next();
    closeScope();
    return new RecordDecl(vars_decl);
}

ASTNode * Parser::parse_array() {
    lexer->next();

    if (lexer->current_token() != '['){
        return Error("Expected '[' at the beginning of array expression");
    }
    lexer->next();

    ASTNode *expression = parse_expression();
    if (!expression) { return nullptr; }

    if (lexer->current_token() != ']'){
        return Error("Expected ']' at the end of the array expression");
    }
    lexer->next();

    ASTNode *type = parse_types();

    if (!type) {
        return Error("Expected valid type after array declaration");
    }

    return new ArrayDecl(expression, type);
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

ASTNode * Parser::parse_statements() {
    switch( lexer->current_token() ) {
        case (int)Token::IDENTIFIER:
            return parse_identifier();
        case (int)Token::IF:
            return parse_if();
        case (int)Token::FOR:
            return parse_for();
        case (int)Token::WHILE:
            return parse_while();
        case (int)Token::VAR:
            return parse_var();
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
        if ( !RHS ) { return nullptr; }

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
        return new Unary(unary_op, operand);
    }

    return 0;
}

ASTNode * Parser::parse_expression() {
    ASTNode *LHS = parse_unary();
    if ( !LHS ) { return 0; }

    return parse_binary_op_rhs(0, LHS);
}

ASTNode * Parser::parse_arg() {

    if ( lexer->current_token() != (int)Token::IDENTIFIER ) {
        return Error("Expected identifier as argument name");
    }

    string arg_name = lexer->identifier();

    lexer->next();

    ASTNode *type = parse_types();

    if (!type){
        return Error("Expected valid type for argument");
    }
    
    lexer->next();

    return new Argument(make_pair(arg_name, type));
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

    vector<ASTNode*> arg_names;

    lexer->next();

    while ( lexer->current_token() == (int)Token::IDENTIFIER) {
        arg_names.push_back(parse_arg());

        if ( lexer->current_token() != ',') { break; }

        lexer->next();
    }

    if ( lexer->current_token() != ')' ) {
        return ErrorP("Expected ')' in prototype");
    }

    lexer->next();

    Prototype * prot = new Prototype(func_name, arg_names);
    addDecl(make_pair(func_name, prot));
    return prot;
}

Routine * Parser::parse_routine() {
    lexer->next();

    Prototype *proto = parse_prototype();

    if ( !proto ) { return nullptr; }

    if ( lexer->current_token() != ':') {
        ErrorR("Expected : before type declaration in routine");
    }

    ASTNode *type = parse_types();

    if (lexer->current_token() != (int) Token::IS ){
        ErrorR("Expected is before routine body declaration");
    }
    openScope();
    ASTNode *expression = parse_expression();

    closeScope();
    return new Routine(proto, expression);
}
                program_decl.push_back(parse_top_level_expression())

Prototype * Parser::parse_extern() {
    lexer->next();

    return parse_prototype();
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
    bool reverse = (lexer->current_token() == (int)Token::REVERSE);
    lexer->next();

    ASTNode *start = parse_expression();
    if ( start == 0 ) { return 0; }

    if ( lexer->current_token() != '.'){
        return Error("Expected '..' after for start value");
    }else{
        lexer->next();
        if (lexer->current_token() != '.') {
            return Error("Expected '..' after for start value");
        }
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

    ASTNode *condition = parse_expression();
    if ( !condition ) { return nullptr; }

    if (lexer->current_token() != (int)Token::LOOP) {
        return Error("Expected 'loop' after expression in 'while'");
    }

    lexer->next();

    ASTNode *body = parse_expression();
    if ( !body ) { return nullptr; }

    if (lexer->current_token() != (int)Token::END){
        return Error("Expected 'end' at the end of the 'loop' body expression");
    }
    lexer->next();

    return new While(condition, body);
}

Program * Parser::parse() {
    vector<ASTNode*> program_decl; 
    while (1) {
        switch (lexer->current_token()) {
            case (int)Token::EOF_:
                return;
            case (int)Token::VAR:
                program_decl.push_back(parse_var());
                break;
            case (int)Token::ROUTINE:
                program_decl.push_back(parse_routine());
                break;
            case (int)Token::TYPE:
                program_decl.push_back(parse_type());
            default:
                std::cerr << "Can't handle top level \n";
                break;
        }
    }
    return new Program(program_decl);
}

void Parser::addDecl(pair<string, ASTNode*> decl) {

}

ASTNode *Parser::findDecl(string name) {

}

void Parser::openScope(){

}

void Parser::closeScope(){

}