cmake_minimum_required(VERSION 2.8.7)

if(LIBBR_INCLUDE_TESTS)
	enable_testing()

	find_package(GTest REQUIRED)

	file(GLOB_RECURSE BR_TEST_SOURCES ./*.cpp)

	include_directories(${GTEST_INCLUDE_DIRS})

	add_executable(br_test ${LIBBR_HEADERS} ${BR_TEST_SOURCES})

	target_link_libraries(br_test br ${GTEST_BOTH_LIBRARIES})

	add_definitions(-DBR_SKIP_TYPE_OPERATE_TEST)
	add_definitions(-DBR_SKIP_TYPE_TRAITS_TEST)

	add_test(Test br_test)
endif()