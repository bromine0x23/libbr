/**
 * @file
 * @brief RuntimeException class
 * @author Bromine0x23
 * @since 2015/10/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/exception.hpp>

#include <string>

namespace BR {

/**
 * @brief Class of runtime exception.
 */
class RuntimeException : public Exception {
public:
	using BaseException = Exception;

	RuntimeException() : RuntimeException("BR::RuntimeException") {};

	RuntimeException(RuntimeException const & exception) noexcept;

	explicit RuntimeException(std::string const & message);

	explicit RuntimeException(CString<NChar> message);

	virtual ~RuntimeException() noexcept;

	RuntimeException & operator=(RuntimeException const & exception) noexcept;

	virtual Message message() const noexcept;

private:
	std::string m_message;
};

} // namespace BR