%{

#include <iostream>
#include <string>
#include <string_view>

%}

%%

-?[0-9]+                     { yylval.int_val = atoi(yytext); return INTEGER_LITERAL; }
true|false|undefined         { yylval.str_val = yytext; return BOOL_LITERAL; }
\"[^\"]*\"|\'[^\']*\'        { std::string tmp_str(yytext); yylval.str_val = tmp_str.substr(1, tmp_str.length() - 2); return STRING_LITERAL; }
boolean|integer|string       { yylval.str_val = yytext; return TYPE; }
"vector of"                  { return VECTOR; }
(push|pop)[ \t]+(front|back) { yylval.str_val = yytext; return PUSH_POP_FRONT_BACK }
to                           { return TO }
do                           { return DO; }
until                        { return UNTIL; }
if                           { return IF; }
then                         { return THEN; }
else                         { return ELSE; }
"function of"                { return FUNCTION; }
return                       { return RETURN; }
application                  { return APPLICATION; }
"+"|"-"|"*"|"/"              { yylval.str_val = yytext; return ARITHMETIC_OP; }
"="                          { return '='; }
"<>"|"<"|">"                 { yylval.str_val = yytext; return LOGICAL_OP; }
"("                          { return '('; }
")"                          { return ')'; }
","                          { return ','; }
"\n"                         { return '\n' }
[ \t]+                       {}
.                            { std::cout << "Unknown expression: '" << yytext << "'" << std::endl; }

%%

void yyerror(std::string_view err_msg) {
    std::cerr << "Lexical error: " << err_msg << std::endl;
}

int main() {
    yylex(); 
    return 0;
}
