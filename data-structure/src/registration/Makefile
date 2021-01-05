
#####################
# Makefile para projeto Cadastro
##
all: cad criaind
cad : cad.o util.o
	gcc -o cad cad.o util.o
criaind : criaind.o util.o
	gcc -o criaind criaind.o util.o

cad.o : cad.c cadastro.h
	gcc cad.c -c -g
criaind.o : criaind.c cadastro.h
	gcc criaind.c -c -g
util.o : util.c cadastro.h 
	gcc util.c -c -g