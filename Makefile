# Define compiler and flags
CXX := g++
CXXFLAGS := -Iinclude -Ienums

# Define source files and output directories
SRC := $(wildcard src/*.cpp)
DEBUG_DIR := bin/Debug
RELEASE_DIR := bin/Release

# Define targets
all: clean build run

release: $(RELEASE_DIR)/NimGame

build: $(DEBUG_DIR)/main

$(RELEASE_DIR)/NimGame: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ -Llib -lpdcurses -static

$(DEBUG_DIR)/main: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ -Lbin -lpdcurses

run: $(DEBUG_DIR)/main
	./$(DEBUG_DIR)/main

clean:
	rm -rf $(DEBUG_DIR)/* $(RELEASE_DIR)/*