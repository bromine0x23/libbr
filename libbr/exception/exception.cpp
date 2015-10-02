#include <libbr/exception/exception.hpp>

namespace BR {

Exception::~Exception() noexcept {}

Exception::Message Exception::message() const noexcept {
	return "BR::Exception";
}

Exception::Message Exception::what() const noexcept {
	return message();
}

} // namespace BR