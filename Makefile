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

build: $(DEBUG_DIR)/NimGame

$(RELEASE_DIR)/NimGame: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ -Llib -lpdcurses -static -static-libstdc++ -static-libgcc

$(DEBUG_DIR)/NimGame: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ -Llib -lpdcurses

run: $(DEBUG_DIR)/NimGame
	./$(DEBUG_DIR)/NimGame

clean:
	rm -rf $(DEBUG_DIR)/* $(RELEASE_DIR)/*