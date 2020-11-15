/**
 * @file
 * @brief warp STL's <a href="http://en.cppreference.com/w/cpp/header/exception">`<exception>`</a>
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

#include <exception>

namespace BR {

inline namespace Exceptions {

using STLException = std::exception;

using STLBadException = std::bad_exception;

using STLTerminateHandler = std::terminate_handler;

using STLExceptionPointer = std::exception_ptr;

using STLNestedException = std::nested_exception;

inline auto set_terminate(STLTerminateHandler handler) noexcept -> STLTerminateHandler {
	return std::set_terminate(handler);
}

inline auto get_terminate() noexcept -> STLTerminateHandler {
	return std::get_terminate();
}

[[noreturn]] inline void terminate() noexcept {
	std::terminate();
}

inline auto uncaught_exceptions() noexcept -> int {
	return std::uncaught_exceptions();
}

inline auto current_exception() noexcept -> STLExceptionPointer {
	return std::current_exception();
}

[[noreturn]] inline void rethrow_exception(STLExceptionPointer pointer) {
	std::rethrow_exception(pointer);
}

template< typename TException >
inline auto make_exception_pointer(TException exception) noexcept -> STLExceptionPointer {
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

} // namespace Exceptions

} // namespace BR