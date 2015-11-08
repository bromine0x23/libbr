cmake_minimum_required(VERSION 3.1)

# set(CMAKE_VERBOSE_MAKEFILE true)

find_package(Doxygen)

#===============================================================================
# Setup Project
#===============================================================================

project(LIBBR CXX)

set(PACKAGE_NAME libbr)

set(PACKAGE_VERSION trunk-git)

set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")

#===============================================================================
# Setup CMake Options
#===============================================================================

option(LIBBR_ENABLE_CXX14 "Use c++14 language features if the compiler supports it." OFF)
option(LIBBR_ENABLE_SHARED "Build libbr as a shared library." OFF)
option(LIBBR_BUILD_32_BITS "Build 32 bit libbr" OFF)
option(LIBBR_GENERATE_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

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
	if (LIBBR_ENABLE_CXX14)
		set(LIBBR_STD_VERSION c++14)
	else()
		set(LIBBR_STD_VERSION c++11)
	endif()
	list(APPEND LIBBR_CXX_FLAGS "-std=${LIBBR_STD_VERSION}")
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

if(LIBBR_GENERATE_DOCUMENTATION)
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