/**
 * @file
 * @brief RuntimeException class
 * @author Bromine0x23
 * @since 2015/10/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/exception.hpp>
#include <libbr/string/string.hpp>

namespace BR {

/**
 * @brief Class of runtime exception.
 */
class RuntimeException : public Exception {
public:
	using BaseException = Exception;

	RuntimeException() : RuntimeException("BR::RuntimeException") {
	};

	RuntimeException(RuntimeException const & exception) noexcept;

	explicit RuntimeException(String<NChar> const & message);

	explicit RuntimeException(CString<NChar> message);

	~RuntimeException() noexcept override;

	auto operator=(RuntimeException const & exception) noexcept -> RuntimeException &;

	auto what() const noexcept -> Message override;

private:
	String<NChar> m_message;
};

} // namespace BR