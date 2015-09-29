cmake_minimum_required(VERSION 3.1)

project(LIBBR)

set_property(GLOBAL PROPERTY CXX_STANDARD 14)

set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY CXX_STANDARD 11)

add_definitions(-std=c++11)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(libbr)

enable_testing()

add_executable(test_config ${SOURCE_FILES} test/test_config.cpp)

# target_link_libraries(test_config br)

add_test(Test test_config)