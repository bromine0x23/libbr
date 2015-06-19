#include <libbr/exception/index_out_of_range_exception.hpp>

namespace BR {

IndexOutOfRangeException::IndexOutOfRangeException() noexcept : BaseException("BR::Exception::IndexOutOfRangeException") {}

IndexOutOfRangeException::IndexOutOfRangeException(char const * message) noexcept : BaseException(message) {}

IndexOutOfRangeException::IndexOutOfRangeException(IndexOutOfRangeException const & exception) noexcept : BaseException(exception) {}

IndexOutOfRangeException & IndexOutOfRangeException::operator=(IndexOutOfRangeException const & exception) noexcept {
	BaseException::operator=(exception);
	return *this;
}

IndexOutOfRangeException::~IndexOutOfRangeException() noexcept {}

} // namespace BR