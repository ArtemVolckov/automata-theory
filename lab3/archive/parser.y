%{
    %option c++
    #include <iostream>
    int yylex(void);
    void yyerror(const char*);
%}

%token INTEGER

%%

program:
    program '\n' {
        std::cout << "empty string" << std::endl;
    }
    | program expr '\n' {
        std::cout << "result = " << $2
    }
    | {
        std::cout << "enter an expression:" << std::endl; 
    }
    ;
expr:
    expr '+' term {
        $$ = $1 + $3;
        std::cout << "expr=" << $1 << " + term=" << $3 << " to expr : " << $$ << std::endl;
    }
    | expr '-' term {
        $$ = $1 - $3;
        std::cout << "expr=" << $1 << " - term=" << $3 << " to expr : " << $$ << std::endl;
    }
    | term {
        std::cout << "term=" << $1 << " to exrp : " << $$ << std::endl;
    }
    ;
term: 
    term '*' factor {
        $$ = $1 * $3;
        std::cout << "term=" << $1 << " * factor=" << $3 << " to term : " << $$ << std::endl;
    }
    | term '/' factor {
        $$ = $1 / $3;
        std::cout << "term=" << $1 << " / factor=" << $3 << " to term : " << $$ << std::endl;
    }
    | factor {
        $$ = $1;
        std::cout << "factor " << $1 << " to term : " << $$ << std::endl;
    }
    ;
factor: 
    INTEGER {
        std::cout << "int=" << $1 << " to factor : " << $$ << std::endl;     
    }
    | '(' expr ')' {
        $$ = $2;
        std::cout << "( expr=" << $2 << " ) to factor : " << $$ << std::endl;
    }
    ;

%%

void yyerror(const char* s) {
    std::cerr << s << std::endl;
}

int yylex(void) {
	int c;

	while ((c = getchar()) == ' ' || c == '\t')
	;
	if (isdigit(c)) {
		ungetc (c, stdin);
		scanf ("%d", &yylval);
		return INTEGER;
	}
	if (c == EOF)
		return 0;
	return c;  
}

int main() {
    yyparse();
    return 0; 
}
