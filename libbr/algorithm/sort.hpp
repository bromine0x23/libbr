/**
 * @file
 * @brief sort
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/has_trivial_copy_assign.hpp>
#include <libbr/type_traits/has_trivial_copy_constructor.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

namespace Detail {
namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
inline auto sort3(TForwardIterator a, TForwardIterator b, TForwardIterator c, TComparator & comparator) -> UInt32 {
	UInt32 swap_count = 0;
	if (comparator(*b, *a)) {
		if (comparator(*c, *b)) {
			swap(*a, *c);
			swap_count = 1;
			// cba
		} else if (comparator(*c, *a)) {
			swap(*a, *b);
			swap(*b, *c);
			swap_count = 2;
			// bca
		} else {
			swap(*a, *b);
			swap_count = 1;
			// bac
		}
	} else if (comparator(*c, *b)) {
		if (comparator(*c, *a)) {
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
inline auto sort4(TForwardIterator a, TForwardIterator b, TForwardIterator c, TForwardIterator d, TComparator & comparator) -> UInt32 {
	auto swap_count = sort3(a, b, c, comparator);
	if (comparator(*d, *c)) {
		swap(*c, *d);
		++swap_count;
		if (comparator(*c, *b)) {
			swap(*b, *c);
			++swap_count;
			if (comparator(*b, *a)) {
				swap(*a, *b);
				++swap_count;
			}
		}
	}
	return swap_count;
}

template< typename TForwardIterator, typename TComparator >
inline auto sort5(TForwardIterator a, TForwardIterator b, TForwardIterator c, TForwardIterator d, TForwardIterator e, TComparator & comparator) -> UInt32 {
	auto swap_count = sort4(a, b, c, d, comparator);
	if (comparator(*e, *d)) {
		swap(*d, *e);
		++swap_count;
		if (comparator(*d, *c)) {
			swap(*c, *d);
			++swap_count;
			if (comparator(*c, *b)) {
				swap(*b, *c);
				++swap_count;
				if (comparator(*b, *a)) {
					swap(*a, *b);
					++swap_count;
				}
			}
		}
	}
	return swap_count;
}

template< typename TRandomAccessIterator, typename TComparator >
inline auto sort_small(TRandomAccessIterator first, TRandomAccessIterator last, TComparator & comparator) -> bool {
	switch (last - first) {
		case 0:
		case 1: {
			return true;
		}
		case 2: {
			if (comparator(*--last, *first)) {
				swap(*first, *last);
			}
			return true;
		}
		case 3: {
			sort3(first, first + 1, --last, comparator);
			return true;
		}
		case 4: {
			sort4(first, first + 1, first + 2, --last, comparator);
			return true;
		}
		case 5: {
			sort5(first, first + 1, first + 2, first + 3, --last, comparator);
			return true;
		}
		default: {
			return false;
		}
	}
}

template< typename TRandomAccessIterator, typename TComparator >
inline auto insertion_sort_incomplete(TRandomAccessIterator first, TRandomAccessIterator last, TComparator & comparator) -> bool {
	constexpr auto move_threshold = 8;
	if (!sort_small(first, last, comparator)) {
		auto j = first + 2;
		sort3(first, first + 1, j, comparator);
		auto move_count = 0;
		for (auto i = j + 1; i != last; j = i, (void)++i) {
			if (comparator(*i, *j)) {
				auto t = move(*i);
				auto k = j;
				j = i;
				do {
					*j = move(*k);
					j = k;
				} while (j != first && comparator(t, *--k));
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
void sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator & comparator) {
	using Difference = typename IteratorTraits<TRandomAccessIterator>::Difference;
	using Element = typename IteratorTraits<TRandomAccessIterator>::Element;
	constexpr Difference insertion_sort_threshold = BooleanAnd< HasTrivialCopyConstructor<Element>, HasTrivialCopyAssign<Element> >() ? 30 : 6;
	constexpr Difference pivot_select_threshold = 1000;
	for (;;) {
		RESTART:

		if (sort_small(first, last, comparator)) {
			return;
		}
		auto length = last - first;
		if (length <= insertion_sort_threshold) {
			// insertion sort
			auto j = first + 2;
			sort3(first, first + 1, j, comparator);
			for (auto i = j + 1; i != last; ++i) {
				if (comparator(*i, *j)) {
					auto t = move(*i);
					auto k = j;
					j = i;
					do {
						*j = move(*k);
						j = k;
					} while (j != first && comparator(t, *--k));
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
			swap_count = sort5(first, first + delta, middle, middle + delta, before_last, comparator);
		} else {
			swap_count = sort3(first, middle, before_last, comparator);
		}

		auto i = first;
		auto j = before_last;
		if (!comparator(*i, *middle)) {
			for (;;) {
				if (i == --j) {
					++i;
					j = last;
					if (!comparator(*first, *--j)) {
						for (;; ++i) {
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
					for (;; ++i) {
						for (; !comparator(*first, *i); ++i) {}
						for (; comparator(*first, *--j);) {}
						if (i >= j) {
							break;
						}
						swap(*i, *j);
						++swap_count;
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
			for (;; ++i) {
				for (; comparator(*i, *middle); ++i) {}
				for (; !comparator(*--j, *middle);) {}
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
		if (i != middle && comparator(*middle, *i)) {
			swap(*i, *middle);
			++swap_count;
		}
		if (swap_count == 0) {
			bool finished = insertion_sort_incomplete(first, i, comparator);
			if (insertion_sort_incomplete(i + 1, last, comparator)) {
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
			Algorithm::sort(first, i, comparator);
			first = ++i;
		} else {
			Algorithm::sort(i + 1, last, comparator);
			last = i;
		}
	}
}

} // namespace Algorithm
} // namespace Detail

/**
 * @brief 排序算法
 * @param[in,out] first,last 待排序区间
 * @param[in] comparator 比较器
 */
template< typename TRandomAccessIterator, typename TComparator >
inline void sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	Detail::Algorithm::sort(first, last, comparator);
}

/**
 * @brief 排序算法(使用BR::Less<>作比较器)
 * @param[in,out] first,last 待排序区间
 */
template< typename TRandomAccessIterator >
inline void sort(TRandomAccessIterator first, TRandomAccessIterator last)  {
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

extern template void sort(SFloat * first, SFloat * last, Less<SFloat> && comparator);

extern template void sort(DFloat * first, DFloat * last, Less<DFloat> && comparator);

extern template void sort(QFloat * first, QFloat * last, Less<QFloat> && comparator);

} // namespace BR