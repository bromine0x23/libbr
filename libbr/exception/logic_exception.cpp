/**
 * @file
 * @author Bromine0x23
 * @since 2015/10/2
 */
#include "logic_exception.hpp"

namespace BR {

LogicException::LogicException(LogicException const & exception) noexcept : m_message(exception.m_message) {
}

LogicException::LogicException(std::string const & message) : m_message(message) {
}

LogicException::LogicException(CString<NChar> message) : m_message(message) {
}

LogicException::~LogicException() noexcept {
}

LogicException &LogicException::operator=(LogicException const & exception) noexcept {
	m_message = exception.m_message;
	return *this;
}

LogicException::Message LogicException::message() const noexcept {
	return m_message.c_str();
}

} // namespace BR