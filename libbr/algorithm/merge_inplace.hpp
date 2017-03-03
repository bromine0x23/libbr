/**
 * @file
 * @brief merge_inplace
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/lower_bound.hpp>
#include <libbr/algorithm/rotate.hpp>
#include <libbr/algorithm/upper_bound.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::inplace_merge
 * @tparam TBidirectionalIterator
 * @tparam TComparator
 * @param[in,out] first,middle,last
 * @param[in] comparator
 */
template< typename TBidirectionalIterator, typename TComparator >
void merge_inplace(TBidirectionalIterator first, TBidirectionalIterator middle, TBidirectionalIterator last, TComparator && comparator);

/**
 * @brief like std::inplace_merge
 * @tparam TBidirectionalIterator
 * @param[in,out] first,middle,last
 */
template< typename TBidirectionalIterator >
void merge_inplace(TBidirectionalIterator first, TBidirectionalIterator middle, TBidirectionalIterator last);

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TBidirectionalIterator, typename TDifference, typename TComparator >
void merge_inplace(TBidirectionalIterator first, TBidirectionalIterator middle, TBidirectionalIterator last, TDifference length0, TDifference length1, TComparator && comparator) {
	using BR::rotate;
	for (;;) {
		if (length1 == 0) {
			return;
		}
		for (;; ++first, (void)--length0) {
			if (length0 == 0) {
				return;
			}
			if (forward<TComparator>(comparator)(*middle, *first)) {
				break;
			}
		}

		TBidirectionalIterator m0, m1;
		TDifference l00, l10;

		if (length0 < length1) {
			l10 = length1 / 2;
			m1 = next(middle, l10);
			m0 = upper_bound(first, middle, *m1, forward<TComparator>(comparator));
			l00 = distance(first, m0);
		} else {
			if (length0 == 1) {
				swap(*first, *middle);
				return;
			}
			l00 = length0 / 2;
			m0 = next(first, l00);
			m1 = lower_bound(middle, last, *m0, forward<TComparator>(comparator));
			l10 = distance(middle, m1);
		}

		auto l01 = length0 - l00, l11 = length1 - l10;

		middle = rotate(m0, middle, m1);

		if (l00 + l10 < l01 + l11) {
			merge_inplace(first, m0, middle, l00, l10, forward<TComparator>(comparator));
			first = middle;
			middle = m1;
			length0 = l01;
			length1 = l11;
		} else {
			merge_inplace(middle, m1, last, l01, l11, forward<TComparator>(comparator));
			last = middle;
			middle = m0;
			length0 = l00;
			length1 = l10;
		}
	}
};

} // namespace Algorithm
} // namespace Detail


inline namespace Algorithm {

template< typename TBidirectionalIterator, typename TComparator >
inline void merge_inplace(TBidirectionalIterator first, TBidirectionalIterator middle, TBidirectionalIterator last, TComparator && comparator) {
	return Detail::Algorithm::merge_inplace(first, middle, last, forward<TComparator>(comparator));
}

template< typename TBidirectionalIterator >
inline void merge_inplace(TBidirectionalIterator first, TBidirectionalIterator middle, TBidirectionalIterator last) {
	return merge_inplace(first, middle, last, Less<void>());
}

} // namespace Algorithm

} // namespace BR
