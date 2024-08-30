CC = g++

EXE = lab3

LEXER_SRC = lexer.l
LEXER = lex.yy.c

PARSER_SRC = parser.y
PARSER = parser.tab.c
PARSER_HEADER = parser.tab.h

all: $(EXE)

clean:
	rm -f $(EXE) $(LEXER) $(PARSER) $(PARSER_HEADER)

$(EXE): $(LEXER) $(PARSER) 
	$(CC)  $^ -o $@

$(LEXER): $(LEXER_SRC)
	flex -o $@ $<

$(PARSER): $(PARSER_SRC)
	bison -d -o $@ $<
