/**
 * @file
 * @brief reverse_copy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Creates a copy of a range that is reversed.
 *
 * Copies the elements from the range \f$ [first, last) \f$ to another range beginning at \p output
 * in such a way that the elements in the new range are in reverse order.
 * @tparam TBidirectionalIterator Type of \p first & \p last which satisfies \em BidirectionalIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @param[in] first,last
 * @param[out] output
 * @return
 */
template< typename TBidirectionalIterator, typename TOutputIterator >
constexpr auto reverse_copy(
	TBidirectionalIterator first, TBidirectionalIterator last,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TBidirectionalIterator, typename TOutputIterator >
constexpr inline auto reverse_copy(TBidirectionalIterator first, TBidirectionalIterator last, TOutputIterator output) -> TOutputIterator {
	for (; first != last; ++output) {
		*output = *--last;
	}
	return output;
}

} // namespace Algorithms

} // namespace BR
