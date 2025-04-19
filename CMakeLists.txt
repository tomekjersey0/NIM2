cmake_minimum_required(VERSION 3.10)

# Project name and version
project(NIM2 VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Automatically gather all source and header files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h" "enums/*.h")

# Include directories
include_directories(include enums)

# Add the executable
add_executable(NIM2 ${SOURCES} ${HEADERS})

# Link platform-specific libraries
if(WIN32)
    target_link_libraries(NIM2 PDCurses) # Use PDCurses on Windows
elseif(UNIX)
    target_link_libraries(NIM2 ncurses) # Use ncurses on Linux
endif()