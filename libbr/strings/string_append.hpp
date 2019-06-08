/**
 * @file
 * @brief string_append
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL strcat
 * @param[out] destination
 * @param[in] source
 */
//@{
auto libbr_nstring_append(BR::NChar * destination, BR::CString<BR::NChar> source) -> BR::NChar *;

auto libbr_wstring_append(BR::WChar * destination, BR::CString<BR::WChar> source) -> BR::WChar *;
//@}

/**
 * @brief like C STL strncat
 * @param[out] destination
 * @param[in] source
 * @param[in] count
 */
//@{
auto libbr_nstring_append_n(BR::NChar * destination, BR::CString<BR::NChar> source, BR::Size count) -> BR::NChar *;

auto libbr_wstring_append_n(BR::WChar * destination, BR::CString<BR::WChar> source, BR::Size count) -> BR::WChar *;
//@}

}

namespace BR {

inline namespace Strings {

/**
 * @brief like C STL strcat
 * @param[out] destination
 * @param[in] source
 * @see libbr_nstring_append
 * @see libbr_wstring_append
 */
//@{
inline auto string_append(NChar * destination, CString<NChar> source) -> NChar * {
	return libbr_nstring_append(destination, source);
}

inline auto string_append(WChar * destination, CString<WChar> source) -> WChar * {
	return libbr_wstring_append(destination, source);
}

template< typename TChar >
auto string_append(TChar * destination, CString<TChar> source) -> TChar * {
	TChar * result = destination;
	for (; *destination != TChar(); ++destination) {}
	for (; *source != TChar();) {
		*destination++ = *source++;
	}
	return result;
}

//@}

/**
 * @brief like C STL strncat
 * @param[out] destination
 * @param[in] source
 * @param[in] count
 * @see libbr_nstring_append_n
 * @see libbr_wstring_append_n
 */
//@{
inline auto string_append(NChar * destination, CString<NChar> source, Size count) -> NChar * {
	return libbr_nstring_append_n(destination, source, count);
}

inline auto string_append(WChar * destination, CString<WChar> source, Size count) -> WChar * {
	return libbr_wstring_append_n(destination, source, count);
}

template< typename TChar >
auto string_append(TChar * destination, CString<TChar> source, Size count) -> TChar * {
	TChar * result = destination;
	for (; *destination != TChar(); ++destination) {}
	for (; count-- > 0;) {
		*destination++ = *source++;
	}
	return result;
}

//@}

} // namespace Strings

} // namespace BR