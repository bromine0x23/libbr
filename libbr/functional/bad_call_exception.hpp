/**
 * @file
 * @brief class BadFunctionCall
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/exception.hpp>

namespace BR {

inline namespace Functional {

/**
 * @brief Exception for bad function call
 */
class BadCallException : public Exception {
public:
	~BadCallException() noexcept override;

	auto what() const noexcept -> Message override;
};

} // namespace Functional

} // namespace BR