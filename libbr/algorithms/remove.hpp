/**
 * @file
 * @brief remove
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/find.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Removes elements that equal to specific value.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p value.
 * @param[in,out] first,last The range of elements to process.
 * @param[in] value The value of elements to remove.
 * @return Iterator to the end of new range.
 */
template< typename TForwardIterator, typename TValue >
constexpr auto remove(
	TForwardIterator first, TForwardIterator last,
	TValue const & value
) -> TForwardIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TValue >
constexpr auto remove(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator {
	first = find(first, last, value);
	if (first != last) {
		for (auto iterator = first; ++iterator != last; ) {
			if (!(*iterator == value)) {
				*first = transfer(*iterator);
				++first;
			}
		}
	}
	return first;
}

} // namespace Algorithms

} // namespace BR
