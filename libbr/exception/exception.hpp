/**
 * @file
 * @brief Exception
 * @author Bromine0x23
 * @since 2015/10/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/std_exception.hpp>

namespace BR {

/**
 * @brief Basic exception class
 */
class Exception : STDException {
public:
	using Message = CString<NChar>;

	Exception() noexcept {
	};

	virtual ~Exception() noexcept override;

	auto what() const noexcept -> Message override;
};

} // namespace BR