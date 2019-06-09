cmake_minimum_required(VERSION 3.12)

if (LIBBR_BUILD_TESTS)
	enable_testing()

	find_package(GTest REQUIRED)
	find_package(Threads REQUIRED)

	include_directories(${GTEST_INCLUDE_DIR})

	set(
		LIBBR_COMPONENT_TESTS
		algorithms
		containers
		functional
		iterators
		math
		memory
		operators
		strings
		type_traits
		type_transform
		utility
	)

	set(LIBBR_TEST_SOURCES "")
	foreach (component ${LIBBR_COMPONENT_TESTS})
		string(TOUPPER ${component} COMPONENT)

		option(LIBBR_ENABLE_TEST_${COMPONENT} "Build tests for component `${component}`" ON)

		if (LIBBR_ENABLE_TEST_${COMPONENT})
			file(GLOB LIBBR_TEST_SOURCES_${COMPONENT} ${component}/*.cpp)
			list(APPEND LIBBR_TEST_SOURCES ${LIBBR_TEST_SOURCES_${COMPONENT}})
		endif()
	endforeach ()

	add_executable(libbr-test test.cpp ${LIBBR_TEST_SOURCES})

	target_compile_options(libbr-test PRIVATE ${LIBBR_COMPILE_FLAGS})
	target_link_options(libbr-test PRIVATE ${LIBBR_LINK_FLAGS}  -s)

	if (LIBBR_ENABLE_STATIC)
		target_link_libraries(libbr-test libbr-static)
	else ()
		target_link_libraries(libbr-test libbr)
	endif ()

	target_link_libraries(libbr-test ${GTEST_LIBRARY})

	if (NOT MSVC)
		target_link_libraries(libbr-test pthread)
	endif ()

	add_test(Test libbr-test)
endif ()