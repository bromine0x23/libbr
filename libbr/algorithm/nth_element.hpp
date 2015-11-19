/**
 * @file
 * @brief nth_element
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/min_element.hpp>
#include <libbr/algorithm/sort.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TRandomAccessIterator, typename TComparator >
inline void nth_element(TRandomAccessIterator first, TRandomAccessIterator nth, TRandomAccessIterator last, TComparator && comparator);

template< typename TRandomAccessIterator >
inline void nth_element(TRandomAccessIterator first, TRandomAccessIterator nth, TRandomAccessIterator last) {
	nth_element(first, nth, last, Less<void>());
}

namespace Detail {
namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
void nth_element(TRandomAccessIterator first, TRandomAccessIterator nth, TRandomAccessIterator last, TComparator & comparator) {
	constexpr auto selection_sort_threshold = 7;
	for (;;) {
		RESTART:
		if (nth == last) {
			return;
		}
		auto length = last - first;
		switch (length) {
			case 0:
			case 1: {
				return;
			}
			case 2: {
				if (comparator(*--last, *first)) {
					swap(*first, *last);
				}
				return;
			}
			case 3: {
				auto middle = first;
				sort3(first, ++middle, --last, comparator);
				return;
			}
		}
		if (length <= selection_sort_threshold) {
			// selection sort
			auto before_last = last;
			for (--before_last; first != before_last; ++first) {
				auto i = min_element(first, last, comparator);
				if (i != first) {
					swap(*first, *i);
				}
			}
			return;
		}

		auto middle = first + length / 2;
		auto before_last = last;
		auto swap_count = sort3(first, middle, --before_last, comparator);

		auto i = first;
		auto j = before_last;

		if (!comparator(*i, *middle)) {
			for (; ;) {
				if (i == --j) {
					++i;
					j = last;
					if (!comparator(*first, *--j)) {
						for (; ; ++i) {
							if (i == j) {
								return;
							}
							if (comparator(*first, *i)) {
								swap(*i, *j);
								++swap_count;
								++i;
								break;
							}
						}
					}
					if (i == j) {
						return;
					}
					for (; ; ++i) {
						for (; !comparator(*first, *i); ++i) { }
						for (; comparator(*first, *--j);) { }
						if (i >= j) {
							break;
						}
						swap(*i, *j);
						++swap_count;
					}
					if (nth < i) {
						return;
					}
					first = i;
					goto RESTART;
				}
				if (comparator(*j, *middle)) {
					swap(*i, *j);
					++swap_count;
					break;
				}
			}
		}

		if (++i < j) {
			for (; ; ++i) {
				for (; comparator(*i, *middle); ++i) { }
				for (; !comparator(*--j, *middle);) { }
				if (i >= j) {
					break;
				}
				swap(*i, *j);
				++swap_count;
				if (middle == i) {
					middle = j;
				}
			}
		}

		if (i != middle && comparator(*middle, *i)) {
			swap(*i, *middle);
			++swap_count;
		}

		if (nth == i) {
			return;
		}

		if (swap_count == 0) {
			if (nth < i) {
				for (j = middle = first; ++j != i; middle = j) {
					if (comparator(*j, *middle)) {
						goto NOT_SORTED;
					}
				}
				return;
			} else {
				for (j = middle = i; ++j != last; middle = j) {
					if (comparator(*j, *middle)) {
						goto NOT_SORTED;
					}
				}
				return;
			}
		}
		NOT_SORTED:
		if (nth < i) {
			last = i;
		} else {
			first = ++i;
		}
	}
}

} // namespace Algorithm
} // namespace Detail

template< typename TRandomAccessIterator, typename TComparator >
void nth_element(TRandomAccessIterator first, TRandomAccessIterator nth, TRandomAccessIterator last, TComparator && comparator) {
	Detail::Algorithm::nth_element(first, nth, last, comparator);
}

} // namespace BR