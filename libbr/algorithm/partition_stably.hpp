/**
 * @file
 * @brief partition_stably
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/rotate.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::stable_partition
 * @tparam TForwardIterator
 * @tparam TUnaryPredicate
 * @param[in,out] first,last
 * @param[in] predicate
 * @return
 */
template< typename TForwardIterator, typename TUnaryPredicate >
auto partition_stably(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

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
	BR_ASSERT(!forward<TUnaryPredicate>(predicate)(*first));
	BR_ASSERT(forward<TUnaryPredicate>(predicate)(*last));
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
			auto const middle = next(first, half_length);

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

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TForwardIterator, typename TUnaryPredicate >
inline auto partition_stably(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	return Detail::Algorithm::partition_stably(first, last, forward<TUnaryPredicate>(predicate), typename IteratorTraits<TForwardIterator>::Category{});
}

} // namespace Algorithm

} // namespace BR
