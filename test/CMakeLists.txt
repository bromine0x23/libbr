cmake_minimum_required(VERSION 3.12)

if (LIBBR_BUILD_TESTS)
	enable_testing()

	find_package(GTest REQUIRED)
	find_package(Threads REQUIRED)

	include_directories(support)

	file(GLOB_RECURSE LIBBR_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
	file(GLOB LIBBR_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/support/*)

	add_executable(libbr-test ${LIBBR_HEADERS} ${LIBBR_TESTS} ${LIBBR_TEST_HEADERS})

	if (LIBBR_ENABLE_STATIC)
		target_link_libraries(libbr-test libbr-static ${GTEST_BOTH_LIBRARIES} pthread)
	else ()
		target_link_libraries(libbr-test libbr        ${GTEST_BOTH_LIBRARIES} pthread)
	endif ()

	add_test(Test libbr-test)
endif ()