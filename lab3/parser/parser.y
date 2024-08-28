%{
//#include <iostream>
//#include <string>
//#include <cstdlib>
#include <stdio.h>

int yylex();
void yyerror(const char* s);
%}

%token INTEGER_LITERAL BOOL_LITERAL STRING_LITERAL
%token TYPE TO ARITHMETIC_OP LOGICAL_OP
%token VECTOR PUSH_POP_FRONT_BACK
%token DO UNTIL 
%token IF THEN ELSE 
%token FUNCTION RETURN APPLICATION

%right '='
%left ARITHMETIC_OP
%left LOGICAL_OP

%nonassoc '(' ')'

%%

program:
    statements
    ;

statements:
    statement
    | statements statement
    ;

statement:
    RETURN expression '\n'
    | IF expression THEN statements ELSE statements '\n'
    | DO statements UNTIL expression '\n'
    | FUNCTION TYPE '(' ')' TO TYPE DO statements RETURN expression '\n'
    | application '\n'
    | expression '\n'
    ;

expression:
    INTEGER_LITERAL
    | BOOL_LITERAL
    | STRING_LITERAL
    | TYPE
    | expression ARITHMETIC_OP expression
    | expression LOGICAL_OP expression
    | '(' expression ')'
    ;

application:
    APPLICATION '(' arguments ')'
    ;

arguments:
    expression
    | arguments ',' expression
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
