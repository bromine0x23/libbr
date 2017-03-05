/**
 * @file
 * @brief remove
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/find.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Removes elements that equal to specific value.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p value.
 * @param[in,out] first,last The range of elements to process.
 * @param[in] value The value of elements to remove.
 * @return Iterator to the end of new range.
 */
template< typename TForwardIterator, typename TValue >
auto remove(
	TForwardIterator first, TForwardIterator last,
	TValue const & value
) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TValue >
auto remove(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator {
	first = find(first, last, value);
	if (first != last) {
		for (auto iterator = first; ++iterator != last; ) {
			if (!(*iterator == value)) {
				*first = move(*iterator);
				++first;
			}
		}
	}
	return first;
}

} // namespace Algorithm

} // namespace BR
