#if defined(NDEBUG)

#else

#include <libbr/assert/assert.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

namespace {

[[noreturn]] inline void libbr_assert_base(BR::NChar const * format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	abort();
}

} // namespace [anonymous]

void libbr_assert(
	BR::NChar const * assertion,
	BR::NChar const * file,
	BR::Size line,
	BR::NChar const * function,
	BR::NChar const * message
) {
	libbr_assert_base("%s:%u: %s:\n\tAssertion `%s` failed. %s\n", file, line, function, assertion, message);
}

#endif // defined
