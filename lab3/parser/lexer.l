%{
#include <stdio.h>
#include "parser.tab.h"
%}

%option noyywrap

%%
-?[0-9]+                      { }
true|false|undefined          { }
\"[^\"]*\"|\'[^\']*\'         { }
boolean|integer|string        { }
"vector of"                   { }
(push|pop)[ \t ]+(front|back) { }
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
