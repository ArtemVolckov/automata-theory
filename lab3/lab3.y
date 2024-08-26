%{
	#include "nodes.h"
	#include "robot.h"
	#include "tree_parser.h"
	#define YYSTYPE val
	struct val
	{
		char *text;
		bool one = true;
		int line;
		int err_type;
		node *tree;
	};
	ast *syntax_tree;
	bool error = false;
	#include <iostream>
	#include <string>
	#include <fstream>
	#include <vector>
	#include <stdio.h>
	#include <stdbool.h>
	#include <math.h>
	int yylex(void);
	void yyerror(const char*);
%}

%locations

%token INTNUM
%token BOOLNUM
%token TYPE
%token UNDEF
%token SVAL
%token LITERAL
%token RECORD
%token DATA
%token CONVERSION
%token TO
%token FROM
%token PROC
%token BLOCK
%token UNBLOCK
%token MOVE
%token PING
%token VISION
%token VOICE
%token CALL
%token WHILE
%token EF
%left '='
%left '@'
%left ','
%left '>' '<'
%left '+' '-'
%left '?' '!'
%left '*' '/'
%left '^'
%left '[' ']'
%left SVAL
%right UMINUS

%%

program:
	program record '\n' {
		std::cout << "HERE RECORD\n";
		if (!error)
		{
			std::cout << "SYNTAX TREE:\n";
			if ($2.tree) {syntax_tree->add($2.tree);}
			syntax_tree->put_tree(syntax_tree->root, 0);
		}
		else
		{
			std::cout << "some errors occured, semantic analysis isn't possible\n";
		}
	}
	| program block '\n' {
		std::cout << "HERE BLOCK\n";
		if (!error)
		{
			std::cout << "SYNTAX TREE:\n";
			syntax_tree->put_tree(syntax_tree->root, 0);
		}
		else
		{
			std::cout << "some errors occured, semantic analysis isn't possible\n";
		}
	}
	| program proc '\n' {
		std::cout << "HERE PROC\n";
		if (!error)
		{
			std::cout << "SYNTAX TREE:\n";
			if ($2.tree) {syntax_tree->add($2.tree);}
			syntax_tree->put_tree(syntax_tree->root, 0);
		}
		else
		{
			std::cout << "some errors occured, semantic analysis isn't possible\n";
		}
	}
	| program sentence '\n' {
		std::cout << "HERE SENTENCE\n";
		if (!error)
		{
			std::cout << "SYNTAX TREE:\n";
			if ($2.tree) {syntax_tree->add($2.tree);}
			syntax_tree->put_tree(syntax_tree->root, 0);
		}
		else
		{
			std::cout << "some errors occured, semantic analysis isn't possible\n";
		}
	}
	| program error '\n' {
		error = true;
		std::cout << "Some error in line " << $2.line << "\n";		
		yyerrok;
	}
	| program EF {printf("Programm finished successfully!\n"); error = false; return 0;}
	| {
		syntax_tree = new ast();
		printf("enter a expression:\n");
	}
	;
record:
	RECORD SVAL DATA '[' group_comma ']' '\n' CONVERSION FROM conv_proc_set  CONVERSION TO conv_proc_set
	{
		$$.tree = new record_node(std::string($2.text), $5.tree, $10.tree, $13.tree , RECORDN, $1.line);
	}
	|	RECORD SVAL DATA '[' group_comma ']' '\n' CONVERSION FROM conv_proc_set
	{
		$$.tree = new record_node(std::string($2.text), $5.tree, $10.tree, nullptr, RECORDN, $1.line);
	}
	| 	RECORD SVAL DATA '[' group_comma ']' '\n' CONVERSION TO conv_proc_set
	{
		std::cout <<"$2 TEXT: " << $2.text << "\n";
		$$.tree = new record_node(std::string($2.text), $5.tree, nullptr, $10.tree , RECORDN, $1.line);
	}
	|	RECORD SVAL DATA '[' group_comma ']' '\n'
	{
		$$.tree = new record_node(std::string($2.text), $5.tree, nullptr, nullptr , RECORDN, $1.line);
	}
	;
block:
	BLOCK '\n' sentence UNBLOCK
	{
		$$.tree = new block_node($3.tree, BLOCKN, $3.line);
	}
	| BLOCK '\n' UNBLOCK
	{
		$$.tree = new block_node(nullptr, BLOCKN, $1.line);
	}
	;

proc:
	PROC SVAL group_comma '&' block 
	{
			$$.tree = new proc_node(std::string($2.text), $3.tree, $5.tree, PROCN, $1.line);
	}
	| SVAL SVAL group_comma '&' block
	{
			std::cout << "Wrong definition of procedure in line " << $1.line << ". Procedures aren't able to return any value in this programming language\n";
			error = true;
	}
	| TYPE SVAL group_comma '&' block
	{
			std::cout << "Wrong definition of procedure in line " << $1.line << ". Procedures aren't able to return any value in this programming language\n";
			error = true;
	}
	;

declaration:
	SVAL SVAL {$$.tree = new decl_node(std::string($1.text), std::string($2.text), nullptr, nullptr, UNDEFVARN, $1.line);
	syntax_tree->put_tree($$.tree, 0);}
	| TYPE SVAL {$$.tree = new decl_node(std::string($1.text), std::string($2.text), nullptr, nullptr, UNDEFVARN, $1.line);
	syntax_tree->put_tree($$.tree, 0);}
	| TYPE SVAL '=' expr	{$$.tree = new decl_node(std::string($1.text), std::string($2.text), nullptr, $4.tree, VARN, $1.line);  printf("NAME: %s\n", $2.text); printf("TYPE: %s\n", $1.text); syntax_tree->put_tree($$.tree, 0);}
	| SVAL SVAL '=' expr	{$$.tree = new decl_node(std::string($1.text), std::string($2.text), nullptr, $4.tree, VARN, $1.line);  printf("NAME: %s\n", $2.text); printf("TYPE: %s\n", $1.text); syntax_tree->put_tree($$.tree, 0);}
	| TYPE SVAL '[' expr ']' {
		$$.tree = new decl_node(std::string($1.text), std::string($2.text), $4.tree, nullptr, UNDEFVARN, $1.line); syntax_tree->put_tree($$.tree, 0);  
	}
	;

sentence:
	declaration '\n'  {$$ = $1; }
	| expr '\n' {$$ = $1; }
	| cond '\n' {$$ = $1;}
	| declaration '\n' sentence {if ($1.tree && $3.tree) {$3.tree->set_left($1.tree); $$ = $3; syntax_tree->put_tree($$.tree, 0);} std::cout << "SENTENCE AND GROUP SET\n"; }
	| expr '\n' sentence {if ($1.tree && $3.tree) {$3.tree->set_left($1.tree); $$ = $3; syntax_tree->put_tree($$.tree, 0);} std::cout << "EXPR AND GROUP SET\n"; }
	| cond '\n' sentence {if ($1.tree && $3.tree) {$3.tree->set_left($1.tree); $$ = $3; syntax_tree->put_tree($$.tree, 0);} std::cout << "BLOCK AND GROUP SET\n";}
	;

cond:
	'{' expr '}' block
	{
		$$.tree = new cond_node($2.tree, $4.tree, CONDN, $1.line);
	}
	| WHILE expr block
	{
		std::cout << "Wrong loop declaration in line " << $2.line << "\n";
		error = true;
	}
	;

group_comma:
	declaration {$$ = $1;}
	| declaration ',' group_comma {$3.tree->set_left($1.tree); $$ = $3; std::cout << "DECLARATION GROUP COMMA\n"; syntax_tree->put_tree($$.tree, 0);}
	;

conv_proc_set:
	TYPE block '\n' {$$.tree = new conv_node(std::string($1.text), $2.tree, CONVPROCN, $1.line);}
	| TYPE block '\n' conv_proc_set {$3.tree->set_left($1.tree); $$ = $3; std::cout << "CONV_PROC AND CONV_PROC SET\n"; syntax_tree->put_tree($$.tree, 0);}
	;

arg_set:
	expr { $$ = $1;}
	| expr ',' arg_set {$3.tree->set_left($1.tree); $$ = $3; std::cout << "EXPR AND ARG_SET\n"; syntax_tree->put_tree($$.tree, 0);}
	| {$$.tree = nullptr;}
	;

expr:
	SVAL {$$.tree = new str_node(std::string($1.text), STRN, $1.line); printf("SVAL WITH VAL = \"%s\"\n", $1.text);}
	| LITERAL {$$.tree = new str_node(std::string($1.text), LITERALN, $1.line);  printf("LITERAL WITH VAL = \"%s\"\n", $1.text);}
	| INTNUM {$$.tree = new int_node(atoi($1.text), INTN, $1.line); printf("INTNUM WITH LINE: %d\n", $1.line); printf("INTNUM %d\n", atoi($1.text));}
	| BOOLNUM {bool buf; if (strcmp($1.text, "TRUE") == 0) {buf = true;} else {buf = false;} $$.tree = new bool_node(buf,
	 BOOLN, $1.line); printf("BOOLNUM %d\n", buf);}
	| '(' expr ')' {$$.tree = $2.tree;}
	| expr '<' expr {$$.tree = new operation_node($1.tree, $3.tree, LESSN, $1.line); }
	| expr '>' expr {$$.tree = new operation_node($1.tree, $3.tree, GREATERN, $1.line); }
	| expr '+' expr {$$.tree = new operation_node($1.tree, $3.tree, PLUSN, $1.line); }
	| expr '-' expr {$$.tree = new operation_node($1.tree, $3.tree, NEGN, $1.line); }
	| expr '?' expr {$$.tree = new operation_node($1.tree, $3.tree, EQUN, $1.line); }
	| expr '!' expr {$$.tree = new operation_node($1.tree, $3.tree, NOTEQUN, $1.line); }
	| expr '*' expr {$$.tree = new operation_node($1.tree, $3.tree, MULN, $1.line); }
	| expr '/' expr {$$.tree = new operation_node($1.tree, $3.tree, DIVN, $1.line); }
	| expr '^' expr {$$.tree = new operation_node($1.tree, $3.tree, EXPN, $1.line); }
	| '-' expr %prec UMINUS {$$.tree = new unary_node($1.tree, UMINN, $1.line);}
	| expr '[' expr ']' {
		$$.tree = new arr_node($1.tree, $3.tree, ARRASSIGNN, $1.line);
	}
	| expr '=' expr {
            $$.tree = new assign_node($1.tree, $3.tree, ASSIGNN, $1.line);
             syntax_tree->put_tree($$.tree, 0); 
	}
	| SVAL '.' SVAL {$$.tree = new struct_ref_node(std::string($1.text), std::string ($3.text), STRUCTREFN, $1.line);}
	| '@' SVAL arg_set '|'
	{
		    std::cout << "CALL HERE!\n";
	            $$.tree = new proc_node(std::string($2.text), $3.tree, nullptr, CALLN, $1.line);
	}
	| CALL SVAL arg_set '|'
	{
		std::cout << "Wrong calling of function in line " << $1.line << "\n";
		error = true;
	}
	| MOVE '[' expr ']'
	{
		int op;
		if (strcmp($1.text, "MOVERIGHT") == 0)
		{
			op = MOVERIGHT;
		}
		else if (strcmp($1.text, "MOVELEFT") == 0)
		{
			op = MOVELEFT;
		}
		else if (strcmp($1.text, "MOVEUP") == 0)
		{
			op = MOVEUP;
		}
		else
		{
			op = MOVEDOWN;
		}
		$$.tree = new move_node($3.tree, op, $1.line);
	}
	| PING '[' expr ']'
	{
                int op;
                if (strcmp($1.text, "PINGRIGHT") == 0)
                {
                        op = PINGRIGHT;
                }
                else if (strcmp($1.text, "PINGLEFT") == 0)
                {
                        op = PINGLEFT;
                }
                else if (strcmp($1.text, "PINGUP") == 0)
                {
                        op = PINGUP;
                }
                else
                {
                        op = PINGDOWN;
                }
                $$.tree = new ping_node($3.tree, op, $1.line);
	}
	| VISION '[' expr ']'
	{
                $$.tree = new vision_node($3.tree, VISIONN, $1.line);
	}
    | VOICE '[' expr ']'
    {
            $$.tree = new voice_node($3.tree, VOICEN, $1.line);
    }
	;
	 

%%

int main() {
	yyparse();

	if (!error) {
		std::string line;
		std::vector<std::string> v;
		std::ifstream in;
		in.open("maze.txt");
		if (in.is_open()) {
			while(std::getline(in,line))
			{
				v.push_back(line);
			}
			in.close();
		}
		robot *r = new cell_robot(v);
		//std::cout << "BEFORE\n";
		//r.print_field();
		if (syntax_tree->root)
		{
			std::cout << "GLOBAL\n";
			tree_parser x;
			x.parse(syntax_tree->root, x.global, r);
			x.global.print();
		}
		//std::cout << "AFTER\n";
		//r.print_field();
	}
	return 0;
}
