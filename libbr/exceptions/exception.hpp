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
class Exception {
public:
	Exception() noexcept {};

	Exception(Exception const&) = default;

	Exception(Exception &&) = default;

	virtual ~Exception() noexcept;

	auto operator=(Exception const &) -> Exception & = default;

	auto operator=(Exception &&) -> Exception & = default;

	virtual auto what() const noexcept -> CString<NChar>;
};

} // namespace Exceptions

} // namespace BR