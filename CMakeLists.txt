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

# Find and link platform-specific libraries
if(WIN32)
    # Try to find PDCurses via vcpkg or custom paths
    find_path(PDCURSES_INCLUDE_DIR curses.h PATH_SUFFIXES pdcurses)
    find_library(PDCURSES_LIBRARY pdcurses)

    # If not found, allow the user to specify custom paths
    if(NOT PDCURSES_INCLUDE_DIR OR NOT PDCURSES_LIBRARY)
        message(WARNING "PDCurses not found! Please specify PDCURSES_INCLUDE_DIR and PDCURSES_LIBRARY manually.")
        set(PDCURSES_INCLUDE_DIR "" CACHE PATH "Path to PDCurses include directory")
        set(PDCURSES_LIBRARY "" CACHE FILEPATH "Path to PDCurses library")
    endif()

    # Add include directory and link library
    target_include_directories(NIM2 PRIVATE ${PDCURSES_INCLUDE_DIR})
    target_link_libraries(NIM2 PRIVATE ${PDCURSES_LIBRARY})
elseif(UNIX)
    # Try to find ncurses via vcpkg or system package manager
    find_package(Curses REQUIRED)

    # Add include directory and link library
    target_include_directories(NIM2 PRIVATE ${CURSES_INCLUDE_DIR})
    target_link_libraries(NIM2 PRIVATE ${CURSES_LIBRARIES})
endif()