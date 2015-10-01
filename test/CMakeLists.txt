cmake_minimum_required(VERSION 3.1)

enable_testing()

add_executable(br_test ${LIBBR_SOURCES} ${LIBBR_HEADERS} test.cpp)

# target_link_libraries(test_config br)

add_test(Test br_test)