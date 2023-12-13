cmake_minimum_required(VERSION 3.10)
project(MyProject)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(MyTests test.cpp)
target_include_directories(MyTests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(MyTests ${Boost_LIBRARIES})
