cmake_minimum_required(VERSION 3.10)

# Project name and version
project(NIM2 VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Automatically gather all source and header files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h" "enums/*.h")

# Add include directories
include_directories(include enums src)

# Add the executable
add_executable(NIM2 ${SOURCES} ${HEADERS})

# Ensure the toolchain file is set
if(NOT CMAKE_TOOLCHAIN_FILE)
    message(WARNING "CMAKE_TOOLCHAIN_FILE is not set. Make sure to set it globally or pass it during configuration.")
endif()

# Find and link platform-specific libraries
if(WIN32)
    # Use vcpkg-provided target for PDCurses (unofficial-pdcurses for MinGW)
    find_package(unofficial-pdcurses CONFIG REQUIRED)
    target_link_libraries(NIM2 PRIVATE unofficial::pdcurses::pdcurses)
elseif(UNIX)
    # Use ncurses on Linux
    find_package(Curses REQUIRED)
    target_link_libraries(NIM2 PRIVATE ${CURSES_LIBRARIES})
endif()