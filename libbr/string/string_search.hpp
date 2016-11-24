/**
 * @file
 * @brief string_search
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL strstr
 * @param[in] S
 * @param[in] K
 */
//@{
auto libbr_nstring_search(BR::NChar * S, BR::CString<BR::NChar> K) -> BR::NChar *;

auto libbr_wstring_search(BR::WChar * S, BR::CString<BR::WChar> K) -> BR::WChar *;
//@}

}

namespace BR {

/**
 * @brief like C STL strstr
 * @param[in] S
 * @param[in] K
 * @see libbr_nstring_search
 * @see libbr_nstring_search
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

template< typename TChar >
auto string_search(TChar * S, CString<TChar> K) -> TChar * {
	return nullptr;
}
//@}

} // namespace BR