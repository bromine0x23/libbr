/**
 * @file
 * @brief LogicException class
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/exception.hpp>
#include <libbr/string/raw_string.hpp>

namespace BR {

/**
 * @brief Class of logical exception.
 */
class LogicException : public Exception {
public:
	using BaseException = Exception;

	LogicException() : LogicException("BR::LogicException") {
	}

	LogicException(LogicException const &) noexcept;

	explicit LogicException(RawString<NChar> const & message);

	explicit LogicException(CString<NChar> message);

	~LogicException() noexcept override;

	auto operator=(LogicException const &) noexcept -> LogicException &;

	auto what() const noexcept -> Message override;

private:
	RawString<NChar> m_message;
};

} // namespace BR