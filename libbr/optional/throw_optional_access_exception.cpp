/**
 * @file
 * @author Bromine0x23
 * @since 2015/11/14
 */
#include <libbr/optional/optional_access_exception.hpp>
#include <libbr/optional/throw_optional_access_exception.hpp>

namespace BR {

[[noreturn]] void throw_optional_access_exception() {
	throw OptionalAccessException();
}

}