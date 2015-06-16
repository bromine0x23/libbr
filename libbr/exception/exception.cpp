#include <libbr/exception/exception.hpp>

namespace BR {
namespace Exception {

Exception::Exception() noexcept : m_message("BR::Exception::Exception") {};

Exception::Exception(char const * message) noexcept : m_message(message) {}

Exception::Exception(Exception const & exception) noexcept : m_message(exception.m_message) {}

Exception::~Exception() noexcept {}

Exception & Exception::operator=(Exception const & exception) noexcept {
	m_message = exception.m_message;
	return *this;
}

char const * Exception::what() const noexcept {
	return m_message;
}


} // namespace Exception
} // namespace BR