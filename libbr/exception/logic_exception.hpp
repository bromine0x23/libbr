/**
 * @file
 * @brief LogicException class
 * @author Bromine0x23
 * @since 2015/10/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/runtime_exception.hpp>

#include <string>

namespace BR {

/**
 * @brief Class of logical exception.
 */
class LogicException : public Exception {
public:
	using BaseException = RuntimeException;

	LogicException() : LogicException("BR::LogicException");

	LogicException(LogicException const &) noexcept;

	explicit LogicException(std::string const & message);

	explicit LogicException(CString<NChar> message);

	virtual ~LogicException() noexcept;

	LogicException & operator=(LogicException const &) noexcept;

	virtual Message message() const noexcept;

private:
	std::string m_message;
};

} // namespace BR