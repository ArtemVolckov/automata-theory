%{
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

void yyerror(const char *s);
int yylex();

enum VarType { INTEGER, BOOLEAN, STRING };

struct Var {
    VarType type;
    union {
        int intValue;
        bool boolValue;
        string strValue;
    };
};

// Хранение переменных
map<string, Var> variables;  
%}

%union {
    int intval;
    bool boolval;
    char *strval;
}

%token <intval> INTEGER_LITERAL
%token <boolval> TRUE FALSE UNDEFINED
%token <strval> STRING_LITERAL
%token BOOLEAN INTEGER STRING
%token PUSH POP FRONT BACK
%token DO UNTIL IF THEN ELSE
%token RIGHT LEFT FORWARD BACK ROTATE_RIGHT ROTATE_LEFT
%token LSM REFLECT DRILL
%token FUNCTION RETURN APPLICATION
%token BEGIN END
%token ASSIGN NE // Определение токенов для присвоения и неравенства
%token IDENTIFIER // Добавлен токен для идентификаторов

%type <intval> expression
%type <boolval> logical_expression
%type <strval> statement
%type <strval> variable_declaration
%type <strval> array_declaration
%type <strval> statements // Добавлено объявление для statements

%%

// Начальная точка входа
program:
    program statement '\n'
    | /* пусто */
    ;

statements:
    statements statement '\n'  // Определение для последовательности операторов
    | /* пусто */
    ;

statement:
    variable_declaration
    | array_declaration
    | assignment
    | if_statement
    | loop
    | robot_command
    | function_definition
    | function_call
    | BEGIN statements END // Используем определение statements
    ;

variable_declaration:
    BOOLEAN variable_list ';'
    | INTEGER variable_list ';'
    | STRING variable_list ';'
    ;

variable_list:
    variable_list ',' variable
    | variable
    ;

variable:
    IDENTIFIER
    ;

array_declaration:
    "vector of" type IDENTIFIER ';'
    ;

type:
    INTEGER
    | BOOLEAN
    | STRING
    ;

assignment:
    variable ASSIGN expression ';' // Изменено на ASSIGN
    ;

if_statement:
    IF logical_expression THEN statement ELSE statement
    | IF logical_expression THEN statement
    ;

loop:
    DO statement UNTIL logical_expression
    ;

robot_command:
    RIGHT ';'
    | LEFT ';'
    | FORWARD ';'
    | BACK ';'
    | ROTATE_RIGHT ';'
    | ROTATE_LEFT ';'
    | LSM ';'
    | REFLECT ';'
    | DRILL ';'
    ;

function_definition:
    FUNCTION IDENTIFIER '(' parameter_list ')' statement
    ;

parameter_list:
    parameter_list ',' parameter
    | parameter
    ;

parameter:
    IDENTIFIER '=' expression
    | IDENTIFIER
    ;

function_call:
    IDENTIFIER '(' argument_list ')' ';'
    ;

argument_list:
    argument_list ',' expression
    | expression
    ;

expression:
    INTEGER_LITERAL
    | variable
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | '(' expression ')'
    ;

logical_expression:
    expression '=' expression
    | expression NE expression // Изменено на NE
    | expression '<' expression
    | expression '>' expression
    | TRUE
    | FALSE
    | UNDEFINED
    ;

%%

// Функция обработки ошибок
void yyerror(const char *s) {
    cerr << "Error: " << s << endl;
}

int main() {
    cout << "Starting the interpreter..." << endl;
    yyparse(); // Запускаем парсер
    return 0;
}