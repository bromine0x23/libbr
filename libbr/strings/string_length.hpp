/**
 * @file
 * @brief string_length
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL strlen
 * @param[in] string
 */
//@{
auto libbr_nstring_length(BR::CString<BR::NChar> string) -> BR::Size;

auto libbr_wstring_length(BR::CString<BR::WChar> string) -> BR::Size;
//@}

}

namespace BR {

inline namespace Strings {

/**
 * @brief like C STL strlen
 * @param[in] string
 * @see libbr_nstring_length
 * @see libbr_wstring_length
 */
//@{
inline auto string_length(CString<NChar> string) -> Size {
	return libbr_nstring_length(string);
}

inline auto string_length(CString<WChar> string) -> Size {
	return libbr_wstring_length(string);
}

template< typename TChar >
auto string_length(CString<TChar> string) -> Size {
	Size length = 0;
	for (; *string != TChar(0); ++string) {
		++length;
	}
	return length;
}

//@}

} // namespace Strings

} // namespace BR