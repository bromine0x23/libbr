/**
 * @file
 * @brief Exception
 * @author Bromine0x23
 * @since 2015/10/2
 */
#pragma once

#include <exception>
#include <libbr/config.hpp>

namespace BR {

using STDException = std::exception;

using BadException = std::bad_exception;

using TerminateHandler = std::terminate_handler;

using ExceptionPointer = std::exception_ptr;

using NestedException = std::nested_exception;

inline auto set_terminate(TerminateHandler handler) noexcept -> TerminateHandler {
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

inline auto uncaught_exception() noexcept -> bool {
	return std::uncaught_exception();
}

#if defined(BR_CPP17)
inline auto uncaught_exceptions() noexcept -> int {
	return std::uncaught_exceptions();
}
#endif

inline auto current_exception() noexcept -> ExceptionPointer {
	return std::current_exception();
}

[[noreturn]] inline void rethrow_exception(ExceptionPointer pointer) {
	std::rethrow_exception(pointer);
}

template< typename TException >
inline auto make_exception_pointer(TException exception) noexcept -> ExceptionPointer {
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

/**
 * @brief Basic exception class
 */
class Exception : STDException {
public:
	using Message = CString<NChar>;

	Exception() noexcept {
	};

	virtual ~Exception() noexcept override;

	auto what() const noexcept -> Message override;
};

} // namespace BR