%{
#include <iostream>
#include <string>
#include <cstdlib>

typedef struct value {
    bool is_defined;
    bool bool_val;
    int int_val;
    std::string str_val;
} value;

#define YYSTYPE value

void yyerror(const char *s);
int yylex(void);

%}

%token INTEGER_LITERAL BOOL_LITERAL STRING_LITERAL TYPE VECTOR PUSH_POP_FRONT_BACK
%token TO DO UNTIL IF THEN ELSE FUNCTION RETURN APPLICATION
%token ARITHMETIC_OP LOGICAL_OP

%left ELSE
%left THEN
%left IF
%left '='
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

void yyerror(const char *s) {
    std::cerr << "Syntax error: " << s << std::endl;
}

int main() {
    return yyparse();
}