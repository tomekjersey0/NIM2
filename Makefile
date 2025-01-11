all: build run

build:
	g++ main.cpp -o main -lpdcurses
run:
	./main