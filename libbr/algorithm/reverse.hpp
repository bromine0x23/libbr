/**
 * @file
 * @brief reverse
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

namespace Detail {
namespace Algorithm {

template< typename TBidirectionalIterator >
inline void reverse(TBidirectionalIterator first, TBidirectionalIterator last, BidirectionalIteratorTag _dummy) {
	for (; first != last; ++first) {
		if (first == --last) {
			break;
		}
		swap(*first, *last);
	}
}


template< typename TRandomAccessIterator >
inline void reverse(TRandomAccessIterator first, TRandomAccessIterator last, RandomAccessIteratorTag _dummy) {
	if (first != last) {
		for (; first < --last; ++first) {
			swap(*first, *last);
		}
	}
}

} // namespace Algorithm
} // namespace Detail

template< typename TBidirectionalIterator >
inline void reverse(TBidirectionalIterator first, TBidirectionalIterator last) {
	return Detail::Algorithm::reverse(first, last, IteratorTraits<TBidirectionalIterator>::category());
}

} // namespace BR
