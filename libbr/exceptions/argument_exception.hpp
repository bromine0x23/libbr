/**
 * @file
 * @brief ArgumentException class
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exceptions/runtime_exception.hpp>

namespace BR {

/**
 * @brief Class to be thrown when an argument value has not been accepted.
 */
class ArgumentException : public RuntimeException {
public:
	using BaseException = LogicException;

	ArgumentException() : BaseException("BR::ArgumentException") {
	}

	explicit ArgumentException(RawString<NChar> const & message) : BaseException(message) {
	}

	explicit ArgumentException(CString<NChar> message) : BaseException(message) {
	}

	~ArgumentException() noexcept override;
};

} // namespace BR