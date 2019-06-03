/**
 * @file
 * @brief string_compare
 * @author Bromine0x23
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
 * @param[in] x,y
 * @param[in] count
 */
//@{
auto libbr_nstring_compare_n(BR::CString<BR::NChar> x, BR::CString<BR::NChar> y, BR::Size count) -> BR::Relation;

auto libbr_wstring_compare_n(BR::CString<BR::WChar> x, BR::CString<BR::WChar> y, BR::Size count) -> BR::Relation;
//@}

}

namespace BR {

inline namespace Strings {

/**
 * @brief like C STL strcmp
 * @param[in] x,y
 * @see libbr_nstring_compare
 * @see libbr_wstring_compare
 */
//@{
inline auto string_compare(CString<NChar> x, CString<NChar> y) -> Relation {
	return libbr_nstring_compare(x, y);
}

inline auto string_compare(CString<WChar> x, CString<WChar> y) -> Relation {
	return libbr_wstring_compare(x, y);
}
//@}

/**
 * @brief like C STL strncmp
 * @param[in] x,y
 * @param[in] count
 * @see libbr_nstring_compare_n
 * @see libbr_wstring_compare_n
 */
//@{
inline auto string_compare(CString<NChar> x, CString<NChar> y, Size count) -> Relation {
	return libbr_nstring_compare_n(x, y, count);
}

inline auto string_compare(CString<WChar> x, CString<WChar> y, Size count) -> Relation {
	return libbr_wstring_compare_n(x, y, count);
}

template< typename TChar >
auto string_compare(CString<TChar> x, CString<TChar> y, Size count) -> Relation {
	for (; count > 0; --count, ++x, ++y) {
		if (*x < *y) {
			return Relation::LT;
		}
		if (*y < *x) {
			return Relation::GT;
		}
	}
	return Relation::EQ;
}
//@}

} // namespace Strings

} // namespace BR