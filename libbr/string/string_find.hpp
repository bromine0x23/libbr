/**
 * @file
 * @brief string_find
 * @author Bromine0x23
 * @since 2016/6/23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL strchr
 * @param[in] S
 * @param[in] c
 */
//@{
auto libbr_nstring_find(BR::NChar * S, BR::NChar c) -> BR::NChar *;

auto libbr_wstring_find(BR::WChar * S, BR::WChar c) -> BR::WChar *;
//@}

/**
 * @brief like C STL memchr
 * @param[in] S
 * @param[in] c
 * @param[in] n
 */
//@{
auto libbr_nstring_find_n(BR::NChar * S, BR::NChar c, BR::Size n) -> BR::NChar *;

auto libbr_wstring_find_n(BR::WChar * S, BR::WChar c, BR::Size n) -> BR::WChar *;
//@}

}

namespace BR {
/**
 * @brief like C STL strchr
 * @param[in] S
 * @param[in] c
 * @see libbr_nstring_find
 * @see libbr_wstring_find
 */
//@{
inline auto string_find(NChar const * S, NChar c) -> NChar const * {
	return const_cast<NChar const *>(libbr_nstring_find(const_cast<NChar *>(S), c));
}

inline auto string_find(WChar const * S, WChar c) -> WChar const * {
	return const_cast<WChar const *>(libbr_wstring_find(const_cast<WChar *>(S), c));
}

inline auto string_find(NChar * S, NChar c) -> NChar * {
	return libbr_nstring_find(S, c);
}

inline auto string_find(WChar * S, WChar c) -> WChar * {
	return libbr_wstring_find(S, c);
}

template< typename TChar >
auto string_find(TChar const * S, TChar c) -> TChar const * {
	for (; *S != TChar(); ++S) {
		if (*S == c) {
			return S;
		}
	}
	return nullptr;
}

template< typename TChar >
inline auto string_find(TChar * S, TChar c) -> WChar * {
	return const_cast<TChar *>(string_find(const_cast<TChar const *>(S), c));
}
//@}

/**
 * @brief like C STL memchr
 * @param[in] S
 * @param[in] c
 * @param[in] n
 * @see libbr_nstring_find_n
 * @see libbr_wstring_find_n
 */
//@{
inline auto string_find(NChar const * S, NChar c, Size n) -> NChar const * {
	return const_cast<NChar const *>(libbr_nstring_find_n(const_cast<NChar *>(S), c, n));
}

inline auto string_find(WChar const * S, WChar c, Size n) -> WChar const * {
	return const_cast<WChar const *>(libbr_wstring_find_n(const_cast<WChar *>(S), c, n));
}

inline auto string_find(NChar * S, NChar c, Size n) -> NChar * {
	return libbr_nstring_find_n(S, c, n);
}

inline auto string_find(WChar * S, WChar c, Size n) -> WChar * {
	return libbr_wstring_find_n(S, c, n);
}

template< typename TChar >
auto string_find(TChar const * S, TChar c, Size n) -> TChar const * {
	for (; n-- > 0; ++S) {
		if (*S == c) {
			return S;
		}
	}
	return nullptr;
}

template< typename TChar >
inline auto string_find(TChar * S, TChar c, Size n) -> WChar * {
	return const_cast<TChar *>(string_find(const_cast<TChar const *>(S), c, n));
}
//@}

} // namespace BR