cmake_minimum_required(VERSION 3.5)

set(LIBBR_SOURCES "")
set(LIBBR_HEADERS "")

file(GLOB LIBBR_SOURCES_ ./*.cpp)

list(APPEND LIBBR_SOURCES ${LIBBR_SOURCES_})

if (MSVC_IDE OR XCODE)
	file(GLOB LIBBR_HEADERS_ ./*.hpp)
	list(APPEND LIBBR_HEADERS ${LIBBR_HEADERS_})
endif()

if (MSVC_IDE)
	source_group("Source Files" FILES ${LIBBR_SOURCES_})
	source_group("Header Files" FILES ${LIBBR_HEADERS_})
endif()

set(LIBBR_COMPONENTS
	config
	algorithm
	assert
	container
	encoding
	enumerate
	exception
	functional
	iterator
	math
	memory
	optional
	random
	string
	type_operate
	type_traits
	utility
)

foreach(component ${LIBBR_COMPONENTS})
	file(GLOB LIBBR_SOURCES_${component} ${component}/*.cpp)
	list(APPEND LIBBR_SOURCES ${LIBBR_SOURCES_${component}})

	if (MSVC_IDE OR XCODE)
		file(GLOB LIBBR_HEADERS_${component} ${component}/*.hpp)
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