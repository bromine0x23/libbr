/**
 * @file
 * @brief sort
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/iterators/advance.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/type_traits/has_trivial_copy_constructor.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Sorts a range into ascending order.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @tparam TComparator Type of \p comparator.
 * @param[in,out] first,last The range of elements to sort.
 * @param[in] comparator Comparison function object which returns <code>​true</code>
 *                       if the first argument is less than (i.e. is ordered before) the second.
 */
template< typename TRandomAccessIterator, typename TComparator >
void sort(
	TRandomAccessIterator first, TRandomAccessIterator last,
	TComparator && comparator
);

/**
 * @brief Sorts a range into ascending order.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @param[in,out] first,last The range of elements to sort.
 */
template< typename TRandomAccessIterator >
void sort(
	TRandomAccessIterator first, TRandomAccessIterator last
);

} // namespace Algorithms



namespace _::Algorithms {

template< typename TForwardIterator, typename TComparator >
inline auto sort3(TForwardIterator a, TForwardIterator b, TForwardIterator c, TComparator && comparator) -> Size {
	Size swap_count = 0;
	if (forward<TComparator>(comparator)(*b, *a)) {
		if (forward<TComparator>(comparator)(*c, *b)) {
			swap(*a, *c);
			swap_count = 1;
			// cba
		} else if (forward<TComparator>(comparator)(*c, *a)) {
			swap(*a, *b);
			swap(*b, *c);
			swap_count = 2;
			// bca
		} else {
			swap(*a, *b);
			swap_count = 1;
			// bac
		}
	} else if (forward<TComparator>(comparator)(*c, *b)) {
		if (forward<TComparator>(comparator)(*c, *a)) {
			swap(*b, *c);
			swap(*a, *b);
			swap_count = 2;
			// cab
		} else {
			swap(*b, *c);
			swap_count = 1;
			// acb
		}
	} else {
		// abc
	}
	return swap_count;
}

template< typename TForwardIterator, typename TComparator >
inline auto sort4(TForwardIterator a, TForwardIterator b, TForwardIterator c, TForwardIterator d, TComparator && comparator) -> Size {
	auto swap_count = sort3(a, b, c, forward<TComparator>(comparator));
	if (forward<TComparator>(comparator)(*d, *c)) {
		swap(*c, *d);
		++swap_count;
		if (forward<TComparator>(comparator)(*c, *b)) {
			swap(*b, *c);
			++swap_count;
			if (forward<TComparator>(comparator)(*b, *a)) {
				swap(*a, *b);
				++swap_count;
			}
		}
	}
	return swap_count;
}

template< typename TForwardIterator, typename TComparator >
inline auto sort5(TForwardIterator a, TForwardIterator b, TForwardIterator c, TForwardIterator d, TForwardIterator e, TComparator && comparator) -> Size {
	auto swap_count = sort4(a, b, c, d, forward<TComparator>(comparator));
	if (forward<TComparator>(comparator)(*e, *d)) {
		swap(*d, *e);
		++swap_count;
		if (forward<TComparator>(comparator)(*d, *c)) {
			swap(*c, *d);
			++swap_count;
			if (forward<TComparator>(comparator)(*c, *b)) {
				swap(*b, *c);
				++swap_count;
				if (forward<TComparator>(comparator)(*b, *a)) {
					swap(*a, *b);
					++swap_count;
				}
			}
		}
	}
	return swap_count;
}

template< typename TRandomAccessIterator, typename TComparator >
inline auto sort_small(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> bool {
	switch (last - first) {
		case 0:
		case 1: {
			return true;
		}
		case 2: {
			if (forward<TComparator>(comparator)(*--last, *first)) {
				swap(*first, *last);
			}
			return true;
		}
		case 3: {
			sort3(first, first + 1, --last, forward<TComparator>(comparator));
			return true;
		}
		case 4: {
			sort4(first, first + 1, first + 2, --last, forward<TComparator>(comparator));
			return true;
		}
		case 5: {
			sort5(first, first + 1, first + 2, first + 3, --last, forward<TComparator>(comparator));
			return true;
		}
		default: {
			return false;
		}
	}
}

template< typename TRandomAccessIterator, typename TComparator >
inline auto insertion_sort_incomplete(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> bool {
	constexpr auto move_threshold = 8;
	if (!sort_small(first, last, forward<TComparator>(comparator))) {
		auto j = first + 2;
		sort3(first, first + 1, j, forward<TComparator>(comparator));
		auto move_count = 0;
		for (auto i = j + 1; i != last; j = i, (void)++i) {
			if (forward<TComparator>(comparator)(*i, *j)) {
				auto t = transfer(*i);
				auto k = j;
				j = i;
				do {
					*j = transfer(*k);
					j = k;
				} while (j != first && forward<TComparator>(comparator)(t, *--k));
				*j = transfer(t);
				if (++move_count == move_threshold) {
					return ++i == last;
				}
			}
		}
	}
	return true;
}

template< typename TRandomAccessIterator, typename TComparator >
void introsort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	using Difference = typename IteratorTraits<TRandomAccessIterator>::Difference;
	using Element    = typename IteratorTraits<TRandomAccessIterator>::Element;
	constexpr Difference insertion_sort_threshold = has_trivial_copy_constructor<Element> && has_trivial_copy_assignment<Element> ? 30 : 6;
	constexpr Difference pivot_select_threshold = 1000;
	for (;;) {
		RESTART:

		if (sort_small(first, last, forward<TComparator>(comparator))) {
			return;
		}
		auto const length = last - first;
		if (length <= insertion_sort_threshold) {
			// insertion sort
			auto j = first + 2;
			sort3(first, first + 1, j, forward<TComparator>(comparator));
			for (auto i = j + 1; i != last; ++i) {
				if (forward<TComparator>(comparator)(*i, *j)) {
					auto t = transfer(*i);
					auto k = j;
					j = i;
					do {
						*j = transfer(*k);
						j = k;
					} while (j != first && forward<TComparator>(comparator)(t, *--k));
					*j = transfer(t);
					*j = transfer(t);
				}
				j = i;
			}
			return;
		}

		auto const half_length = length / 2;
		auto middle = first; advance(middle, half_length);
		auto before_last = last; --before_last;

		Size swap_count = 0;
		if (length >= pivot_select_threshold) {
			auto delta = half_length / 2;
			swap_count = sort5(first, first + delta, middle, middle + delta, before_last, forward<TComparator>(comparator));
		} else {
			swap_count = sort3(first, middle, before_last, forward<TComparator>(comparator));
		}

		auto i = first;
		auto j = before_last;
		if (!forward<TComparator>(comparator)(*i, *middle)) {
			for (;;) {
				if (i == --j) {
					++i;
					j = last;
					if (!forward<TComparator>(comparator)(*first, *--j)) {
						for (;; ++i) {
							if (i == j) {
								return;
							}
							if (forward<TComparator>(comparator)(*first, *i)) {
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
					for (;; ++i) {
						for (; !forward<TComparator>(comparator)(*first, *i); ++i) {}
						for (; forward<TComparator>(comparator)(*first, *--j);) {}
						if (i >= j) {
							break;
						}
						swap(*i, *j);
						++swap_count;
					}
					first = i;
					goto RESTART;
				}
				if (forward<TComparator>(comparator)(*j, *middle)) {
					swap(*i, *j);
					++swap_count;
					break;
				}
			}
		}

		if (++i < j) {
			for (;; ++i) {
				for (; forward<TComparator>(comparator)(*i, *middle); ++i) {}
				for (; !forward<TComparator>(comparator)(*--j, *middle);) {}
				if (i > j) {
					break;
				}
				swap(*i, *j);
				++swap_count;
				if (middle == i) {
					middle = j;
				}
			}
		}
		if (i != middle && forward<TComparator>(comparator)(*middle, *i)) {
			swap(*i, *middle);
			++swap_count;
		}
		if (swap_count == 0) {
			bool finished = insertion_sort_incomplete(first, i, forward<TComparator>(comparator));
			if (insertion_sort_incomplete(i + 1, last, forward<TComparator>(comparator))) {
				if (finished) {
					return;
				}
				last = i;
				continue;
			} else {
				if (finished) {
					first = ++i;
					continue;
				}
			}
		}
		if (i - first < last - i) {
			introsort(first, i, forward<TComparator>(comparator));
			first = ++i;
		} else {
			introsort(i + 1, last, forward<TComparator>(comparator));
			last = i;
		}
	}
}

extern template void introsort(NChar  * first, NChar  * last, Less<> && comparator);
extern template void introsort(WChar  * first, WChar  * last, Less<> && comparator);
extern template void introsort(SInt8  * first, SInt8  * last, Less<> && comparator);
extern template void introsort(UInt8  * first, UInt8  * last, Less<> && comparator);
extern template void introsort(SInt16 * first, SInt16 * last, Less<> && comparator);
extern template void introsort(UInt16 * first, UInt16 * last, Less<> && comparator);
extern template void introsort(SInt32 * first, SInt32 * last, Less<> && comparator);
extern template void introsort(UInt32 * first, UInt32 * last, Less<> && comparator);
extern template void introsort(SInt64 * first, SInt64 * last, Less<> && comparator);
extern template void introsort(UInt64 * first, UInt64 * last, Less<> && comparator);
extern template void introsort(SFloat * first, SFloat * last, Less<> && comparator);
extern template void introsort(DFloat * first, DFloat * last, Less<> && comparator);
extern template void introsort(QFloat * first, QFloat * last, Less<> && comparator);

template< typename TRandomAccessIterator, typename TComparator >
inline void sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	introsort(first, last, forward<TComparator>(comparator));
}

} // namespace _::Algorithms

inline namespace Algorithms {

template< typename TRandomAccessIterator, typename TComparator >
inline void sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	_::Algorithms::sort(first, last, forward<TComparator>(comparator));
}

template< typename TRandomAccessIterator >
void sort(TRandomAccessIterator first, TRandomAccessIterator last) {
	sort(first, last, Less<>{});
}

} // namespace Algorithms

} // namespace BR