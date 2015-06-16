#pragma once

#include <libbr/config.hpp>

namespace BR {

struct Any {
	template< typename T >
	Any(T const &);
};

struct AnyPointer {
	template< typename T >
	AnyPointer(T const *) { }
};

} // namespace BR


