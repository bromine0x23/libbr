#include <libbr/functional/bad_call_exception.hpp>

namespace BR {

BadCallException::~BadCallException() noexcept {
}

auto BadCallException::what() const noexcept -> Message {
	return "BadCallException";
}

} // namespace BR