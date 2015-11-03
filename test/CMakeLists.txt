cmake_minimum_required(VERSION 3.1)

enable_testing()

file(GLOB_RECURSE BR_TEST_SOURCES ./*.cpp)

add_executable(br_test ${LIBBR_HEADERS} ${BR_TEST_SOURCES})

target_link_libraries(br_test br)

add_test(Test br_test)