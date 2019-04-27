include(CheckCXXCompilerFlag)

set(LIBBR_COMPILE_FLAGS "")
set(LIBBR_LINK_FLAGS "")

# Mangle the name of a compiler flag into a valid CMake identifier.
# Ex: --std=c++11 -> STD_EQ_CXX11
macro(mangle_name str output)
	string(STRIP "${str}" strippedStr)
	string(REGEX REPLACE "^/" "" strippedStr "${strippedStr}")
	string(REGEX REPLACE "^-+" "" strippedStr "${strippedStr}")
	string(REGEX REPLACE "-+$" "" strippedStr "${strippedStr}")
	string(REPLACE "-" "_" strippedStr "${strippedStr}")
	string(REPLACE "=" "_EQ_" strippedStr "${strippedStr}")
	string(REPLACE "+" "X" strippedStr "${strippedStr}")
	string(TOUPPER "${strippedStr}" ${output})
endmacro()

# Add a list of flags to all of 'CMAKE_CXX_FLAGS', 'CMAKE_C_FLAGS',
# 'LIBBR_COMPILE_FLAGS' and 'LIBBR_LINK_FLAGS'.
macro(add_target_flags)
	foreach(value ${ARGN})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${value}")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${value}")
		list(APPEND LIBBR_COMPILE_FLAGS ${value})
		list(APPEND LIBBR_LINK_FLAGS ${value})
	endforeach()
endmacro()

# If the specified 'condition' is true then add a list of flags to
# all of 'CMAKE_CXX_FLAGS', 'CMAKE_C_FLAGS', 'LIBBR_COMPILE_FLAGS'
# and 'LIBBR_LINK_FLAGS'.
macro(add_target_flags_if condition)
	if (${condition})
		add_target_flags(${ARGN})
	endif()
endmacro()

# Add a specified list of flags to both 'LIBBR_COMPILE_FLAGS' and
# 'LIBBR_LINK_FLAGS'.
macro(add_flags)
	foreach(value ${ARGN})
		list(APPEND LIBBR_COMPILE_FLAGS ${value})
		list(APPEND LIBBR_LINK_FLAGS ${value})
	endforeach()
endmacro()

# If the specified 'condition' is true then add a list of flags to both
# 'LIBBR_COMPILE_FLAGS' and 'LIBBR_LINK_FLAGS'.
macro(add_flags_if condition)
	if (${condition})
		add_flags(${ARGN})
	endif()
endmacro()

# Add each flag in the list to LIBBR_COMPILE_FLAGS and LIBBR_LINK_FLAGS
# if that flag is supported by the current compiler.
macro(add_flags_if_supported)
	foreach(flag ${ARGN})
		mangle_name("${flag}" flagname)
		check_cxx_compiler_flag("${flag}" "LIBBR_SUPPORTS_${flagname}_FLAG")
		add_flags_if(LIBBR_SUPPORTS_${flagname}_FLAG ${flag})
	endforeach()
endmacro()

# Add a list of flags to 'LIBBR_COMPILE_FLAGS'.
macro(add_compile_flags)
	foreach(f ${ARGN})
		list(APPEND LIBBR_COMPILE_FLAGS ${f})
	endforeach()
endmacro()

# If 'condition' is true then add the specified list of flags to
# 'LIBBR_COMPILE_FLAGS'
macro(add_compile_flags_if condition)
	if (${condition})
		add_compile_flags(${ARGN})
	endif()
endmacro()

# For each specified flag, add that flag to 'LIBBR_COMPILE_FLAGS' if the
# flag is supported by the C++ compiler.
macro(add_compile_flags_if_supported)
	foreach(flag ${ARGN})
		mangle_name("${flag}" flagname)
		check_cxx_compiler_flag("${flag}" "LIBBR_SUPPORTS_${flagname}_FLAG")
		add_compile_flags_if(LIBBR_SUPPORTS_${flagname}_FLAG ${flag})
	endforeach()
endmacro()

# Add a list of flags to 'LIBBR_LINK_FLAGS'.
macro(add_link_flags)
	foreach(f ${ARGN})
		list(APPEND LIBBR_LINK_FLAGS ${f})
	endforeach()
endmacro()

# If 'condition' is true then add the specified list of flags to
# 'LIBBR_LINK_FLAGS'
macro(add_link_flags_if condition)
	if (${condition})
		add_link_flags(${ARGN})
	endif()
endmacro()

# For each specified flag, add that flag to 'LIBBR_LINK_FLAGS' if the
# flag is supported by the C++ compiler.
macro(add_link_flags_if_supported)
	foreach(flag ${ARGN})
		mangle_name("${flag}" flagname)
		check_cxx_compiler_flag("${flag}" "LIBBR_SUPPORTS_${flagname}_FLAG")
		add_link_flags_if(LIBBR_SUPPORTS_${flagname}_FLAG ${flag})
	endforeach()
endmacro()