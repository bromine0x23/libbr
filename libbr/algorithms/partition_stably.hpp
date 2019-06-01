/**
 * @file
 * @brief partition_stably
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/rotate.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/iterators/distance.hpp>
#include <libbr/iterators/next.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Divides elements into two groups while preserving their relative order.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @param[in,out] first,last The range of elements to reorder.
 * @param[in] predicate Unary predicate which returns ​<code>true</code> if the element should be ordered before other elements.
 * @return Iterator to the first element of the second group.
 */
template< typename TForwardIterator, typename TUnaryPredicate >
auto partition_stably(
	TForwardIterator first, TForwardIterator last,
	TUnaryPredicate && predicate
) -> TForwardIterator;

} // namespace Algorithms



namespace _ {
namespace Algorithms {

template< typename TForwardIterator, typename TDistance, typename TUnaryPredicate >
auto partition_stably(TForwardIterator first, TForwardIterator last, TDistance length, TUnaryPredicate && predicate, ForwardTraversalTag) -> TForwardIterator {
	BR_ASSERT(!forward<TUnaryPredicate>(predicate)(*first));
	BR_ASSERT(length >= 1);
	switch (length) {
		case 1: {
			return first;
		}
		case 2: {
			auto middle = first;
			if (forward<TUnaryPredicate>(predicate)(*++middle)) {
				swap(*first, *middle);
				return middle;
			}
			return first;
		}
		default: {
			TDistance const half_length = length / 2;
			auto const middle = next(first, half_length);

			auto first_end = middle;
			auto first_false = partition_stably(first, first_end, half_length, forward<TUnaryPredicate>(predicate), ForwardTraversalTag{});

			TDistance second_length = length - half_length;
			auto second_start = first_end;
			auto second_false = last;
			for (; forward<TUnaryPredicate>(predicate)(*second_start);) {
				if (++second_start == last) {
					goto SECOND_HALF_DONE;
				}
				--second_length;
			}
			second_false = partition_stably(second_start, last, second_length, forward<TUnaryPredicate>(predicate), ForwardTraversalTag{});
			SECOND_HALF_DONE:

			return rotate(first_false, middle, second_false);
		}
	}
	BR_ASSERT(false);
}

template< typename TForwardIterator, typename TUnaryPredicate >
auto partition_stably(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate, ForwardTraversalTag) -> TForwardIterator {
	for (;; ++first) {
		if (first == last) {
			return first;
		}
		if (!forward<TUnaryPredicate>(predicate)(*first)) {
			break;
		}
	}
	return partition_stably(first, last, distance(first, last), forward<TUnaryPredicate>(predicate), ForwardTraversalTag{});
}

template< typename TBidirectionalIterator, typename TDistance, typename TUnaryPredicate >
auto partition_stably(TBidirectionalIterator first, TBidirectionalIterator last, TDistance length, TUnaryPredicate && predicate, BidirectionalTraversalTag) -> TBidirectionalIterator {
	using BR::rotate;
	BR_ASSERT(!forward<TUnaryPredicate>(predicate)(*first));
	BR_ASSERT(length >= 1);
	switch (length) {
		case 2: {
			swap(*first, *last);
			return last;
		}
		case 3: {
			auto middle = first;
			if (forward<TUnaryPredicate>(predicate)(*++middle)) {
				swap(*first, *middle);
				swap(*middle, *last);
				return last;
			}
			swap(*middle, *last);
			swap(*first, *middle);
			return middle;
		}
		default: {
			TDistance const half_length = length / 2;
			auto middle = next(first, half_length);

			TDistance first_length = half_length;
			auto first_end = middle;
			auto first_false = first;
			for (; !forward<TUnaryPredicate>(predicate)(*--first_end);) {
				if (first_end == first) {
					goto FIRST_HALF_DONE;
				}
				--first_length;
			}
			first_false = partition_stably(first, first_end, first_length, forward<TUnaryPredicate>(predicate), BidirectionalTraversalTag{});
			FIRST_HALF_DONE:

			auto second_start = middle;
			auto second_false = last;
			++second_false;
			TDistance second_length = length - half_length;
			for (; forward<TUnaryPredicate>(predicate)(*second_start);) {
				if (++second_start == last) {
					goto SECOND_HALF_DONE;
				}
				--second_length;
			}
			second_false = partition_stably(second_start, last, second_length, forward<TUnaryPredicate>(predicate), BidirectionalTraversalTag{});
			SECOND_HALF_DONE:

			return rotate(first_false, middle, second_false);
		}
	}
	BR_ASSERT(false);
}

template< typename TBidirectionalIterator, typename TUnaryPredicate >
auto partition_stably(TBidirectionalIterator first, TBidirectionalIterator last, TUnaryPredicate && predicate, BidirectionalTraversalTag) -> TBidirectionalIterator {
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
	return partition_stably(first, last, distance(first, last) + 1, forward<TUnaryPredicate>(predicate), BidirectionalTraversalTag{});
}

template< typename TForwardIterator, typename TUnaryPredicate >
inline auto partition_stably(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	return partition_stably(first, last, forward<TUnaryPredicate>(predicate), IteratorTraits<TForwardIterator>::iterator_category());
}

} // namespace Algorithms
} // namespace _

inline namespace Algorithms {

template< typename TForwardIterator, typename TUnaryPredicate >
inline auto partition_stably(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	return _::Algorithms::partition_stably(first, last, forward<TUnaryPredicate>(predicate));
}

} // namespace Algorithms

} // namespace BR
