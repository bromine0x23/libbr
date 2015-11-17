/**
 * @file
 * @brief STL's <exception>
 * @author Bromine0x23
 * @since 2015/11/12
 */
#pragma once

#include <libbr/config.hpp>

#include <exception>

namespace BR {

using STDException = std::exception;

using BadException = std::bad_exception;

using TerminateHandler = void(*)();

using ExceptionPointer = std::exception_ptr;

using NestedException = std::nested_exception;

inline auto set_terminate(TerminateHandler handler) noexcept -> TerminateHandler {
	return std::set_terminate(handler);
}

inline auto get_terminate() noexcept -> TerminateHandler {
	return std::get_terminate();
}

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

inline auto current_exception() noexcept -> ExceptionPointer{
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

} // namespace BR