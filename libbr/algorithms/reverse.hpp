/**
 * @file
 * @brief reverse
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Reverses the order of elements in a range.
 *
 * Reverses the order of the elements in the range \f$ [first, last) \f$.
 * @tparam TBidirectionalIterator Type of \p first & \p last which satisfies \em BidirectionalIterator.
 * @param[in,out] first,last The range of elements to reverse.
 */
template< typename TBidirectionalIterator >
void reverse(
	TBidirectionalIterator first, TBidirectionalIterator last
);

} // namespace Algorithms



namespace _ {
namespace Algorithms {

template< typename TBidirectionalIterator >
inline void reverse(TBidirectionalIterator first, TBidirectionalIterator last, BidirectionalTraversalTag) {
	for (; first != last; ++first) {
		if (first == --last) {
			break;
		}
		swap(*first, *last);
	}
}


template< typename TRandomAccessIterator >
inline void reverse(TRandomAccessIterator first, TRandomAccessIterator last, RandomAccessTraversalTag) {
	if (first != last) {
		for (; first < --last; ++first) {
			swap(*first, *last);
		}
	}
}

template< typename TBidirectionalIterator >
inline void reverse(TBidirectionalIterator first, TBidirectionalIterator last) {
	return reverse(first, last, IteratorTraits<TBidirectionalIterator>::iterator_category());
}

} // namespace Algorithms
} // namespace _

inline namespace Algorithms {

template< typename TBidirectionalIterator >
inline void reverse(TBidirectionalIterator first, TBidirectionalIterator last) {
	return _::Algorithms::reverse(first, last);
}

} // namespace Algorithms

} // namespace BR
