%{
#include <stdio.h>
#include "parser.tab.h"
%}

%option noyywrap

%%
-?[0-9]+                      { yylval.int_val = atoi(yytext); return INTEGER_LITERAL; }
true|false|undefined          { yylval.str_val = strdup(yytext); return BOOL_LITERAL; }
\"[^\"]*\"|\'[^\']*\'         { yylval.str_val = strdup(yytext); return STRING_LITERAL;}
boolean|integer|string        { yylval.str_val = strdup(yytext); return TYPE; }
"vector of"                   { return VECTOR; }
(push|pop)[ \t ]+(front|back) { yylval.str_val = strdup(yytext); return PUSH_POP_FRONT_BACK; }
to                            { return TO; }
do                            { return DO; }
until                         { return UNTIL; }
if                            { return IF; }
then                          { return THEN; }
else                          { return ELSE; }
"function of"                 { return FUNCTION; }
return                        { return RETURN; }
application                   { return APPLICATION; }
"+"|"-"|"*"|"/"               { yylval.str_val = strdup(yytext); return ARITHMETIC_OP; }
"<>"|"<"|">"                  { yylval.str_val = strdup(yytext); return LOGICAL_OP; }
":="                          { return ASSIGN; }
"="                           { return '='; }
"("                           { return '('; }
")"                           { return ')'; }
","                           { return ','; }
"\n"                          { return '\n'; }
"..."                         { return ELIPSIS; }
[ \t]+                        { }
[a-zA-Z_][a-zA-Z0-9_]*        { yylval.str_val = strdup(yytext); return NAME; }
.                             { fprintf(stderr, "Unknown expresion: %s\n", yytext); }
%%
