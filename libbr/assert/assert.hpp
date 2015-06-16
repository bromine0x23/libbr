#pragma once

#include <libbr/config.hpp>

#if defined(NDEBUG)

#define BR_ASSERT(expr) static_cast<void>(0)

#else

namespace BR {

[[noreturn]] void __assert__(
	char const * assertion,
	char const * file,
	Size line,
	char const * func
);

} // namespace BR

#define BR_ASSERT(expr) \
	((expr) \
	? static_cast<void>(0) \
	: BR::__assert__(BR_STRINGIZE(expr), __FILE__, __LINE__, __func__)) \
// ASSERT

#endif // NDEBUG


