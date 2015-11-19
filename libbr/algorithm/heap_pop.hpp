/**
 * @file
 * @brief heap_pop
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename TRandomAccessIterator, typename TComparator >
inline void heap_pop(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator);

template< typename TRandomAccessIterator >
inline void heap_pop(TRandomAccessIterator first, TRandomAccessIterator last) {
	heap_pop(first, last, Less<>());
}

namespace Detail {
namespace Algorithm {

template< typename TRandomAccessIterator, typename TDifference, typename TComparator >
void heap_shift_down(TRandomAccessIterator first, TRandomAccessIterator last, TDifference length, TRandomAccessIterator start, TComparator & comparator) {
	auto child = start - first;
	if (length < 2 || (length - 2) / 2 < child) {
		return;
	}

	child = 2 * child + 1;
	auto child_i = first + child;

	if ((child + 1) < length && comparator(*child_i, *(child_i + 1))) {
		++child_i;
		++child;
	}

	if (comparator(*child_i, *start)) {
		return;
	}

	auto top = move(*start);
	do {
		*start = move(*child_i);
		start = child_i;

		if ((length - 2) / 2 < child) {
			break;
		}

		child = 2 * child + 1;
		child_i = first + child;

		if ((child + 1) < length && comparator(*child_i, *(child_i + 1))) {
			++child_i;
			++child;
		}

	} while (!comparator(*child_i, top));
	*start = move(top);
}

} // namespace Algorithm
} // namespace Detail

template< typename TRandomAccessIterator, typename TComparator >
void heap_pop(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	auto length = last - first;
	if (length > 1) {
		swap(*first, *--last);
		heap_shift_down(first, last, length - 1, first, comparator);
	}
}

} // namespace BR
