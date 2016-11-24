/**
 * @file
 * @brief next_permutation
 * @author Bromine0x23
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
 * @brief like std::next_permutation
 * @tparam TBidirectionalIterator
 * @tparam TComparator
 * @param[in,out] first,last
 * @param[in] comparator
 * @return
 */
template< typename TBidirectionalIterator, typename TComparator >
auto next_permutation(TBidirectionalIterator first, TBidirectionalIterator last, TComparator && comparator) -> bool;

/**
 * @brief like std::next_permutation
 * @tparam TBidirectionalIterator
 * @param[in,out] first,last
 * @return
 */
template< typename TBidirectionalIterator >
auto next_permutation(TBidirectionalIterator first, TBidirectionalIterator last) -> bool;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TBidirectionalIterator, typename TComparator >
auto next_permutation(TBidirectionalIterator first, TBidirectionalIterator last, TComparator && comparator) -> bool {
	auto i = last;
	if (first == last || first == --i) {
		return false;
	}
	for (;;) {
		auto after_i = i;
		if (forward<TComparator>(comparator)(*--i, *after_i)) {
			auto j = last;
			for (; !forward<TComparator>(comparator)(*i, *--j); ) {}
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
inline auto next_permutation(TBidirectionalIterator first, TBidirectionalIterator last) -> bool {
	return next_permutation(first, last, Less<void>());
}

} // namespace Algorithm

} // namespace BR
