CC = gcc -I src
LIB := $(shell cd src && ls *.c)

all: $(LIB:.c=) main.out
	@

main.out:
	@$(CC) $(shell ls bin/*.o) -o $@

%:
	@$(CC) -c src/$@.c -o bin/$@.o
