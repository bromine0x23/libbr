cmake_minimum_required(VERSION 3.1)

set(LIBBR_SOURCES "")
set(LIBBR_HEADERS "")

file(GLOB LIBBR_SOURCES_ ./*.cpp)

if (MSVC_IDE OR XCODE)
	file(GLOB LIBBR_HEADERS_       ./*.hpp)
	file(GLOB LIBBR_HEADERS_CONFIG config/*.hpp)
	if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
		list(APPEND LIBBR_HEADERS_CONFIG config/compiler/intel.hpp)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		list(APPEND LIBBR_HEADERS_CONFIG config/compiler/msvc.hpp)
	endif()
	if(WIN32)
		list(APPEND LIBBR_HEADERS_CONFIG config/platform/win32.hpp)
	endif()
endif()

list(APPEND LIBBR_SOURCES ${LIBBR_SOURCES_})
list(APPEND LIBBR_HEADERS ${LIBBR_HEADERS_})
list(APPEND LIBBR_HEADERS ${LIBBR_HEADERS_CONFIG})

if (MSVC_IDE)
	source_group("Source Files"         FILES ${LIBBR_SOURCES_})
	source_group("Header Files"         FILES ${LIBBR_HEADERS_})
	source_group("Header Files\\config" FILES ${LIBBR_HEADERS_CONFIG})
endif()

set(LIBBR_COMPONENTS assert container exception iterator math memory type_operate type_traits utility)

foreach(component ${LIBBR_COMPONENTS})

	file(GLOB_RECURSE LIBBR_SOURCES_${component} ${component}/*.cpp)
	list(APPEND LIBBR_SOURCES ${LIBBR_SOURCES_${component}})

	if (MSVC_IDE OR XCODE)
		file(GLOB_RECURSE LIBBR_HEADERS_${component} ${component}/*.hpp)
		list(APPEND LIBBR_HEADERS ${LIBBR_HEADERS_${component}})
	endif()

	if (MSVC_IDE)
		source_group("Source Files\\${component}" FILES ${LIBBR_SOURCES_${component}})
		source_group("Header Files\\${component}" FILES ${LIBBR_HEADERS_${component}})
	endif()
endforeach(component)

if (LIBBR_ENABLE_SHARED)
	add_library(br SHARED ${LIBBR_SOURCES} ${LIBBR_HEADERS})
else()
	add_library(br STATIC ${LIBBR_SOURCES} ${LIBBR_HEADERS})
endif()