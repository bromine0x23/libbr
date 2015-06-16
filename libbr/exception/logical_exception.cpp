#include <libbr/exception/logical_exception.hpp>

namespace BR {
namespace Exception {

LogicalException::LogicalException() noexcept : BaseException("BR::Exception::LogicalException") {}

LogicalException::LogicalException(char const * message) noexcept : BaseException(message) {}

LogicalException::LogicalException(LogicalException const & exception) noexcept : BaseException(exception) {}

LogicalException & LogicalException::operator=(LogicalException const & exception) noexcept {
	BaseException::operator=(exception);
	return *this;
}

LogicalException::~LogicalException() noexcept {}

} // namespace Exception
} // namespace BR