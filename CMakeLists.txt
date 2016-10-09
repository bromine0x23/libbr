cmake_minimum_required(VERSION 3.5)

# set(CMAKE_VERBOSE_MAKEFILE true)

#===============================================================================
# Setup Project
#===============================================================================
project(LIBBR LANGUAGES CXX)

set(PACKAGE_NAME libbr)

set(PACKAGE_VERSION trunk-git)

set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")

#===============================================================================
# Setup CMake Options
#===============================================================================
option(LIBBR_ENABLE_CXX14 "Use c++14 language features if the compiler supports it." ON)
option(LIBBR_ENABLE_SHARED "Build libbr as a shared library." OFF)
option(LIBBR_BUILD_32_BITS "Build 32 bit libbr" OFF)
option(LIBBR_INCLUDE_DOCUMENTATION "Build the HTML based API documentation (requires Doxygen)" OFF)
option(LIBBR_INCLUDE_TESTS "Build the tests (requires gtest)." ON)

#===============================================================================
# Configure System
#===============================================================================
set(LIBBR_CXX_FLAGS "")

#===============================================================================
# Setup Compiler Flags
#===============================================================================
if (MSVC)
	add_definitions(/wd4819)
else()
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)

	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	if (COMPILER_SUPPORTS_CXX14 AND LIBBR_ENABLE_CXX14)
		set(CMAKE_CXX_STANDARD 14)
	else()
		set(CMAKE_CXX_STANDARD 11)
	endif()
endif()

if (LIBBR_ENABLE_SHARED)
	add_definitions(-DBR_BUILD_SHARED)
else()
	add_definitions(-DBR_BUILD_STATIC)
endif()

if (LIBBR_BUILD_32_BITS)
	if (CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT WIN32)
		message(STATUS "Building 32 bits executables and libraries.")
		list(APPEND LIBBR_CXX_FLAGS "-m32")
	else()
		message(FATAL_ERROR "LIBBR_BUILD_32_BITS=ON is not supported on this platform.")
	endif()
endif()

string(REPLACE ";" " " LIBBR_CXX_FLAGS "${LIBBR_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIBBR_CXX_FLAGS}")

#===============================================================================
# Setup Source Code
#===============================================================================
include_directories(${PROJECT_SOURCE_DIR}/libbr/..)

add_subdirectory(libbr)

#===============================================================================
# Setup Tests
#===============================================================================

add_subdirectory(test)

#===============================================================================
# Setup Doxygen Target
#===============================================================================

if(LIBBR_INCLUDE_DOCUMENTATION)
	find_package(Doxygen)

	if(NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen is needed to build the documentation.")
	endif()

	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE} "${PROJECT_SOURCE_DIR}/Doxyfile"
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM
		USES_TERMINAL
	)
endif()