/**
 * @file
 * @brief Exception
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exceptions/stl.hpp>

namespace BR {

inline namespace Exceptions {

/**
 * @brief Basic exception class
 */
class Exception : STLException {
public:
	using Message = CString<NChar>;

	Exception() noexcept {
	};

	~Exception() noexcept override;

	auto what() const noexcept -> Message override;
};

} // namespace Exceptions

} // namespace BR