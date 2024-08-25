%{
	#ifndef AST
	#define AST
	#include "nodes.h"
	#endif
    struct val
    {
        char *text;
		bool one = true;
		int line;
		int err_type;
		node *tree;
    };
    #define YYSTYPE val
	#include "lab3.tab.h"
	#include <cstdlib>
	#include <cstring>
	#include <cmath>
	void yyerror(const char*);
%}

%option yylineno

%%

[0-9]+ {
	std::cout << "INTNUM CAPTURED " << yytext << "\n";
	yylval.text = new char[strlen(yytext) + 1];
	strcpy(yylval.text, yytext);
	yylval.line = yylineno;
	std::cout << "INTNUM FLEX LINE " << yylineno << "\n";
	yylval.err_type = -1;
	return INTNUM;
}

TRUE|FALSE {
	yylval.text = yytext;
	yylval.line = yylineno;
	return BOOLNUM;
}

NUMERIC|LOGIC|STRING {
	yylval.text = (char*)malloc(strlen(yytext) + 1);
	strcpy(yylval.text, yytext);
	printf("TYPE CAPTURED: %s\n", yytext);
	yylval.line = yylineno;
	return TYPE;
}

VISION {
	yylval.text = yytext;
	yylval.line = yylineno;
	return VISION;
}

VOICE {
        yylval.text = yytext;
        yylval.line = yylineno;
        return VOICE;
}

PROC {
	yylval.text = yytext;
	yylval.line = yylineno;
	return PROC;
}

RECORD {
    yylval.text = (char*)malloc(strlen(yytext) + 1);
    strcpy(yylval.text, yytext);
    yylval.line = yylineno;
	return RECORD;
}

DATA {
	yylval.text = yytext;
	yylval.line = yylineno;
	return DATA;
}

CONVERSION {
	yylval.text = yytext;
	std::cout << "CONVERSION CAPTURED\n";
	yylval.line = yylineno;
	return CONVERSION;
}

TO {
	yylval.text = yytext;
	std::cout << "TO CAPTURED\n";
	yylval.line = yylineno;
	return TO;
}

FROM {
	yylval.text = yytext;
	std::cout << "FROM CAPTURED\n";
	yylval.line = yylineno;
	return FROM;
}

BLOCK {
	yylval.text = yytext;
	std::cout << "BLOCK CAPTURED\n";
	yylval.line = yylineno;
	return BLOCK;
}

UNBLOCK {
	yylval.text = yytext;
	std::cout << "UNBLOCK CAPTURED\n";
	yylval.line = yylineno;
	return UNBLOCK;
}

MOVEUP|MOVEDOWN|MOVERIGHT|MOVELEFT {
    yylval.text = (char*)malloc(strlen(yytext) + 1);
    strcpy(yylval.text, yytext);
    yylval.line = yylineno;
	return MOVE;
}

PINGUP|PINGDOWN|PINGLEFT|PINGRIGHT {
    yylval.text = (char*)malloc(strlen(yytext) + 1);
    strcpy(yylval.text, yytext);
    yylval.line = yylineno;
	return PING;
}

CALL {
    yylval.text = (char*)malloc(strlen(yytext) + 1);
  	strcpy(yylval.text, yytext);
    yylval.line = yylineno;
    yylval.err_type = CALLN;
	return CALL;
}

WHILE {
    yylval.text = (char*)malloc(strlen(yytext) + 1);
  	strcpy(yylval.text, yytext);
    yylval.line = yylineno;
    yylval.err_type = CONDN;
	return WHILE;
}

UNDEF {
    yylval.text = (char*)malloc(strlen(yytext) + 1);
    strcpy(yylval.text, yytext);
    yylval.line = yylineno;
	return UNDEF;
}

[-&+*/^?!<>\n\"()=\[\],.{}@|] {
	std::cout << "SYMBOL CAPTURED " << yytext << "\n";
	yylval.line = yylineno;
	yylval.err_type = -1;
    return *yytext;
}

[a-zA-Z]([a-zA-Z0-9])* {
	yylval.text = (char*)malloc(strlen(yytext) + 1);
	strcpy(yylval.text, yytext);
	printf("SVAL CAPTURED: %s\n", yytext);
	yylval.line = yylineno;
	yylval.err_type = -1;
	return SVAL;
}
\"[a-zA-Z]([a-zA-Z0-9])*\" {
        yylval.text = (char*)malloc(strlen(yytext) + 1);
	int i = 0;
        for (i = 1; i < strlen(yytext) - 1; i++)
	{
		yylval.text[i-1] = yytext[i];
	}
	yylval.text[i-1] = '\0';
	printf("%d\n", i);
    printf("LITERAL CAPTURED: %s\n", yytext);
    yylval.line = yylineno;
    yylval.err_type = -1;
    return LITERAL;
}

[ \t]	;	/* skip tabs and whitespaces */

. {
	printf("%s\n", yytext);
	yyerror("Unknown character");
}

<<EOF>> {return EF;}

%%

void yyerror(const char *s)
{
	//fprintf(stderr, "%s\n", s);
}

int yywrap(void)
{
	return 1;
}
