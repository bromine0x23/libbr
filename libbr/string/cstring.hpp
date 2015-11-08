/**
 * @file
 * @brief cstring
 * @author Bromine0x23
 * @since 2015/11/5
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/math/relation.hpp>

extern "C" {

auto libbr_nstring_append(BR::NChar * D, BR::CString<BR::NChar> S) -> BR::NChar *;

auto libbr_wstring_append(BR::WChar * D, BR::CString<BR::WChar> S) -> BR::WChar *;

auto libbr_nstring_append_n(BR::NChar * D, BR::CString<BR::NChar> S, BR::Size n) -> BR::NChar *;

auto libbr_wstring_append_n(BR::WChar * D, BR::CString<BR::WChar> S, BR::Size n) -> BR::WChar *;

auto libbr_nstring_compare(BR::CString<BR::NChar> X, BR::CString<BR::NChar> Y) -> BR::Relation;

auto libbr_wstring_compare(BR::CString<BR::WChar> X, BR::CString<BR::WChar> Y) -> BR::Relation;

auto libbr_nstring_compare_n(BR::CString<BR::NChar> X, BR::CString<BR::NChar> Y, BR::Size n) -> BR::Relation;

auto libbr_wstring_compare_n(BR::CString<BR::WChar> X, BR::CString<BR::WChar> Y, BR::Size n) -> BR::Relation;

auto libbr_nstring_copy(BR::NChar * D, BR::CString<BR::NChar> S) -> BR::NChar *;

auto libbr_wstring_copy(BR::WChar * D, BR::CString<BR::WChar> S) -> BR::WChar *;

auto libbr_nstring_copy_n(BR::NChar * D, BR::CString<BR::NChar> S, BR::Size n) -> BR::NChar *;

auto libbr_wstring_copy_n(BR::WChar * D, BR::CString<BR::WChar> S, BR::Size n) -> BR::WChar *;

auto libbr_nstring_find(BR::NChar * S, BR::NChar c) -> BR::NChar *;

auto libbr_wstring_find(BR::WChar * S, BR::WChar c) -> BR::WChar *;

auto libbr_nstring_find_n(BR::NChar * S, BR::NChar c, BR::Size n) -> BR::NChar *;

auto libbr_wstring_find_n(BR::WChar * S, BR::WChar c, BR::Size n) -> BR::WChar *;

auto libbr_nstring_fill(BR::NChar * D, BR::NChar c, BR::Size n) -> BR::NChar *;

auto libbr_wstring_fill(BR::WChar * D, BR::WChar c, BR::Size n) -> BR::WChar *;

auto libbr_nstring_length(BR::CString<BR::NChar> S) -> BR::Size;

auto libbr_wstring_length(BR::CString<BR::WChar> S) -> BR::Size;

auto libbr_nstring_move(BR::NChar * D, BR::CString<BR::NChar> S, BR::Size n) -> BR::NChar *;

auto libbr_wstring_move(BR::WChar * D, BR::CString<BR::WChar> S, BR::Size n) -> BR::WChar *;

auto libbr_nstring_search(BR::NChar * S, BR::CString<BR::NChar> K) -> BR::NChar *;

auto libbr_wstring_search(BR::WChar * S, BR::CString<BR::WChar> K) -> BR::WChar *;

}

namespace BR {

/**
 * @brief like C STL strcat
 * @param[out] D
 * @param[in] S
 */
//@{
inline auto string_append(NChar * D, CString<NChar> S) -> NChar * {
	return libbr_nstring_append(D, S);
}

inline auto string_append(WChar * D, CString<WChar> S) -> WChar * {
	return libbr_wstring_append(D, S);
}
//@}

/**
 * @brief like C STL strncat
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
//@{
inline auto string_append(NChar * D, CString<NChar> S, Size n) -> NChar * {
	return libbr_nstring_append_n(D, S, n);
}

inline auto string_append(WChar * D, CString<WChar> S, Size n) -> WChar * {
	return libbr_wstring_append_n(D, S, n);
}
//@}

/**
 * @brief like C STL strcmp
 * @param[in] X
 * @param[in] Y
 * @see libbr_string_compare_n
 * @see libbr_string_compare_w
 */
//@{
inline auto string_compare(CString<NChar> X, CString<NChar> Y) -> Relation {
	return libbr_nstring_compare(X, Y);
}

inline auto string_compare(CString<WChar> X, CString<WChar> Y) -> Relation {
	return libbr_wstring_compare(X, Y);
}
//@}

/**
 * @brief like C STL strcmp
 * @param[in] X
 * @param[in] Y
 * @param[in] n
 */
//@{
inline auto string_compare(CString<NChar> X, CString<NChar> Y, Size n) -> Relation {
	return libbr_nstring_compare_n(X, Y, n);
}

inline auto string_compare(CString<WChar> X, CString<WChar> Y, Size n) -> Relation {
	return libbr_wstring_compare_n(X, Y, n);
}
//@}

/**
 * @brief like C STL strcpy
 * @param[out] D
 * @param[in] S
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
 */
//@{
inline auto string_copy(NChar * D, CString<NChar> S, Size n) -> NChar * {
	return libbr_nstring_copy_n(D, S, n);
}

inline auto string_copy(WChar * D, CString<WChar> S, Size n) -> WChar * {
	return libbr_wstring_copy_n(D, S, n);
}
//@}

/**
 * @brief like C STL strchr
 * @param[in] S
 * @param[in] c
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
//@}

/**
 * @brief like C STL memchr
 * @param[in] S
 * @param[in] c
 * @param[in] n
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
//@}

/**
 * @brief like C STL memset
 * @param[out] D
 * @param[in] c
 * @param[in] n
 */
//@{
inline auto string_fill(NChar * D, NChar c, Size n) -> NChar * {
	return libbr_nstring_fill(D, c, n);
}

inline auto string_fill(WChar * D, WChar c, Size n) -> WChar * {
	return libbr_wstring_fill(D, c, n);
}
//@}

/**
 * @brief like C STL strlen
 * @param[out] S
 */
//@{
inline auto string_length(CString<NChar> S) -> Size {
	return libbr_nstring_length(S);
}

inline auto string_length(CString<WChar> S) -> Size {
	return libbr_wstring_length(S);
}
//@}

/**
 * @brief like C STL memmove
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
//@{
inline auto string_move(NChar * D, CString<NChar> S, Size n) -> NChar * {
	return libbr_nstring_move(D, S, n);
}

inline auto string_move(WChar * D, CString<WChar> S, Size n) -> WChar * {
	return libbr_wstring_move(D, S, n);
}
//@}

/**
 * @brief like C STL strlen
 * @param[in] S
 * @param[in] K
 */
//@{
inline auto string_search(NChar const * S, CString<NChar> K) -> NChar const * {
	return const_cast<NChar const *>(libbr_nstring_search(const_cast<NChar *>(S), K));
}

inline auto string_search(WChar const * S, CString<WChar> K) -> WChar const * {
	return const_cast<WChar const *>(libbr_wstring_search(const_cast<WChar *>(S), K));
}

inline auto string_search(NChar * S, CString<NChar> K) -> NChar * {
	return libbr_nstring_search(S, K);
}

inline auto string_search(WChar * S, CString<WChar> K) -> WChar * {
	return libbr_wstring_search(S, K);
}
//@}

} // namespace BR

