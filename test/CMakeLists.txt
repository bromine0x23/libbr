cmake_minimum_required(VERSION 3.1)

enable_testing()

find_package(GTest REQUIRED)

file(GLOB_RECURSE BR_TEST_SOURCES ./*.cpp)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(br_test ${LIBBR_HEADERS} ${BR_TEST_SOURCES})

target_link_libraries(br_test br ${GTEST_BOTH_LIBRARIES})

add_test(Test br_test)