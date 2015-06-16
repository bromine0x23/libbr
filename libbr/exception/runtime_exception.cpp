#include <libbr/exception/runtime_exception.hpp>

namespace BR {
namespace Exception {

RuntimeException::RuntimeException() noexcept : BaseException("BR::Exception::RuntimeException") {}

RuntimeException::RuntimeException(char const * message) noexcept : BaseException(message) {}

RuntimeException::RuntimeException(RuntimeException const & exception) noexcept : BaseException(exception) {}

RuntimeException & RuntimeException::operator=(RuntimeException const & exception) noexcept {
	BaseException::operator=(exception);
	return *this;
}

RuntimeException::~RuntimeException() noexcept {}

} // namespace Exception
} // namespace BR