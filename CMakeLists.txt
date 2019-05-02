cmake_minimum_required(VERSION 3.12)
project(
	libbr
	DESCRIPTION "A terrible C++ library with ugly code and useless features."
	VERSION 0.0.1
	LANGUAGES C CXX
)

#===============================================================================
# CMake
#===============================================================================
set(
	CMAKE_MODULE_PATH
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake"
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules"
	${CMAKE_MODULE_PATH}
)

#===============================================================================
# Options
#===============================================================================
include(CMakeDependentOption)

option(LIBBR_ENABLE_SHARED "Build libbr as a shared library." ON)
option(LIBBR_ENABLE_STATIC "Build libbr as a static library." ON)
option(LIBBR_BUILD_TESTS "Build the tests (requires gtest)." ON)
option(LIBBR_BUILD_DOCUMENTATION "Build the libbr documentation." OFF)
option(LIBBR_BUILD_32_BITS "Build 32 bit libbr." OFF)
set(LIBBR_CXX_STANDARD 14 CACHE STRING "C++ standard version expected to compile libbr.")

set(LIBBR_CONFIGURE_IDE_DEFAULT OFF)
if (XCODE OR MSVC_IDE)
	set(LIBBR_CONFIGURE_IDE_DEFAULT ON)
endif()
option(LIBBR_CONFIGURE_IDE "Configure libcxx for use within an IDE" ${LIBBR_CONFIGURE_IDE_DEFAULT})

if (NOT LIBBR_ENABLE_SHARED AND NOT LIBBR_ENABLE_STATIC)
	message(FATAL_ERROR "libbr must be built as either a shared or static library.")
endif ()

if (CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT WIN32)
	if (LIBBR_BUILD_32_BITS)
		message(STATUS "Building 32 bits executables and libraries.")
	endif ()
elseif (LIBBR_BUILD_32_BITS)
	message(FATAL_ERROR "LIBBR_BUILD_32_BITS=ON is not supported on this platform.")
endif ()

#===============================================================================
# libdir
#===============================================================================
if (NOT DEFINED LIB_INSTALL_DIR)
	set(LIB_INSTALL_DIR lib)
endif()

#===============================================================================
# Compiler Flags
#===============================================================================
include(LibbrFlags)

if (LIBBR_CXX_STANDARD LESS 11)
	message(FATAL_ERROR "C++14 or greater is required.")
endif()
if (NOT MSVC)
	check_cxx_compiler_flag("-std=c++${LIBBR_CXX_STANDARD}" "LIBBR_SUPPORTS_STD_EQ_CXX${LIBBR_CXX_STANDARD}_FLAG")
	if (NOT LIBBR_SUPPORTS_STD_EQ_CXX${LIBBR_CXX_STANDARD}_FLAG)
		message(FATAL_ERROR "Unsupported C++ standard version: ${LIBBR_CXX_STANDARD}")
	endif()
	set(CMAKE_CXX_STANDARD ${LIBBR_CXX_STANDARD})
endif()

add_target_flags_if(LIBBR_BUILD_32_BITS "-m32")

#===============================================================================
# Main
#===============================================================================
include_directories(libbr/..)
add_subdirectory(libbr)

#===============================================================================
# Tests
#===============================================================================
add_subdirectory(test)

#===============================================================================
# Setup Doxygen Target
#===============================================================================

if(LIBBR_BUILD_DOCUMENTATION)
	find_package(Doxygen)

	if(NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen is needed to build the documentation.")
	endif()

	add_custom_target(document
		COMMAND ${DOXYGEN_EXECUTABLE} "${PROJECT_SOURCE_DIR}/Doxyfile"
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM
		USES_TERMINAL
		)
endif()