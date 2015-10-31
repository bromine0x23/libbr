#pragma once

#include <libbr/config.hpp>

#if defined(NDEBUG)

#define BR_ASSERT(expr) ((void)0)

#else

namespace BR {

[[noreturn]] void __assert__(
	char const * assertion,
	char const * file,
	Size line,
	char const * func
);

} // namespace BR

#define BR_ASSERT(expr) ((expr) ? (void)0 : BR::__assert__(BR_STRINGIFY(expr), __FILE__, __LINE__, __func__))

#endif // NDEBUG


