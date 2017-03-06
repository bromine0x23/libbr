/**
 * @file
 * @brief replace
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Replaces all elements that equal to specific value.
 *
 * Replaces all elements that equal to \p old_value.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p old_value & \p new_value.
 * @param[in,out] first,last The range of elements to process.
 * @param[in] old_value The value of elements to replace.
 * @param[in] new_value The value to use as replacement.
 */
template< typename TForwardIterator, typename TValue >
void replace(
	TForwardIterator first, TForwardIterator last,
	TValue const & old_value,
	TValue const & new_value
);

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
