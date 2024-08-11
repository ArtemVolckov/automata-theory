CC = gcc

CC_FLAGS =

REGEX_SRC = regex.c
REGEX_EXE = $(REGEX_SRC:.c=)

GENERATOR_SRC = generator.c
GENERATOR_EXE = $(GENERATOR_SRC:.c=)

all: $(REGEX_EXE) $(GENERATOR_EXE)

clean:
	rm -f $(REGEX_EXE) $(GENERATOR_EXE)

$(REGEX_EXE): $(REGEX_SRC)
	$(CC) $< -o $@

$(GENERATOR_EXE): $(GENERATOR_SRC)
	$(CC) $< -o $@
