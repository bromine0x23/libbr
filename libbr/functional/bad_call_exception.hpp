/**
 * @file
 * @brief class BadFunctionCall
 * @author Bromine0x23
 * @since 2015/10/31
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/exception.hpp>


namespace BR {

class BadCallException : public Exception {
public:
	~BadCallException() noexcept override;

	auto what() const noexcept -> Message override;
};

} // namespace BR