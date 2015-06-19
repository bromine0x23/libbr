cmake_minimum_required(VERSION 3.1)
project(LIBBR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -W")

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(libbr)

enable_testing()

add_executable(test_config ${SOURCE_FILES} test/test_config.cpp)

target_link_libraries(test_config br)

add_test(Test test_config)