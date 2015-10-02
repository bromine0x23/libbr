/**
 * @file
 * @author Bromine0x23
 * @since 2015/10/2
 */
#include <libbr/exception/runtime_exception.hpp>

namespace BR {

RuntimeException::RuntimeException(RuntimeException const & exception) noexcept : m_message(exception.m_message) {
}

RuntimeException::RuntimeException(std::string const & message) : m_message(message) {
}

RuntimeException::RuntimeException(CString<NChar> message) : m_message(message) {}

RuntimeException::~RuntimeException() noexcept {
}

RuntimeException & RuntimeException::operator=(RuntimeException const & exception) noexcept {
	m_message = exception.m_message;
	return *this;
}

RuntimeException::Message RuntimeException::message() const noexcept {
	return m_message.c_str();
}

} // namespace BR