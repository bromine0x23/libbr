#include <libbr/exception/exception.hpp>
#include <libbr/exception/runtime_exception.hpp>
#include <libbr/exception/logic_exception.hpp>
#include <libbr/exception/out_of_range_exception.hpp>
#include <libbr/exception/argument_exception.hpp>

namespace BR {

auto set_terminate(TerminateHandler handler) noexcept -> TerminateHandler {
	return std::set_terminate(handler);
}

[[noreturn]] void terminate() noexcept {
	std::terminate();
}

auto uncaught_exception() noexcept -> bool {
	return std::uncaught_exception();
}

#if defined(BR_CPP17)
auto uncaught_exceptions() noexcept -> int {
	return std::uncaught_exceptions();
}
#endif

Exception::~Exception() noexcept {
}

Exception::Message Exception::what() const noexcept {
	return "BR::Exception";
}

RuntimeException::RuntimeException(RuntimeException const & exception) noexcept : m_message(exception.m_message) {
}

RuntimeException::RuntimeException(std::string const & message) : m_message(message) {
}

RuntimeException::RuntimeException(CString<NChar> message) : m_message(message) {}

RuntimeException::~RuntimeException() noexcept {
}

auto RuntimeException::operator=(RuntimeException const & exception) noexcept -> RuntimeException & {
	m_message = exception.m_message;
	return *this;
}

auto RuntimeException::what() const noexcept -> Message {
	return m_message.c_str();
}

LogicException::LogicException(LogicException const & exception) noexcept : m_message(exception.m_message) {
}

LogicException::LogicException(std::string const & message) : m_message(message) {
}

LogicException::LogicException(CString<NChar> message) : m_message(message) {
}

LogicException::~LogicException() noexcept {
}

auto LogicException::operator=(LogicException const & exception) noexcept -> LogicException & {
	m_message = exception.m_message;
	return *this;
}

auto LogicException::what() const noexcept -> Message {
	return m_message.c_str();
}

OutOfRangeException::~OutOfRangeException() noexcept {
}

ArgumentException::~ArgumentException() noexcept {
}

} // namespace BR