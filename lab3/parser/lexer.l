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
to                            { }
do                            { }
until                         { }
if                            { }
then                          { }
else                          { }
"function of"                 { }
return                        { }
application                   { }
"+"|"-"|"*"|"/"               { }
"="                           { }
"<>"|"<"|">"                  { }
"("                           { }
")"                           { }
","                           { }
"\n"                          { }
[ \t]+                        { }
.                             { fprintf(stderr, "Unknown expresion: %s\n", yytext); }
%%
