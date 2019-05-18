cmake_minimum_required(VERSION 3.12)

if (LIBBR_BUILD_TESTS)
	enable_testing()

	find_package(GTest REQUIRED)
	find_package(Threads REQUIRED)

	include_directories(${GTEST_INCLUDE_DIR})
	include_directories(support)

	file(GLOB_RECURSE LIBBR_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
	file(GLOB LIBBR_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/support/*)

	add_executable(libbr-test ${LIBBR_HEADERS} ${LIBBR_TESTS} ${LIBBR_TEST_HEADERS})

	target_compile_options(libbr-test PRIVATE ${LIBBR_COMPILE_FLAGS})
	target_link_options(libbr-test PRIVATE ${LIBBR_LINK_FLAGS})

	if (LIBBR_ENABLE_STATIC)
		target_link_libraries(libbr-test libbr-static ${GTEST_BOTH_LIBRARIES})
	else ()
		target_link_libraries(libbr-test libbr        ${GTEST_BOTH_LIBRARIES})
	endif ()

	if (NOT MSVC)
		target_link_libraries(libbr-test pthread)
	endif ()

	add_test(Test libbr-test)
endif ()