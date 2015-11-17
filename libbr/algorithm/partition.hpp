/**
 * @file
 * @brief partition
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

namespace Detail {
namespace Algorithm {

template< typename TForwardIterator, typename TUnaryPredicate >
auto partition(TForwardIterator first, TForwardIterator last, TUnaryPredicate & predicate, ForwardTraversalTag) -> TForwardIterator {
	for (;; ++first) {
		if (first == last) {
			return first;
		}
		if (!predicate(*first)) {
			break;
		}
	}
	for (auto i = first; ++i != last;) {
		if (predicate(*i)) {
			swap(*first, *i);
			++first;
		}
	}
	return first;
}

template< typename TBidirectionalIterator, typename TUnaryPredicate >
auto partition(TBidirectionalIterator first, TBidirectionalIterator last, TUnaryPredicate & predicate, BidirectionalTraversalTag) -> TBidirectionalIterator {
	for (;; ++first) {
		for (;; ++first) {
			if (first == last) {
				return first;
			}
			if (!predicate(*first)) {
				break;
			}
		}
		do {
			if (first == --last) {
				return first;
			}
		} while (!predicate(*last));
		swap(*first, *last);
	}
}

} // namespace Algorithm
} // namespace Detail

template< typename TForwardIterator, typename TUnaryPredicate >
inline auto partition(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	return Detail::Algorithm::partition(first, last, predicate, IteratorTraits<TForwardIterator>::category());
}

} // namespace BR
