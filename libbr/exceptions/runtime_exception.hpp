/**
 * @file
 * @brief RuntimeException class
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exceptions/exception.hpp>
#include <libbr/exceptions/_/message.hpp>

namespace BR {

inline namespace Exceptions {

/**
 * @brief Class of runtime exception.
 */
class RuntimeException : public Exception {
public:
	using BaseException = Exception;

private:
	_::Exceptions::Message _message;

public:
	RuntimeException() : RuntimeException("BR::RuntimeException") {
	};

	RuntimeException(RuntimeException const & exception) noexcept;

	explicit RuntimeException(CString<NChar> message);

	~RuntimeException() noexcept override;

	auto operator=(RuntimeException const & exception) noexcept -> RuntimeException &;

	auto what() const noexcept -> CString<NChar> override;
};

} // namespace Exceptions

} // namespace BR