CC = gcc

CC_FLAGS = -g

REGEX_SRC = regex.c
REGEX_EXE = $(REGEX_SRC:.c=)

GENERATOR_SRC = generator.c
GENERATOR_EXE = $(GENERATOR_SRC:.c=)

HASHMAP_SRC = hashmap.c
HASHMAP_EXE = $(HASHMAP_SRC:.c=)

all: $(REGEX_EXE) $(GENERATOR_EXE) $(HASHMAP_EXE)

clean:
	rm -f $(REGEX_EXE) $(GENERATOR_EXE) $(HASHMAP_EXE)

$(REGEX_EXE): $(REGEX_SRC)
	$(CC) $< -o $@

$(GENERATOR_EXE): $(GENERATOR_SRC)
	$(CC) $< -o $@

$(HASHMAP_EXE): $(HASHMAP_SRC)
	$(CC) $(CC_FLAGS) $< -o $@
