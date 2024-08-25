CC = gcc

all: build run 

build:
	$(CC) bf.c -o bf -Wall -Wextra
run:
	./bf tests.bf
