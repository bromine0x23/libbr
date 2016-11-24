/**
 * @file
 * @brief replace
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::replace
 * @tparam TForwardIterator
 * @tparam TValue
 * @param[in,out] first,last
 * @param[in] old_value
 * @param[in] new_value
 */
template< typename TForwardIterator, typename TValue >
void replace(TForwardIterator first, TForwardIterator last, TValue const & old_value, TValue const & new_value);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TValue >
inline void replace(TForwardIterator first, TForwardIterator last, TValue const & old_value, TValue const & new_value) {
	for (; first != last; ++first) {
		if (*first == old_value) {
			*first = new_value;
		}
	}
}

} // namespace Algorithm

} // namespace BR
