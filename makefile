CC = gcc
CFLAGS = -std=c17 -Wall -Wfatal-errors -pedantic
PFLAGS = include
LFLAGS = -lMLV -lm

EXEC = GemCraft

# ------------- Paths -------------

SRC = src/
BIN = bin/
DOC = doc/doxygen/
INCLUDES = $(BIN)display $(BIN)game_engine $(BIN)user_event $(BIN)utils

# ----------- Files to compile -----------


SRC_FILES = $(wildcard $(SRC)*/*.c) $(SRC)main.c
OBJ_FILES = $(patsubst $(SRC)%.c, $(BIN)%.o, $(SRC_FILES))

# Generic rule

$(EXEC) : $(OBJ_FILES)
	$(CC) $^ -o $@ $(LFLAGS)

$(BIN)%.o : $(SRC)%.c
	@mkdir --parents $(INCLUDES)
	$(CC) $(CFLAGS) -I./$(PFLAGS) -c $< -o $@

# Doxygen

doc: $(DOC)/doxygen

$(DOC)/doxygen: 
	@doxygen doxyfile

run: $(EXEC)
	@./$(EXEC)

# Cleaning

clean: 
	rm -fr $(BIN)*

mrproper: clean
	rm -fr $(EXEC)
