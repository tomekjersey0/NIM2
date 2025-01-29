# Define compiler and flags
CXX := g++
CXXFLAGS := -Iinclude -Ienums

# Define source files and output directories
SRC := $(wildcard src/*.cpp)
DEBUG_DIR := bin/Debug
RELEASE_DIR := bin/Release

# Define targets
all: build run

release: $(RELEASE_DIR)/main

build: $(DEBUG_DIR)/main

$(RELEASE_DIR)/main: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ lib/libpdcurses.a -static

$(DEBUG_DIR)/main: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ bin/pdcurses.dll

run: $(DEBUG_DIR)/main
	./$(DEBUG_DIR)/main

clean:
	rm -rf $(DEBUG_DIR)/* $(RELEASE_DIR)/*