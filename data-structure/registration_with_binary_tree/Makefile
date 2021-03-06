.PHONY: main.out

SRC = src/c
BIN = bin
CC := gcc -I $(SRC)
LIB := $(shell ls $(SRC)/*.c | xargs -n 1 basename)

all: $(LIB:.c=) main.out
	@

main.out:
	@$(CC) $(shell ls $(BIN)/*.o) -o $@

%:
	@$(CC) -c $(SRC)/$@.c -o $(BIN)/$@.o