/**
 * @file
 * @brief sort
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/type_traits/boolean_and.hpp>
#include <libbr/type_traits/has_trivial_copy_constructor.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Algorithm {

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

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
inline auto sort3(TForwardIterator a, TForwardIterator b, TForwardIterator c, TComparator && comparator) -> UInt32 {
	UInt32 swap_count = 0;
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
inline auto sort4(TForwardIterator a, TForwardIterator b, TForwardIterator c, TForwardIterator d, TComparator && comparator) -> UInt32 {
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
inline auto sort5(TForwardIterator a, TForwardIterator b, TForwardIterator c, TForwardIterator d, TForwardIterator e, TComparator && comparator) -> UInt32 {
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
	using BR::move;
	constexpr auto move_threshold = 8;
	if (!sort_small(first, last, forward<TComparator>(comparator))) {
		auto j = first + 2;
		sort3(first, first + 1, j, forward<TComparator>(comparator));
		auto move_count = 0;
		for (auto i = j + 1; i != last; j = i, (void)++i) {
			if (forward<TComparator>(comparator)(*i, *j)) {
				auto t = move(*i);
				auto k = j;
				j = i;
				do {
					*j = move(*k);
					j = k;
				} while (j != first && forward<TComparator>(comparator)(t, *--k));
				*j = move(t);
				if (++move_count == move_threshold) {
					return ++i == last;
				}
			}
		}
	}
	return true;
}

template< typename TRandomAccessIterator, typename TComparator >
void sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	using BR::move;
	using BR::sort;
	using Difference = typename IteratorTraits<TRandomAccessIterator>::Difference;
	using Element = typename IteratorTraits<TRandomAccessIterator>::Element;
	constexpr Difference insertion_sort_threshold = BooleanAnd< HasTrivialCopyConstructor<Element>, HasTrivialCopyAssignment<Element> >{} ? 30 : 6;
	constexpr Difference pivot_select_threshold = 1000;
	for (;;) {
		RESTART:

		if (sort_small(first, last, forward<TComparator>(comparator))) {
			return;
		}
		auto length = last - first;
		if (length <= insertion_sort_threshold) {
			// insertion sort
			auto j = first + 2;
			sort3(first, first + 1, j, forward<TComparator>(comparator));
			for (auto i = j + 1; i != last; ++i) {
				if (forward<TComparator>(comparator)(*i, *j)) {
					auto t = move(*i);
					auto k = j;
					j = i;
					do {
						*j = move(*k);
						j = k;
					} while (j != first && forward<TComparator>(comparator)(t, *--k));
					*j = move(t);
				}
				j = i;
			}
			return;
		}

		auto const half_length = length / 2;
		auto middle = first; advance(middle, half_length);
		auto before_last = last; --before_last;

		UInt32 swap_count(0);
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
			sort(first, i, forward<TComparator>(comparator));
			first = ++i;
		} else {
			sort(i + 1, last, forward<TComparator>(comparator));
			last = i;
		}
	}
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline void sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	Detail::Algorithm::sort(first, last, forward<TComparator>(comparator));
}

template< typename TRandomAccessIterator >
void sort(TRandomAccessIterator first, TRandomAccessIterator last) {
	sort(first, last, Less<>());
}

extern template void sort(NChar * first, NChar * last, Less<NChar> && comparator);

extern template void sort(WChar * first, WChar * last, Less<WChar> && comparator);

extern template void sort(SInt8 * first, SInt8 * last, Less<SInt8> && comparator);

extern template void sort(UInt8 * first, UInt8 * last, Less<UInt8> && comparator);

extern template void sort(SInt16 * first, SInt16 * last, Less<SInt16> && comparator);

extern template void sort(UInt16 * first, UInt16 * last, Less<UInt16> && comparator);

extern template void sort(SInt32 * first, SInt32 * last, Less<SInt32> && comparator);

extern template void sort(UInt32 * first, UInt32 * last, Less<UInt32> && comparator);

extern template void sort(SInt64 * first, SInt64 * last, Less<SInt64> && comparator);

extern template void sort(UInt64 * first, UInt64 * last, Less<UInt64> && comparator);

extern template void sort(Float32 * first, Float32 * last, Less<Float32> && comparator);

extern template void sort(Float64 * first, Float64 * last, Less<Float64> && comparator);

} // namespace Algorithm

} // namespace BR