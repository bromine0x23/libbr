/**
 * @file
 * @brief string_fill
 * @author Bromine0x23
 * @since 2016/6/23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL memset
 * @param[out] D
 * @param[in] c
 * @param[in] n
 */
//@{
auto libbr_nstring_fill(BR::NChar * D, BR::NChar c, BR::Size n) -> BR::NChar *;

auto libbr_wstring_fill(BR::WChar * D, BR::WChar c, BR::Size n) -> BR::WChar *;
//@}

}

namespace BR {

/**
 * @brief like C STL memset
 * @param[out] D
 * @param[in] c
 * @param[in] n
 * @see libbr_nstring_fill
 * @see libbr_wstring_fill
 */
//@{
inline auto string_fill(NChar * D, NChar c, Size n) -> NChar * {
	return libbr_nstring_fill(D, c, n);
}

inline auto string_fill(WChar * D, WChar c, Size n) -> WChar * {
	return libbr_wstring_fill(D, c, n);
}

template< typename TChar >
auto string_fill(TChar * D, TChar c, Size n) -> TChar * {
	TChar * R = D;
	for (; n > 0; --n) {
		*D++ = c;
	}
	return R;
}
//@}

} // namespace BR