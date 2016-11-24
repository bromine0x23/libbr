/**
 * @file
 * @brief string_compare
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/relation.hpp>

extern "C" {

/**
 * @brief like C STL strcmp
 * @param[in] X
 * @param[in] Y
 */
//@{
auto libbr_nstring_compare(BR::CString<BR::NChar> X, BR::CString<BR::NChar> Y) -> BR::Relation;

auto libbr_wstring_compare(BR::CString<BR::WChar> X, BR::CString<BR::WChar> Y) -> BR::Relation;
//@}

/**
 * @brief like C STL strncmp
 * @param[in] X
 * @param[in] Y
 * @param[in] n
 */
//@{
auto libbr_nstring_compare_n(BR::CString<BR::NChar> X, BR::CString<BR::NChar> Y, BR::Size n) -> BR::Relation;

auto libbr_wstring_compare_n(BR::CString<BR::WChar> X, BR::CString<BR::WChar> Y, BR::Size n) -> BR::Relation;
//@}

}

namespace BR {

/**
 * @brief like C STL strcmp
 * @param[in] X
 * @param[in] Y
 * @see libbr_nstring_compare
 * @see libbr_wstring_compare
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
 * @brief like C STL strncmp
 * @param[in] X
 * @param[in] Y
 * @param[in] n
 * @see libbr_nstring_compare_n
 * @see libbr_wstring_compare_n
 */
//@{
inline auto string_compare(CString<NChar> X, CString<NChar> Y, Size n) -> Relation {
	return libbr_nstring_compare_n(X, Y, n);
}

inline auto string_compare(CString<WChar> X, CString<WChar> Y, Size n) -> Relation {
	return libbr_wstring_compare_n(X, Y, n);
}

template< typename TChar >
auto string_compare(CString<TChar> X, CString<TChar> Y, Size n) -> Relation {
	for (; n > 0; --n, ++X, ++Y) {
		if (*X < *Y) {
			return Relation::LT;
		}
		if (*Y < *X) {
			return Relation::GT;
		}
	}
	return Relation::EQ;
}

//@}

} // namespace BR