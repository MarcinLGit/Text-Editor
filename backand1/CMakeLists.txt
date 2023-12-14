cmake_minimum_required(VERSION 3.10)
project(Backand)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(Backand hash_calculator.cpp)
target_include_directories(MyTests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(MyTests ${Boost_LIBRARIES})


set(SOURCES 
    hash_calculator.cpp
    test.cpp
)

# Dodaj plik nagłówkowy
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Dodaj testowy plik wykonywalny
add_executable(TestMyProject ${SOURCES})

# Linkuj bibliotekę Boost.Test
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
target_include_directories(TestMyProject PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(TestMyProject PRIVATE ${Boost_LIBRARIES})
