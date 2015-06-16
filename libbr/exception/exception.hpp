#pragma once

#include <exception>
#include <libbr/config.hpp>

namespace BR {
namespace Exception {

using STDException = std::exception;

using BadException = std::bad_exception;

using TerminateHandler = std::terminate_handler;

using ExceptionPointer = std::exception_ptr;

using NestedException = std::nested_exception;

inline TerminateHandler setTerminate(TerminateHandler handler) noexcept {
	return std::set_terminate(handler);
}

/*
TerminateHandler getTerminate() noexcept {
	return std::get_terminate();
}
*/

[[noreturn]] inline void terminate() noexcept {
	std::terminate();
}

inline bool uncaughtException() noexcept {
	return std::uncaught_exception();
}

#if defined(BR_CPP17)
inline int uncaughtExceptions() noexcept {
	return std::uncaught_exceptions();
}
#endif

inline ExceptionPointer currentException() noexcept {
	return std::current_exception();
}

[[noreturn]] inline void rethrowException(ExceptionPointer pointer) {
	std::rethrow_exception(pointer);
}

template< typename TException >
inline ExceptionPointer makeExceptionPointer(TException exception) noexcept {
	return std::make_exception_ptr(exception);
}

template< typename TException >
[[noreturn]] inline void throwNested(TException && exception) {
	std::throw_with_nested(exception);
}

template< typename TException >
inline void rethrowIfNested(TException const & exception) {
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

} // namespace Exception
} // namespace BR