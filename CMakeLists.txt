cmake_minimum_required(VERSION 3.15)
project(CineSeat VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
)

# Executable target
add_executable(cineseat ${SOURCES})

# Target properties
set_target_properties(cineseat PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
