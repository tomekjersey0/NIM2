all: build run

build:
	g++ -Iinclude src/*.cpp -o main -lpdcurses
run:
	./main