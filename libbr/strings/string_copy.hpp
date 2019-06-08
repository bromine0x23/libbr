/**
 * @file
 * @brief string_copy
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL memmove
 * @param[in] source
 * @param[out] destination
 * @param[in] count
 */
//@{
auto libbr_nstring_copy(BR::CString<BR::NChar> source, BR::NChar * destination, BR::Size count) -> BR::NChar *;

auto libbr_wstring_copy(BR::CString<BR::WChar> source, BR::WChar * destination, BR::Size count) -> BR::WChar *;
//@}

}

namespace BR {

inline namespace Strings {

/**
 * @brief like C STL memmove
 * @param[in] source
 * @param[out] destination
 * @param[in] count
 * @see libbr_nstring_copy
 * @see libbr_wstring_copy
 */
//@{
inline auto string_copy(CString<NChar> source, NChar * destination, Size count) -> NChar * {
	return libbr_nstring_copy(source, destination, count);
}

inline auto string_copy(CString<WChar> source, WChar * destination, Size count) -> WChar * {
	return libbr_wstring_copy(source, destination, count);
}

template< typename TChar >
auto string_copy(CString<TChar> source, TChar * destination, Size count) -> TChar * {
	TChar * result = destination;
	if (destination < source) {
		for (; count > 0; --count) {
			*destination++ = *source++;
		}
	} else if (source < destination) {
		destination += count;
		source += count;
		for (; count > 0; --count) {
			*--destination = *--source;
		}
	}
	return result;
}
//@}

} // namespace Strings

} // namespace BR