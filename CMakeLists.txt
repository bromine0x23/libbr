cmake_minimum_required(VERSION 3.0)

project(LIBBR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fabi-version=0 -march=corei7")

set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wall -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(libbr)

enable_testing()

add_executable(test_config ${SOURCE_FILES} test/test_config.cpp)

target_link_libraries(test_config br)

add_test(Test test_config)