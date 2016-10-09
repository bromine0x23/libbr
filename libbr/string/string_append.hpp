/**
 * @file
 * @brief string_append
 * @author Bromine0x23
 * @since 2016/6/23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL strcat
 * @param[out] D
 * @param[in] S
 */
//@{
auto libbr_nstring_append(BR::NChar * D, BR::CString<BR::NChar> S) -> BR::NChar *;

auto libbr_wstring_append(BR::WChar * D, BR::CString<BR::WChar> S) -> BR::WChar *;
//@}

/**
 * @brief like C STL strncat
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
//@{
auto libbr_nstring_append_n(BR::NChar * D, BR::CString<BR::NChar> S, BR::Size n) -> BR::NChar *;

auto libbr_wstring_append_n(BR::WChar * D, BR::CString<BR::WChar> S, BR::Size n) -> BR::WChar *;
//@}

}

namespace BR {

/**
 * @brief like C STL strcat
 * @param[out] D
 * @param[in] S
 * @see libbr_nstring_append
 * @see libbr_wstring_append
 */
//@{
inline auto string_append(NChar * D, CString<NChar> S) -> NChar * {
	return libbr_nstring_append(D, S);
}

inline auto string_append(WChar * D, CString<WChar> S) -> WChar * {
	return libbr_wstring_append(D, S);
}

template< typename TChar >
auto string_append(TChar * D, CString<TChar> S) -> TChar * {
	TChar * R = D;
	for (; *D != TChar(); ++D) {}
	for (; *S != TChar();) {
		*D++ = *S++;
	}
	return R;
}

//@}

/**
 * @brief like C STL strncat
 * @param[out] D
 * @param[in] S
 * @param[in] n
 * @see libbr_nstring_append_n
 * @see libbr_wstring_append_n
 */
//@{
inline auto string_append(NChar * D, CString<NChar> S, Size n) -> NChar * {
	return libbr_nstring_append_n(D, S, n);
}

inline auto string_append(WChar * D, CString<WChar> S, Size n) -> WChar * {
	return libbr_wstring_append_n(D, S, n);
}

template< typename TChar >
auto string_append(TChar * D, CString<TChar> S, Size n) -> TChar * {
	TChar * R = D;
	for (; *D != TChar(); ++D) {}
	for (; n-- > 0;) {
		*D++ = *S++;
	}
	return R;
}

//@}

} // namespace BR