cmake_minimum_required(VERSION 3.15)
project(CineSeat VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Source files
set(SOURCES
    src/main.cpp
    src/database.cpp
)

# Executable target
add_executable(cineseat ${SOURCES})

target_link_libraries(cineseat PRIVATE libmysql)

# Target properties
set_target_properties(cineseat PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
