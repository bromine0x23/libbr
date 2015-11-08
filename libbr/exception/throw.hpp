/**
 * @file
 * @brief throw functions
 * @author Bromine0x23
 * @since 2015/11/6
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

[[noreturn]] void throw_runtime_exception(CString<NChar> message);

[[noreturn]] void throw_logic_exception(CString<NChar> message);

[[noreturn]] void throw_argument_exception(CString<NChar> message);

[[noreturn]] void throw_domain_exception(CString<NChar> message);

[[noreturn]] void throw_index_exception(CString<NChar> message);

[[noreturn]] void throw_length_exception(CString<NChar> message);

}