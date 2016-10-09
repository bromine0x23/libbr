#include <libbr/assert/assert.hpp>
#include <libbr/exception/std_exception.hpp>
#include <libbr/exception/exception.hpp>
#include <libbr/exception/runtime_exception.hpp>
#include <libbr/exception/logic_exception.hpp>
#include <libbr/exception/argument_exception.hpp>
#include <libbr/exception/domain_exception.hpp>
#include <libbr/exception/index_exception.hpp>
#include <libbr/exception/length_exception.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/string/string_length.hpp>

namespace BR {

Exception::~Exception() noexcept {
}

Exception::Message Exception::what() const noexcept {
	return "BR::Exception";
}

RuntimeException::RuntimeException(RuntimeException const & exception) noexcept : m_message(exception.m_message) {
}

RuntimeException::RuntimeException(RawString<NChar> const & message) : m_message(message) {
}

RuntimeException::RuntimeException(CString<NChar> message) : m_message(message, string_length(message)) {}

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

LogicException::LogicException(RawString<NChar> const & message) : m_message(message) {
}

LogicException::LogicException(CString<NChar> message) : m_message(message, string_length(message)) {
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
#if defined(BR_NO_EXCEPTIONS)
	assert(!"throw_runtime_exception");
#else
	throw RuntimeException(message);
#endif
}

[[noreturn]] void throw_logic_exception(CString<NChar> message) {
#if defined(BR_NO_EXCEPTIONS)
	assert(!"throw_logic_exception");
#else
	throw LogicException(message);
#endif
}

[[noreturn]] void throw_argument_exception(CString<NChar> message) {
#if defined(BR_NO_EXCEPTIONS)
	assert(!"throw_argument_exception");
#else
	throw ArgumentException(message);
#endif
}

[[noreturn]] void throw_domain_exception(CString<NChar> message) {
#if defined(BR_NO_EXCEPTIONS)
	assert(!"throw_domain_exception");
#else
	throw DomainException(message);
#endif
}

[[noreturn]] void throw_index_exception(CString<NChar> message) {
#if defined(BR_NO_EXCEPTIONS)
	assert(!"throw_index_exception");
#else
	throw IndexException(message);
#endif
}

[[noreturn]] void throw_length_exception(CString<NChar> message) {
#if defined(BR_NO_EXCEPTIONS)
	assert(!"throw_length_exception");
#else
	throw LengthException(message);
#endif
}

} // namespace BR