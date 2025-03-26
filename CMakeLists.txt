# Minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name and version
project(NIM2 VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(NIM2 ${SOURCES})

# Include directories
target_include_directories(NIM2 PRIVATE "include/" "enums/")

# Link libraries based on platform
if(WIN32)
    target_link_libraries(NIM2 PRIVATE pdcurses)
else()
    target_link_libraries(NIM2 PRIVATE ncurses)
endif()