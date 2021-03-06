/**
 * @file
 * @brief rotate
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/move.hpp>
#include <libbr/algorithms/move_backward.hpp>
#include <libbr/algorithms/swap.hpp>
#include <libbr/math/gcd.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/iterators/next.hpp>
#include <libbr/iterators/prev.hpp>
#include <libbr/type_traits/has_trivial_move_assignment.hpp>
#include <libbr/utility/transfer.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Rotates the order of elements in a range.
 *
 * Swaps the elements in the range \f$ [first, last) \f$ in such a way
 * that the element \p middle becomes the first element of the new range and \f$ middle-1 \f$ becomes the last element.
 * @tparam TForwardIterator Type of \p first, \p middle & \p last which satisfies \em ForwardIterator.
 * @param[in,out] first The beginning of the original range.
 * @param[in,out] middle The element that should appear at the beginning of the rotated range.
 * @param[in,out] last The end of the original range.
 * @return The iterator equal to \f$ first + (last - middle) \f$
 */
template< typename TForwardIterator >
constexpr auto rotate(
	TForwardIterator first,
	TForwardIterator middle,
	TForwardIterator last
) -> TForwardIterator;

} // namespace Algorithms



namespace _::Algorithms {

template< typename TForwardIterator >
constexpr inline auto rotate_left(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	auto tmp = transfer(*first);
	auto before_last = move(next(first), last, first);
	*before_last = transfer(tmp);
	return before_last;
}

template< typename TBidirectionalIterator >
constexpr inline auto rotate_right(TBidirectionalIterator first, TBidirectionalIterator last) -> TBidirectionalIterator {
	auto before_last = prev(last);
	auto tmp = transfer(*before_last);
	auto after_first = move_backward(first, before_last, last);
	*first = transfer(tmp);
	return after_first;
}

template< typename TForwardIterator >
constexpr auto rotate_forward(TForwardIterator first, TForwardIterator middle, TForwardIterator last) -> TForwardIterator {
	using BR::swap;
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
constexpr auto rotate_gcd(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last) -> TRandomAccessIterator {
	auto const length0 = middle - first;
	auto const length1 = last - middle;
	if (length0 == length1) {
		swap(first, middle, middle);
		return middle;
	}
	auto const g = gcd(length0, length1);
	for (auto p = first + g; p != first;) {
		auto t = transfer(*--p);
		auto p1 = p;
		auto p2 = p1 + length0;
		do {
			*p1 = transfer(*p2);
			p1 = p2;
			auto const d = last - p2;
			if (length0 < d) {
				p2 += length0;
			} else {
				p2 = first + (length0 - d);
			}
		} while (p2 != p);
		*p1 = transfer(t);
	}
	return first + length1;
}

template< typename TForwardIterator >
constexpr inline auto rotate(TForwardIterator first, TForwardIterator middle, TForwardIterator last, ForwardTraversalTag) -> TForwardIterator {
	if constexpr (has_trivial_move_assignment< typename IteratorTraits<TForwardIterator>::Element >) {
		if (next(first) == middle) {
			return rotate_left(first, last);
		}
	}
	return rotate_forward(first, middle, last);
}

template< typename TBidirectionalIterator >
constexpr inline auto rotate(TBidirectionalIterator first, TBidirectionalIterator middle, TBidirectionalIterator last, BidirectionalTraversalTag) -> TBidirectionalIterator {
	if constexpr (has_trivial_move_assignment< typename IteratorTraits<TBidirectionalIterator>::Element >) {
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
constexpr inline auto rotate(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last, RandomAccessTraversalTag) -> TRandomAccessIterator {
	if constexpr (has_trivial_move_assignment< typename IteratorTraits<TRandomAccessIterator>::Element >) {
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

template< typename TForwardIterator >
constexpr inline auto rotate(TForwardIterator first, TForwardIterator middle, TForwardIterator last) -> TForwardIterator {
	if (first == middle) {
		return last;
	}
	if (middle == last) {
		return first;
	}
	return rotate(first, middle, last, IteratorTraits<TForwardIterator>::iterator_category());
}

} // namespace _::Algorithms

inline namespace Algorithms {

template< typename TForwardIterator >
constexpr inline auto rotate(TForwardIterator first, TForwardIterator middle, TForwardIterator last) -> TForwardIterator {
	return _::Algorithms::rotate(first, middle, last);
}

} // namespace Algorithms

} // namespace BR
