#pragma once

#include <exception>
#include <libbr/config.hpp>

namespace BR {

using STDException = std::exception;

using BadException = std::bad_exception;

using TerminateHandler = std::terminate_handler;

using ExceptionPointer = std::exception_ptr;

using NestedException = std::nested_exception;

inline TerminateHandler set_terminate(TerminateHandler handler) noexcept {
	return std::set_terminate(handler);
}

/*
TerminateHandler get_terminate() noexcept {
	return std::get_terminate();
}
*/

[[noreturn]] inline void terminate() noexcept {
	std::terminate();
}

inline bool uncaught_exception() noexcept {
	return std::uncaught_exception();
}

#if defined(BR_CPP17)
inline int uncaught_exceptions() noexcept {
	return std::uncaught_exceptions();
}
#endif

inline ExceptionPointer current_exception() noexcept {
	return std::current_exception();
}

[[noreturn]] inline void rethrow_exception(ExceptionPointer pointer) {
	std::rethrow_exception(pointer);
}

template< typename TException >
inline ExceptionPointer make_exception_pointer(TException exception) noexcept {
	return std::make_exception_ptr(exception);
}

template< typename TException >
[[noreturn]] inline void throw_nested(TException && exception) {
	std::throw_with_nested(exception);
}

template< typename TException >
inline void rethrow_if_nested(TException const & exception) {
	std::rethrow_if_nested(exception);
}

class Exception : STDException {
public:
	Exception() noexcept;

	explicit Exception(char const * message) noexcept;

	Exception(Exception const & exception) noexcept;

	virtual ~Exception() noexcept;

	Exception & operator=(Exception const & exception) noexcept;

	virtual char const * what() const noexcept;

protected:
	char const * m_message;
};

} // namespace BR