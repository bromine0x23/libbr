#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include <libbr/assert/assert.hpp>

#if defined(NDEBUG)

#else

namespace BR {

namespace {

[[noreturn]] static void assert_base(char const * format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	abort();
}

} // namespace [anonymous]

void __assert__(
	char const * assertion,
	char const * file,
	Size line,
	char const * function
) {
	assert_base("%s:%u: %s:\n\tAssertion `%s' failed.\n", file, line, function, assertion);
}

} // namespace BR

#endif // defined
