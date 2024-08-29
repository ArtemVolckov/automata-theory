%{
#include <iostream>
#include <string>

struct Value {
    int int_val;
    std::string str_val;
};
#define YYSTYPE Value

#include "parser.tab.h"
%}

%option noyywrap

%%
-?[0-9]+                      { yylval.int_val = atoi(yytext); return INTEGER_LITERAL; }
true|false|undefined          { yylval.str_val = yytext; return BOOL_LITERAL; }
\"[^\"]*\"|\'[^\']*\'         { std::string tmp_str = std::string(yytext); 
                                yylval.str_val = tmp_str.substr(1, tmp_str.length() - 2); 
                                return STRING_LITERAL;}
boolean|integer|string        { yylval.str_val = yytext; return TYPE; }
"vector of"                   { return VECTOR; }
(push|pop)[ \t ]+(front|back) { yylval.str_val = yytext; return PUSH_POP_FRONT_BACK; }
to                            { return TO; }
do                            { return DO; }
until                         { return UNTIL; }
if                            { return IF; }
then                          { return THEN; }
else                          { return ELSE; }
"function of"                 { return FUNCTION; }
return                        { return RETURN; }
"+"|"-"                       { yylval.str_val = yytext; return ARITHMETIC_OP; }
"<>"|"<"|">"                  { yylval.str_val = yytext; return LOGICAL_OP; }
"="                           { return '='; }
":="                          { return ASSIGN; }
"("                           { return '('; }
")"                           { return ')'; }
"["                           { return '['; }
"]"                           { return ']'; }
","                           { return ','; }
"\n"                          { return '\n'; }
"..."                         { return ELIPSIS; }
[ \t]+                        { }
[a-zA-Z_][a-zA-Z0-9_]*        { yylval.str_val = yytext; return NAME; }
.                             { std::cerr << "Unknown expresion: " << yytext << std::endl; }
%%
