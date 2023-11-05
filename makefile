CC = gcc
CFLAGS = -std=c17 -Wall -Wfatal-errors -pedantic
PFLAGS = include
LFLAGS = -lMLV -lm

EXEC = GemCraft

# ------------- Paths -------------

SRC = src/
BIN = bin/

# ----------- Files to compile -----------

SRC_FILES = $(wildcard $(SRC)*.c)
OBJ_FILES = $(patsubst $(SRC)%.c, $(BIN)%.o, $(SRC_FILES))

# Generic rule

$(EXEC) : $(OBJ_FILES)
	$(CC) $^ -o $@ $(LFLAGS)

$(BIN)%.o : $(SRC)%.c
	$(CC) $(CFLAGS) -I./$(PFLAGS) -c $< -o $@

# Cleaning

clean : 
	rm -f $(BIN)*

mrproper: clean
	rm -f $(EXEC)
