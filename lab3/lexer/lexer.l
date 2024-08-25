%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
%}

%%

// Определение лексем
[0-9]+              { yylval.intval = atoi(yytext); return INTEGER_LITERAL; }
"true"             { yylval.boolval = true; return TRUE; }
"false"            { yylval.boolval = false; return FALSE; }
"undefined"        { yylval.boolval = false; return UNDEFINED; }
\"([^\"]*)\"       { yylval.strval = strdup(yytext); return STRING_LITERAL; }
\'([^\']*)\'       { yylval.strval = strdup(yytext); return STRING_LITERAL; }
"boolean"          { return BOOLEAN; }
"integer"          { return INTEGER; }
"string"           { return STRING; }
"vector of"        { return PUSH; }
"do"               { return DO; }
"until"            { return UNTIL; }
"if"               { return IF; }
"then"             { return THEN; }
"else"             { return ELSE; }
"right"            { return RIGHT; }
"left"             { return LEFT; }
"forward"          { return FORWARD; }
"back"             { return BACK; }
"rotate_right"     { return ROTATE_RIGHT; }
"rotate_left"      { return ROTATE_LEFT; }
"lms"              { return LSM; }
"reflect"          { return REFLECT; }
"drill"            { return DRILL; }
"function"         { return FUNCTION; }
"return"           { return RETURN; }
"application"      { return APPLICATION; }
"begin"            { return BEGIN; }
"end"              { return END; }
"+"                { return '+'; }
"-"                { return '-'; }
"*"                { return '*'; }
"/"                { return '/'; }
"="                { return '='; }
"<>"               { return '<>'; }
"<"                { return '<'; }
">"                { return '>'; }
"("                { return '('; }
")"                { return ')'; }
","                { return ','; }
";"                { return ';'; }
[ \t\n]+           { /* игнорируем пробелы и переводы строк */ }
.                  { printf("Неправильный символ: %s\n", yytext); }

%%

// Функция для обработки ошибок
void yyerror(const char *s) {
    std::cerr << "Лексическая ошибка: " << s << std::endl;
}

int main() {
    yylex(); // Запуск лексического анализатора
    return 0;
}