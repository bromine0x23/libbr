/**
 * @file
 * @brief string_copy
 * @author Bromine0x23
 * @since 2016/6/23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>

extern "C" {

/**
 * @brief like C STL strcpy
 * @param[out] D
 * @param[in] S
 */
//@{
auto libbr_nstring_copy(BR::NChar * D, BR::CString<BR::NChar> S) -> BR::NChar *;

auto libbr_wstring_copy(BR::WChar * D, BR::CString<BR::WChar> S) -> BR::WChar *;
//@}

/**
 * @brief like C STL strncpy
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
//@{
auto libbr_nstring_copy_n(BR::NChar * D, BR::CString<BR::NChar> S, BR::Size n) -> BR::NChar *;

auto libbr_wstring_copy_n(BR::WChar * D, BR::CString<BR::WChar> S, BR::Size n) -> BR::WChar *;
//@}

}

namespace BR {

/**
 * @brief like C STL strcpy
 * @param[out] D
 * @param[in] S
 * @see libbr_nstring_copy
 * @see libbr_wstring_copy
 */
//@{
inline auto string_copy(NChar * D, CString<NChar> S) -> NChar * {
	return libbr_nstring_copy(D, S);
}

inline auto string_copy(WChar * D, CString<WChar> S) -> WChar * {
	return libbr_wstring_copy(D, S);
}
//@}

/**
 * @brief like C STL strncpy
 * @param[out] D
 * @param[in] S
 * @param[in] n
 * @see libbr_nstring_copy_n
 * @see libbr_wstring_copy_n
 */
//@{
inline auto string_copy(NChar * D, CString<NChar> S, Size n) -> NChar * {
	return libbr_nstring_copy_n(D, S, n);
}

inline auto string_copy(WChar * D, CString<WChar> S, Size n) -> WChar * {
	return libbr_wstring_copy_n(D, S, n);
}

template< typename TChar >
auto string_copy(TChar * D, CString<TChar> S, Size n) -> TChar * {
	BR_ASSERT(S < D || S >= D + n);
	for (; n > 0; --n) {
		*D++ = *S++;
	}
	return D;
}
//@}

} // namespace BR