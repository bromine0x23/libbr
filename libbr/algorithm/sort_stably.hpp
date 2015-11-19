/**
 * @file
 * @brief sort_stably
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/merge_inplace.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/type_traits/has_trivial_copy_assign.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TRandomAccessIterator, typename TComparator >
inline void sort_stably(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator);

template< typename TRandomAccessIterator >
inline void sort_stably(TRandomAccessIterator first, TRandomAccessIterator last) {
	return sort_stably(first, last, Less<>());
}

namespace Detail {
namespace Algorithm {

template< typename TRandomAccessIterator, typename TDifference, typename TComparator >
void sort_stably(TRandomAccessIterator first, TRandomAccessIterator last, TDifference length, TComparator & comparator) {
	constexpr auto switch_threshold = 128;

	switch (length) {
		case 0:
		case 1: {
			break;
		}
		case 2: {
			if (comparator(*--last, *first)) {
				swap(*first, *last);
			}
			break;
		}
		default: {
			if (HasTrivialCopyAssign< typename IteratorTraits<TRandomAccessIterator>::Element >() && length < switch_threshold) {
				// Insertion sort
				if (first != last) {
					for (auto i = first; ++i != last; ) {
						auto j = i;
						auto t = move(*j);
						for (auto k = i; k != first && comparator(t, *--k); --j) {
							*j = move(*k);
						}
						*j = move(t);
					}
				}
			} else {
				auto const length0 = length / 2;
				auto const length1 = length - length0;
				auto middle = first + length0;

				sort_stably(first, middle, length0, comparator);
				sort_stably(middle, last, length1, comparator);
				merge_inplace(first, middle, last, length0, length1, comparator);
			}
			break;
		}
	}
}

} // namespace Algorithm
} // namespace Detail

template< typename TRandomAccessIterator, typename TComparator >
void sort_stably(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	Detail::Algorithm::sort_stably(first, last, last - first, comparator);
}

} // namespace BR
