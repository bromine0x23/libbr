/**
 * @file
 * @brief next_permutation
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/reverse.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename TBidirectionalIterator, typename TComparator >
inline auto next_permutation(TBidirectionalIterator first, TBidirectionalIterator last, TComparator && comparator) -> bool;

template< typename TBidirectionalIterator >
inline auto next_permutation(TBidirectionalIterator first, TBidirectionalIterator last) -> bool {
	return next_permutation(first, last, Less<void>());
}

namespace Detail {
namespace Algorithm {

template< typename TBidirectionalIterator, typename TComparator >
auto next_permutation(TBidirectionalIterator first, TBidirectionalIterator last, TComparator & comparator) -> bool {
	auto i = last;
	if (first == last || first == --i) {
		return false;
	}
	for (;;) {
		auto after_i = i;
		if (comparator(*--i, *after_i)) {
			auto j = last;
			for (; !comparator(*i, *--j); ) {}
			swap(*i, *j);
			reverse(after_i, last);
			return true;
		}
		if (i == first) {
			reverse(first, last);
			return false;
		}
	}
}

} // namespace Algorithm
} // namespace Detail

template< typename TBidirectionalIterator, typename TComparator >
inline auto next_permutation(TBidirectionalIterator first, TBidirectionalIterator last, TComparator && comparator) -> bool {
	return Detail::Algorithm::next_permutation(first, last, comparator);
}

} // namespace BR
