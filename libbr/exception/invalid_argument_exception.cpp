#include <libbr/exception/invalid_argument_exception.hpp>

namespace BR {

InvalidArgumentException::InvalidArgumentException() noexcept : BaseException("BR::Exception::InvalidArgumentException") {}

InvalidArgumentException::InvalidArgumentException(char const * message) noexcept : BaseException(message) {}

InvalidArgumentException::InvalidArgumentException(InvalidArgumentException const & exception) noexcept : BaseException(exception) {}

InvalidArgumentException & InvalidArgumentException::operator=(InvalidArgumentException const & exception) noexcept {
	BaseException::operator=(exception);
	return *this;
}

InvalidArgumentException::~InvalidArgumentException() noexcept {}

} // namespace BR