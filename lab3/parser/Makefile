CC = g++ -g

EXE = lab3

LEXER_SRC = lexer.l
LEXER = lex.yy.c

PARSER_SRC = parser.y
PARSER = parser.tab.c
PARSER_HEADER = parser.tab.h

AST_SRC = ../ast/ast.cpp

all: $(EXE)

clean:
	rm -f $(EXE) $(LEXER) $(PARSER) $(PARSER_HEADER)

$(EXE): $(LEXER) $(PARSER) $(AST_SRC)
	$(CC)  $^ -o $@

$(LEXER): $(LEXER_SRC)
	flex -o $@ $<

$(PARSER): $(PARSER_SRC)
	bison -d -o $@ $<
