cmake_minimum_required(VERSION 3.12)


set(
	LIBBR_COMPONENTS
	algorithms
	assert
	exceptions
	functional
	iterators
	math
	memory
	type_traits
	type_transform
	utility
)

set(LIBBR_SOURCES "")
set(LIBBR_HEADERS "")


file(GLOB LIBBR_SOURCES_ ./*.cpp)
list(APPEND LIBBR_SOURCES ${LIBBR_SOURCES_})
if (LIBBR_CONFIGURE_IDE)
	file(GLOB LIBBR_HEADERS_ ./*.hpp)
	list(APPEND LIBBR_HEADERS ${LIBBR_HEADERS_})
	if (MSVC_IDE)
		source_group("Source Files" FILES ${LIBBR_SOURCES_})
		source_group("Header Files" FILES ${LIBBR_HEADERS_})
	endif ()
endif ()

foreach (component ${LIBBR_COMPONENTS})
	file(GLOB LIBBR_SOURCES_${component} ${component}/*.cpp)
	list(APPEND LIBBR_SOURCES ${LIBBR_SOURCES_${component}})
	if (LIBBR_CONFIGURE_IDE)
		file(GLOB_RECURSE LIBBR_HEADERS_${component} ${component}/*.hpp)
		list(APPEND LIBBR_HEADERS ${LIBBR_HEADERS_${component}})
		if (MSVC_IDE)
			source_group("Source Files\\${component}" FILES ${LIBBR_SOURCES_${component}})
			source_group("Header Files\\${component}" FILES ${LIBBR_HEADERS_${component}})
		endif ()
	endif ()
endforeach ()

if (NOT WIN32)
	add_flags_if_supported(-fPIC)
endif ()


if (LIBBR_ENABLE_SHARED)
	add_library(libbr SHARED ${LIBBR_SOURCES})
	set_target_properties(
		libbr
		PROPERTIES
		VERSION "${LIBBR_VERSION}.0"
		SOVERSION "${LIBBR_VERSION}"
		OUTPUT_NAME "br"
	)
	target_compile_options(libbr PRIVATE ${LIBBR_COMPILE_FLAGS})
	target_compile_definitions(libbr PRIVATE LIBBR_EXPORTS)
	target_link_options(libbr PRIVATE ${LIBBR_LINK_FLAGS})
	target_include_directories(libbr INTERFACE "$<INSTALL_INTERFACE:include/>")
	install(
		TARGETS libbr
		EXPORT LibbrTargets
		RUNTIME DESTINATION ${LIB_INSTALL_DIR}
		LIBRARY DESTINATION ${LIB_INSTALL_DIR}
		ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
endif ()
if (LIBBR_ENABLE_STATIC)
	add_library(libbr-static STATIC ${LIBBR_SOURCES})
	set_target_properties(
		libbr-static
		PROPERTIES
		OUTPUT_NAME "br"
	)
	target_compile_options(libbr-static PRIVATE ${LIBBR_COMPILE_FLAGS})
	target_compile_definitions(libbr-static PRIVATE LIBBR_STATIC)
	target_link_options(libbr-static PRIVATE ${LIBBR_LINK_FLAGS})
	target_include_directories(libbr-static INTERFACE "$<INSTALL_INTERFACE:include/>")
	install(
		TARGETS libbr-static
		EXPORT LibbrTargets
		ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
endif ()