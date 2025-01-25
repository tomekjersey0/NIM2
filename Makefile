all: build run

build:
	g++ -Iinclude -Ienums src/*.cpp -o main -lpdcurses
run:
	./main