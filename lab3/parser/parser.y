%union {
    int int_val;
    char* str_val;
}

%{
#include <stdio.h>
#include "../ast/ast.h"

int yylex();
void yyerror(const char* s);
%}

%token ASSIGN TO ELIPSIS
%token VECTOR PUSH_POP_FRONT_BACK
%token DO UNTIL 
%token IF THEN ELSE 
%token FUNCTION RETURN APPLICATION

%token <int_val> INTEGER_LITERAL
%token <str_val> STRING_LITERAL BOOL_LITERAL TYPE ARITHMETIC_OP LOGICAL_OP NAME

%right '=' ASSIGN
%left ARITHMETIC_OP
%left LOGICAL_OP

%nonassoc '(' ')'

%%

program:
    function_declarations
    ;

function_declarations:
    function_declarations function_declaration
    | function_declaration
    ;

function_declaration:
    FUNCTION TYPE NAME '(' parameter_list ')' statements {
    }
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
    statements statement
    | statement
    ;

statement:
    RETURN expression '\n' {

    }
    | IF expression THEN statements ELSE statement '\n' {

    }
    | DO statement UNTIL expression '\n' {

    }
    | FUNCTION TYPE '(' ')' TO TYPE DO statement RETURN expression '\n' {

    }
    | application '\n' {

    }
    | expression '\n' {

    }
    ;

expression:
    INTEGER_LITERAL {
        printf("%d\n", $1);
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
    | '(' expression ')' {

    }
    |
    ;

application:
           APPLICATION '(' arguments ')' {

    }
    ;

arguments:
    expression {} {

    }
    | arguments ',' expression {

    }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
    if (yyparse() == 0)
        printf("Parsing completed successfully.\n");
    else {
        fprintf(stderr, "Parsing failed.\n");
        return 1;
    }
    return 0;
}
