CC = gcc

EXE = lab3

LEXER_SRC = lexer.l
LEXER = lex.yy.c

PARSER_SRC = parser.y
PARSER = parser.tab.c

all: $(EXE)

$(EXE): $(LEXER) $(PARSER) 
	$(CC) -lfl $^ -o $@

$(LEXER): $(LEXER_SRC)
	flex -o $@ $<

$(PARSER): $(PARSER_SRC)
	bison -d -o $@ $<
