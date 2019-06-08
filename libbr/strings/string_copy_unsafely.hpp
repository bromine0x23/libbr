/**
 * @file
 * @brief string_copy_unsafely
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>

extern "C" {

/**
 * @brief like C STL strcpy
 * @param[in] source
 * @param[out] destination
 */
//@{
auto libbr_nstring_copy_unsafely(BR::CString<BR::NChar> source, BR::NChar * destination) -> BR::NChar *;

auto libbr_wstring_copy_unsafely(BR::CString<BR::WChar> source, BR::WChar * destination) -> BR::WChar *;
//@}

/**
 * @brief like C STL strncpy
 * @param[in] source
 * @param[out] destination
 * @param[in] count
 */
//@{
auto libbr_nstring_copy_unsafely_n(BR::CString<BR::NChar> source, BR::NChar * destination, BR::Size count) -> BR::NChar *;

auto libbr_wstring_copy_unsafely_n(BR::CString<BR::WChar> source, BR::WChar * destination, BR::Size count) -> BR::WChar *;
//@}

}

namespace BR {

inline namespace Strings {

/**
 * @brief like C STL strcpy
 * @param[in] source
 * @param[out] destination
 * @see libbr_nstring_copy_unsafely
 * @see libbr_wstring_copy_unsafely
 */
//@{
inline auto string_copy_unsafely(CString<NChar> source, NChar * destination) -> NChar * {
	return libbr_nstring_copy_unsafely(source, destination);
}

inline auto string_copy_unsafely(CString<WChar> source, WChar * destination) -> WChar * {
	return libbr_wstring_copy_unsafely(source, destination);
}
//@}

/**
 * @brief like C STL strncpy
 * @param[in] source
 * @param[out] destination
 * @param[in] count
 * @see libbr_nstring_copy_unsafely_n
 * @see libbr_wstring_copy_unsafely_n
 */
//@{
inline auto string_copy_unsafely(CString<NChar> source, NChar * destination, Size count) -> NChar * {
	return libbr_nstring_copy_unsafely_n(source, destination, count);
}

inline auto string_copy_unsafely(CString<WChar> source, WChar * destination, Size count) -> WChar * {
	return libbr_wstring_copy_unsafely_n(source, destination, count);
}

template< typename TChar >
auto string_copy_unsafely(CString<TChar> source, TChar * destination, Size count) -> TChar * {
	BR_ASSERT(source < destination || source >= destination + count);
	for (; count > 0; --count) {
		*destination++ = *source++;
	}
	return destination;
}
//@}

} // namespace Strings

} // namespace BR