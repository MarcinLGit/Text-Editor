cmake_minimum_required(VERSION 3.10)

project(MyProgram)

set(CMAKE_CXX_STANDARD 11)

# Add your source files
set(SOURCES
    logic.cpp
    hash_calculator.cpp
    test.cpp
)

add_executable(my_program ${SOURCES})

target_link_libraries(my_program
    PUBLIC
    ssl
    crypto
    pthread
)