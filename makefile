CC = gcc
CFLAGS = -std=c17 -Wall -Wfatal-errors -pedantic -g -g3
PFLAGS = include
LFLAGS = -lMLV -lm

EXEC = GemCraft

# ------------- Paths -------------

SRC = src/
BIN = bin/
INCLUDES = $(BIN)display $(BIN)game_engine $(BIN)user_event $(BIN)utils

# ----------- Files to compile -----------


SRC_FILES = $(wildcard $(SRC)*/*.c) $(SRC)main.c
OBJ_FILES = $(patsubst $(SRC)%.c, $(BIN)%.o, $(SRC_FILES))

# Generic rule

$(EXEC) : $(OBJ_FILES)
	$(CC) $^ -o $@ $(LFLAGS)  -g -g3

$(BIN)%.o : $(SRC)%.c
	@mkdir --parents $(INCLUDES)
	$(CC) $(CFLAGS) -I./$(PFLAGS) -c $< -o $@

# Cleaning

clean : 
	rm -fr $(BIN)*

mrproper: clean
	rm -fr $(EXEC)
