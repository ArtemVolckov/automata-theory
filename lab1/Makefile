CC = gcc

REGEX_DIR = regex
SMC_DIR = smc
FLEX_DIR = flex

REGEX_SRC = $(REGEX_DIR)/regex.c
REGEX_EXE = $(REGEX_SRC:.c=)

SMC_SRC = $(SMC_DIR)/smc.c
SMC_RECOGNIZER_SRC = $(SMC_DIR)/SmcRecognizer.c
SMC_RECOGNIZER_SM_SRC = $(SMC_DIR)/SmcRecognizer_sm.c
SMC_EXE = $(SMC_SRC:.c=)

FLEX_SRC = $(FLEX_DIR)/lex.yy.c
FLEX_EXE = $(FLEX_DIR)/lexer
FLEX_FLAGS = -lfl

GENERATOR_SRC = generator.c
GENERATOR_EXE = $(GENERATOR_SRC:.c=)

HASHMAP_SRC = hashmap.c

PARSER_SRC = output_parser.c
PARSER_EXE = $(PARSER_SRC:.c=)

all: $(REGEX_EXE) $(SMC_EXE) $(FLEX_EXE) $(GENERATOR_EXE) $(PARSER_EXE)

clean:
	rm -f $(REGEX_EXE) $(SMC_EXE) $(FLEX_EXE) $(GENERATOR_EXE) $(PARSER_EXE)

$(REGEX_EXE): $(REGEX_SRC)
	$(CC) $< -o $@

$(SMC_EXE): $(SMC_SRC)
	$(CC) $(SMC_RECOGNIZER_SRC) $(SMC_RECOGNIZER_SM_SRC) $< -o $@

$(FLEX_EXE): $(FLEX_SRC)
	$(CC) $(FLEX_FLAGS) $< -o $@

$(GENERATOR_EXE): $(GENERATOR_SRC)
	$(CC) $< -o $@

$(PARSER_EXE): $(PARSER_SRC)
	$(CC) $(HASHMAP_SRC) $< -o $@
