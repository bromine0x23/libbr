/**
 * @file
 * @brief reverse
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::reverse
 * @tparam TBidirectionalIterator
 * @param[in,out] first,last
 */
template< typename TBidirectionalIterator >
void reverse(TBidirectionalIterator first, TBidirectionalIterator last);

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

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

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TBidirectionalIterator >
inline void reverse(TBidirectionalIterator first, TBidirectionalIterator last) {
	return Detail::Algorithm::reverse(first, last, typename IteratorTraits<TBidirectionalIterator>::Category{});
}

} // namespace Algorithm

} // namespace BR
