/**
 * @file
 * @brief replace
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithms {

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

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TValue >
inline void replace(TForwardIterator first, TForwardIterator last, TValue const & old_value, TValue const & new_value) {
	for (; first != last; ++first) {
		if (*first == old_value) {
			*first = new_value;
		}
	}
}

} // namespace Algorithms

} // namespace BR
