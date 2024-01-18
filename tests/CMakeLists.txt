set(TEST_MAIN "MyTests")
set(TEST_SOURCES "test.cpp")
set(TEST_INCLUDES "./")

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(${TEST_MAIN} ${TEST_SOURCES})
target_include_directories(${TEST_MAIN} PUBLIC ${TEST_INCLUDES})
target_link_libraries(${TEST_MAIN} PUBLIC ${LIBRARY_NAME} ${Boost_LIBRARIES})

if(ENABLE_COVERAGE)
	set(COVERAGE_MAIN "coverage")
	set(COVERAGE_EXCLUDES
	    "${PROJECT_SOURCE_DIR}/cmake/*"
	    "${PROJECT_SOURCE_DIR}/docs/*"
	    "${PROJECT_SOURCE_DIR}/tests/*"
	    "${PROJECT_SOURCE_DIR}/build/*"
	    "/usr/include/*")
	setup_target_for_coverage_lcov(
	    NAME
	    ${COVERAGE_MAIN}
	    EXECUTABLE
	    ${TEST_MAIN}
	    DEPENDENCIES
	    ${TEST_MAIN})
endif()


