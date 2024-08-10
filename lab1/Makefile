CC = gcc

CC_FLAGS =

REGEX_SRC = regex.c
REGEX_EXE = $(REGEX_SRC:.c=)

all: $(REGEX_EXE)

$(REGEX_EXE): $(REGEX_SRC)
	$(CC) $< -o $@
