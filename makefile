program=webbox2

default: main.c
	gcc -s main.c -o $(program) -static

shared: main.c
	gcc main.c -o $(program)