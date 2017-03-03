/**
 * @file
 * @brief prev_permutation
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/reverse.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Generates the next smaller lexicographic permutation of a range of elements
 * @tparam TBidirectionalIterator Type of \p first0 & \p last0 which satisfies \em BidirectionalIterator.
 * @tparam TComparator Type of \p comparator
 * @param[in,out] first,last The range of elements to permute.
 * @param[in] comparator Comparison function object which returns ​<code>true</code> if the first argument is less than the second.
 * @retval true The new permutation precedes the old in lexicographical order.
 * @retval false The first permutation was reached and the range was reset to the last permutation.
 */
template< typename TBidirectionalIterator, typename TComparator >
auto prev_permutation(
	TBidirectionalIterator first, TBidirectionalIterator last,
	TComparator && comparator
) -> Boolean;

/**
 * @brief Generates the next smaller lexicographic permutation of a range of elements
 * @tparam TBidirectionalIterator Type of \p first0 & \p last0 which satisfies \em BidirectionalIterator.
 * @param[in,out] first,last The range of elements to permute.
 * @retval true The new permutation precedes the old in lexicographical order.
 * @retval false The first permutation was reached and the range was reset to the last permutation.
 */
template< typename TBidirectionalIterator >
auto prev_permutation(
	TBidirectionalIterator first, TBidirectionalIterator last
) -> Boolean;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TBidirectionalIterator, typename TComparator >
auto prev_permutation(TBidirectionalIterator first, TBidirectionalIterator last, TComparator && comparator) -> Boolean {
	auto i = last;
	if (first == last || first == --i) {
		return false;
	}
	for (;;) {
		auto after_i = i;
		if (forward<TComparator>(comparator)(*after_i, *--i)) {
			auto j = last;
			for (; !forward<TComparator>(comparator)(*--j, *i);) {}
			swap(*i, *j);
			reverse(after_i, last);
			return true;
		}
		if (i == first) {
			reverse(first, last);
			return false;
		}
	}
}

template< typename TBidirectionalIterator >
inline auto prev_permutation(TBidirectionalIterator first, TBidirectionalIterator last) -> Boolean {
	return prev_permutation(first, last, Less<void>());
}

} // namespace Algorithm

} // namespace BR
