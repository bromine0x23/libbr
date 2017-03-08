#include <libbr/container.hpp>
#include <libbr/container/detail/throw_optional_access_exception.hpp>
#include <libbr/assert/assert.hpp>

namespace BR {

inline namespace Container {

OptionalAccessException::~OptionalAccessException() noexcept {
}

} // namespace Container

namespace Detail {
namespace Container {

void throw_optional_access_exception() {
#if defined(BR_NO_EXCEPTIONS)
	assert(!"throw_optional_access_exception");
#else
	throw OptionalAccessException();
#endif
}

} // namespace Container
} // namespace Detail

} // namespace BR