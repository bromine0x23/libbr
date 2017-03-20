#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include <libbr/assert/assert.hpp>

#if defined(NDEBUG)

#else

namespace {

[[noreturn]] static inline void libbr_assert_base(BR::CString<BR::NChar>  format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	abort();
}

} // namespace [anonymous]

void libbr_assert(
	BR::CString<BR::NChar>  assertion,
	BR::CString<BR::NChar>  file,
	BR::Size line,
	BR::CString<BR::NChar>  function
) {
	libbr_assert_base("%s:%u: %s:\n\tAssertion `%s' failed.\n", file, line, function, assertion);
}

#endif // defined
