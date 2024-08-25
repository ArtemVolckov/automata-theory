CC = g++

SRCS = main.cpp ast/ast.cpp

EXE = main

LEXER_SRC = lexer/lexer.l
LEXER = lexer/lexer.cpp

PARSER_SRC = parser/parser.y
PARSER = parser/parser.cpp

all = $(EXE)

$(EXE): $(SRCS) $(LEXER) $(PARSER) 
	$(CC) -lfl $^ -o $@

$(LEXER): $(LEXER_SRC)
	flex $^ -o $@

$(PARSER): $(PARSER_SRC)
	bison -d $^ -o $@
