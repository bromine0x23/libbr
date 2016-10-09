/**
 * @file
 * @brief string_length
 * @author Bromine0x23
 * @since 2016/6/23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL strlen
 * @param[in] S
 */
//@{
auto libbr_nstring_length(BR::CString<BR::NChar> S) -> BR::Size;

auto libbr_wstring_length(BR::CString<BR::WChar> S) -> BR::Size;
//@}

}

namespace BR {

/**
 * @brief like C STL strlen
 * @param[in] S
 * @see libbr_nstring_length
 * @see libbr_wstring_length
 */
//@{
inline auto string_length(CString<NChar> S) -> Size {
	return libbr_nstring_length(S);
}

inline auto string_length(CString<WChar> S) -> Size {
	return libbr_wstring_length(S);
}

template< typename TChar >
auto string_length(CString<TChar> S) -> Size {
	Size l = 0;
	for (; *S != TChar(0); ++S) {
		++l;
	}
	return l;
}

//@}

} // namespace BR