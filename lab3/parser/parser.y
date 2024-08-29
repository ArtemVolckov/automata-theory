%{
#include <iostream>
#include <string>
#include "../ast/ast.hpp"

struct Value {
    int int_val;
    std::string str_val;
};

#define YYSTYPE Value

int yylex();
void yyerror(const char* s);
%}

%token INTEGER_LITERAL STRING_LITERAL BOOL_LITERAL NAME
%token ASSIGN TO ELIPSIS TYPE ARITHMETIC_OP LOGICAL_OP
%token VECTOR PUSH_POP_FRONT_BACK
%token DO UNTIL 
%token IF THEN ELSE 
%token FUNCTION RETURN

%right '=' ASSIGN
%left ARITHMETIC_OP
%left LOGICAL_OP

%nonassoc '(' ')'
%nonassoc '[' ']'

%%
program:
    function_declarations
    ;

function_declarations:
    function_declarations function_declaration {

    }
    | function_declaration {

    }
    ;

function_declaration:
    FUNCTION TYPE NAME '(' parameter_list ')' '\n' statements {

    }
    | '\n'    
    ;

parameter_list:
    parameter_list ',' ELIPSIS {

    }
    | parameter_list ',' parameter {

    }
    | parameter {

    }
    | {

    }
    ;

parameter:
    NAME '=' INTEGER_LITERAL {

    }
    | NAME '=' BOOL_LITERAL {

    }
    | NAME '=' STRING_LITERAL {

    } 
    | NAME {

    }
    ;

statements:
    statements statement '\n' {

    }
    | statement '\n' {

    }
    ;

statement:
    TYPE variables_list '\n' {

    }
    | VECTOR TYPE vector_variables_list '\n' {

    }
    | RETURN expression '\n' {

    }
    | IF expression THEN statements ELSE statements {

    }
    | DO statements UNTIL expression '\n' {

    }
    | expression '\n' {

    }
    ;

variables_list:
    variables_list ',' variable {

    }
    | variable {

    }
    ;

variable:
    NAME ASSIGN INTEGER_LITERAL {

    }
    | NAME ASSIGN BOOL_LITERAL {

    }
    | NAME ASSIGN STRING_LITERAL {

    }
    | NAME {

    }
    ;

vector_variables_list:
    vector_variables_list ',' vector_variable {

    }
    | vector_variable {

    }
    ;

vector_variable:
    NAME {

    }
    ;

expression:
    INTEGER_LITERAL {
        
    }
    | BOOL_LITERAL {

    }
    | STRING_LITERAL {

    }
    | TYPE {

    }
    | expression ARITHMETIC_OP expression {

    }
    | expression LOGICAL_OP expression {

    }
    ;
%%

void yyerror(const char* s) {
    std::cerr << s << std::endl;
}

int main() {
    if (yyparse() == 0)
        std::cout << "Parsing completed successfully." << std::endl;
    else {
        std::cerr << "Parsing failed." << std::endl;
        return 1;
    }
    return 0;
}
