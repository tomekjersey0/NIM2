# Define compiler and flags
CXX := g++
CXXFLAGS := -Iinclude -Ienums
LDFLAGS := -lpdcurses
DEB_LDFLAGS := -Lbin/Debug
REL_LDFLAGS := -Llib

# Define source files and output directories
SRC := $(wildcard src/*.cpp)
OBJ_DEBUG := $(patsubst src/%.cpp, obj/Debug/%.o, $(SRC))
OBJ_RELEASE := $(patsubst src/%.cpp, obj/Release/%.o, $(SRC))
DEBUG_DIR := bin/Debug
RELEASE_DIR := bin/Release
OBJ_DIR_DEBUG := obj/Debug
OBJ_DIR_RELEASE := obj/Release

# Ensure shell knows what g++ is
pre:
	@if [ -z "$$(which g++ 2>/dev/null)" ]; then \
		echo "g++ is not in your PATH. Add this to your ~/.bashrc:"; \
		echo 'export PATH=/c/MinGW/bin:$$PATH'; \
		echo 'You may have to restart your terminal.'; \
		exit 1; \
	fi


# Define targets
all: clean build run

release: pre $(RELEASE_DIR)/NimGame

build: pre $(DEBUG_DIR)/NimGame

# Ensure obj directories exist
$(OBJ_DIR_DEBUG) $(OBJ_DIR_RELEASE):
	@mkdir -p $@

# Compile Debug Objects
$(OBJ_DIR_DEBUG)/%.o: src/%.cpp | $(OBJ_DIR_DEBUG)
#	@echo "Compiling $< into $@"
	$(CXX) $(CXXFLAGS) -g -O0 -DDEBUG -c $< -o $@

# Compile Release Objects
$(OBJ_DIR_RELEASE)/%.o: src/%.cpp | $(OBJ_DIR_RELEASE)
#	@echo "Compiling $< into $@"
	$(CXX) $(CXXFLAGS) -O2 -DNDEBUG -c $< -o $@

# Link Debug Executable
$(DEBUG_DIR)/NimGame: $(OBJ_DEBUG)
	@echo "Linking Debug Executable"
	$(CXX) $^ -o $@ $(LDFLAGS) $(DEB_LDFLAGS)

# Link Release Executable (Static)
$(RELEASE_DIR)/NimGame: $(OBJ_RELEASE)
	@echo "Linking Release Executable"
	$(CXX) $^ -o $@ $(LDFLAGS) $(REL_LDFLAGS) -static -static-libstdc++ -static-libgcc

# Run Debug
run: $(DEBUG_DIR)/NimGame
	@echo "Running Debug version"
	./$(DEBUG_DIR)/NimGame

# Clean
clean:
	@echo "Cleaning up"
	@rm -rf $(OBJ_DIR_DEBUG)/*.o $(OBJ_DIR_RELEASE)/*.o $(DEBUG_DIR)/NimGame $(RELEASE_DIR)/NimGame
