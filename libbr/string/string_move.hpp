/**
 * @file
 * @brief string_move
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL memmove
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
//@{
auto libbr_nstring_move(BR::NChar * D, BR::CString<BR::NChar> S, BR::Size n) -> BR::NChar *;

auto libbr_wstring_move(BR::WChar * D, BR::CString<BR::WChar> S, BR::Size n) -> BR::WChar *;
//@}

}

namespace BR {

/**
 * @brief like C STL memmove
 * @param[out] D
 * @param[in] S
 * @param[in] n
 * @see libbr_nstring_move
 * @see libbr_wstring_move
 */
//@{
inline auto string_move(NChar * D, CString<NChar> S, Size n) -> NChar * {
	return libbr_nstring_move(D, S, n);
}

inline auto string_move(WChar * D, CString<WChar> S, Size n) -> WChar * {
	return libbr_wstring_move(D, S, n);
}

template< typename TChar >
auto string_move(TChar * D, CString<TChar> S, Size n) -> TChar * {
	TChar * R = D;
	if (D < S) {
		for (; n > 0; --n) {
			*D++ = *S++;
		}
	} else if (S < D) {
		D += n;
		S += n;
		for (; n > 0; --n) {
			*--D = *--S;
		}
	}
	return R;
}
//@}

} // namespace BR