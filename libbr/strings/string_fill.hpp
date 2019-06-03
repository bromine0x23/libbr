/**
 * @file
 * @brief string_fill
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL memset
 * @param[out] destination
 * @param[in] count
 * @param[in] value
 */
//@{
auto libbr_nstring_fill(BR::NChar * destination, BR::Size count, BR::NChar value) -> BR::NChar *;

auto libbr_wstring_fill(BR::WChar * destination, BR::Size count, BR::WChar value) -> BR::WChar *;
//@}

}

namespace BR {

inline namespace Strings {

/**
 * @brief like C STL memset
 * @param[out] destination
 * @param[in] count
 * @param[in] value
 * @see libbr_nstring_fill
 * @see libbr_wstring_fill
 */
//@{
inline auto string_fill(NChar * destination, NChar value, Size count) -> NChar * {
	return libbr_nstring_fill(destination, value, count);
}

inline auto string_fill(WChar * destination, WChar value, Size count) -> WChar * {
	return libbr_wstring_fill(destination, value, count);
}

template< typename TChar >
auto string_fill(TChar * destination, Size count, TChar value) -> TChar * {
	TChar * result = destination;
	for (; count > 0; --count) {
		*destination++ = value;
	}
	return result;
}
//@}

} // namespace Strings

} // namespace BR