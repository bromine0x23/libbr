/**
 * @file
 * @brief partition
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Divides a range of elements into two groups.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @param[in,out] first,last The range of elements to reorder.
 * @param[in] predicate Unary predicate which returns ​<code>true</code> if the element should be ordered before other elements.
 * @return Iterator to the first element of the second group.
 */
template< typename TForwardIterator, typename TUnaryPredicate >
auto partition(
	TForwardIterator first, TForwardIterator last,
	TUnaryPredicate && predicate
) -> TForwardIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TForwardIterator, typename TUnaryPredicate >
auto partition(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate, ForwardTraversalTag) -> TForwardIterator {
	for (;; ++first) {
		if (first == last) {
			return first;
		}
		if (!forward<TUnaryPredicate>(predicate)(*first)) {
			break;
		}
	}
	for (auto i = first; ++i != last;) {
		if (forward<TUnaryPredicate>(predicate)(*i)) {
			swap(*first, *i);
			++first;
		}
	}
	return first;
}

template< typename TBidirectionalIterator, typename TUnaryPredicate >
auto partition(TBidirectionalIterator first, TBidirectionalIterator last, TUnaryPredicate && predicate, BidirectionalTraversalTag) -> TBidirectionalIterator {
	for (;; ++first) {
		for (;; ++first) {
			if (first == last) {
				return first;
			}
			if (!forward<TUnaryPredicate>(predicate)(*first)) {
				break;
			}
		}
		do {
			if (first == --last) {
				return first;
			}
		} while (!forward<TUnaryPredicate>(predicate)(*last));
		swap(*first, *last);
	}
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {
template< typename TForwardIterator, typename TUnaryPredicate >
inline auto partition(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	return Detail::Algorithm::partition(first, last, forward<TUnaryPredicate>(predicate), IteratorTraits<TForwardIterator>::category());
}

} // namespace Algorithm

} // namespace BR
