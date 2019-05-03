#include <libbr/assert/assert.hpp>
#include <libbr/exceptions/stl.hpp>
#include <libbr/exceptions/exception.hpp>

namespace BR {

inline namespace Exceptions {

Exception::~Exception() noexcept {
}

Exception::Message Exception::what() const noexcept {
	return "BR::Exceptions::Exception";
}

} // namespace Exceptions

} // namespace BR