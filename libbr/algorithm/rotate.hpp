/**
 * @file
 * @brief rotate
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/move.hpp>
#include <libbr/algorithm/move_backward.hpp>
#include <libbr/algorithm/swap.hpp>
#include <libbr/math/gcd.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/iterator/prev.hpp>
#include <libbr/type_traits/has_trivial_move_assignment.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename TForwardIterator >
inline auto rotate(TForwardIterator first, TForwardIterator middle, TForwardIterator last) -> TForwardIterator;

namespace Detail {
namespace Algorithm {

template< typename TForwardIterator >
inline auto rotate_left(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	auto tmp = move(*first);
	auto before_last = move(next(first), last, first);
	*before_last = move(tmp);
	return before_last;
}

template< typename TBidirectionalIterator >
inline auto rotate_right(TBidirectionalIterator first, TBidirectionalIterator last) -> TBidirectionalIterator {
	auto before_last = prev(last);
	auto tmp = move(*before_last);
	auto after_first = move_backward(first, before_last, last);
	*first = move(tmp);
	return after_first;
}

template< typename TForwardIterator >
auto rotate_forward(TForwardIterator first, TForwardIterator middle, TForwardIterator last) -> TForwardIterator {
	for (auto i = middle;;) {
		swap(*first, *i);
		++first;
		if (++i == last) {
			break;
		}
		if (first == middle) {
			middle = i;
		}
	}
	auto result = first;
	if (first != middle) {
		for (auto i = middle;;) {
			swap(*first, *i);
			++first;
			if (++i == last) {
				if (first == middle) {
					break;
				}
				i = middle;
			} else if (first == middle) {
				middle = i;
			}
		}
	}
	return result;
}

template< typename TRandomAccessIterator >
auto rotate_gcd(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last) -> TRandomAccessIterator {
	auto const length0 = middle - first;
	auto const length1 = last - middle;
	if (length0 == length1) {
		swap(first, middle, middle);
		return middle;
	}
	auto const g = gcd(length0, length1);
	for (auto p = first + g; p != first;) {
		auto t = move(*--p);
		auto p1 = p;
		auto p2 = p1 + length0;
		do {
			*p1 = move(*p2);
			p1 = p2;
			auto const d = last - p2;
			if (length0 < d) {
				p2 += length0;
			} else {
				p2 = first + (length0 - d);
			}
		} while (p2 != p);
		*p1 = move(t);
	}
	return first + length1;
}

template< typename TForwardIterator >
inline auto rotate(TForwardIterator first, TForwardIterator middle, TForwardIterator last, ForwardTraversalTag) -> TForwardIterator {
	if (HasTrivialMoveAssignment< typename IteratorTraits<TForwardIterator>::Element >{}) {
		if (next(first) == middle) {
			return rotate_left(first, last);
		}
	}
	return rotate_forward(first, middle, last);
}

template< typename TBidirectionalIterator >
inline auto rotate(TBidirectionalIterator first, TBidirectionalIterator middle, TBidirectionalIterator last, BidirectionalTraversalTag) -> TBidirectionalIterator {
	if (HasTrivialMoveAssignment< typename IteratorTraits<TBidirectionalIterator>::Element >{}) {
		if (next(first) == middle) {
			return rotate_left(first, last);
		}
		if (next(middle) == last) {
			return rotate_right(first, last);
		}
	}
	return rotate_forward(first, middle, last);
}

template< typename TRandomAccessIterator >
inline auto rotate(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last, RandomAccessTraversalTag) -> TRandomAccessIterator {
	if (HasTrivialMoveAssignment< typename IteratorTraits<TRandomAccessIterator>::Element >{}) {
		if (next(first) == middle) {
			return rotate_left(first, last);
		}
		if (next(middle) == last) {
			return rotate_right(first, last);
		}
		return rotate_gcd(first, middle, last);
	}
	return rotate_forward(first, middle, last);
}

} // namespace Algorithm
} // namespace Detail

template< typename TForwardIterator >
auto rotate(TForwardIterator first, TForwardIterator middle, TForwardIterator last) -> TForwardIterator {
	if (first == middle) {
		return last;
	}
	if (middle == last) {
		return first;
	}
	return Detail::Algorithm::rotate(first, middle, last, IteratorTraits<TForwardIterator>::category());
}

} // namespace BR
