set(TEST_MAIN "MyTests")
set(TEST_SOURCES "test.cpp")
set(TEST_INCLUDES "./")

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(${TEST_MAIN} ${TEST_SOURCES})
target_include_directories(${TEST_MAIN} PUBLIC ${TEST_INCLUDES})
target_link_libraries(${TEST_MAIN} PUBLIC ${LIBRARY_NAME} ${Boost_LIBRARIES})
