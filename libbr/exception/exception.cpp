#include <libbr/exception/std_exception.hpp>
#include <libbr/exception/exception.hpp>
#include <libbr/exception/runtime_exception.hpp>
#include <libbr/exception/logic_exception.hpp>
#include <libbr/exception/argument_exception.hpp>
#include <libbr/exception/domain_exception.hpp>
#include <libbr/exception/index_exception.hpp>
#include <libbr/exception/length_exception.hpp>
#include <libbr/exception/throw.hpp>

namespace BR {

Exception::~Exception() noexcept {
}

Exception::Message Exception::what() const noexcept {
	return "BR::Exception";
}

RuntimeException::RuntimeException(RuntimeException const & exception) noexcept : m_message(exception.m_message) {
}

RuntimeException::RuntimeException(String<NChar> const & message) : m_message(message) {
}

RuntimeException::RuntimeException(CString<NChar> message) : m_message(message) {}

RuntimeException::~RuntimeException() noexcept {
}

auto RuntimeException::operator=(RuntimeException const & exception) noexcept -> RuntimeException & {
	m_message = exception.m_message;
	return *this;
}

auto RuntimeException::what() const noexcept -> Message {
	return m_message.data();
}

LogicException::LogicException(LogicException const & exception) noexcept : m_message(exception.m_message) {
}

LogicException::LogicException(String<NChar> const & message) : m_message(message) {
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
	return m_message.data();
}

ArgumentException::~ArgumentException() noexcept {
}

DomainException::~DomainException() noexcept {
}

IndexException::~IndexException() noexcept {
}

LengthException::~LengthException() noexcept {
}

[[noreturn]] void throw_runtime_exception(CString<NChar> message) {
	throw RuntimeException(message);
}

[[noreturn]] void throw_logic_exception(CString<NChar> message) {
	throw LogicException(message);
}

[[noreturn]] void throw_argument_exception(CString<NChar> message) {
	throw ArgumentException(message);
}

[[noreturn]] void throw_domain_exception(CString<NChar> message) {
	throw DomainException(message);
}

[[noreturn]] void throw_index_exception(CString<NChar> message) {
	throw IndexException(message);
}

[[noreturn]] void throw_length_exception(CString<NChar> message) {
	throw LengthException(message);
}

} // namespace BR