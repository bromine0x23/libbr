/**
 * @file
 * @brief equal_range
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/lower_bound.hpp>
#include <libbr/algorithm/upper_bound.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::equal_range
 * @tparam TForwardIterator
 * @tparam TValue
 * @tparam TComparator
 * @param[in] first,last
 * @param[in] value
 * @param[in] comparator
 * @return
 */
template< typename TForwardIterator, typename TValue, typename TComparator >
auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator >;

/**
 * @brief like std::equal_range
 * @tparam TForwardIterator
 * @tparam TValue
 * @param[in] first,last
 * @param[in] value
 * @return
 */
template< typename TForwardIterator, typename TValue >
auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value) -> Pair< TForwardIterator, TForwardIterator >;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TValue, typename TComparator >
auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	for (auto length = distance(first, last); length != 0; ) {
		auto half_length = length / 2;
		auto middle = next(first, length);
		if (forward<TComparator>(comparator)(*middle, value)) {
			first = ++middle;
			length -= half_length + 1;
		} else if (forward<TComparator>(comparator)(value, *middle)) {
			last = middle;
			length = half_length;
		} else {
			return {lower_bound(first, middle, value, forward<TComparator>(comparator)), upper_bound(next(middle), last, value, forward<TComparator>(comparator))};
		}
	}
	return {first, first};
}

template< typename TForwardIterator, typename TValue >
inline auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value) -> Pair< TForwardIterator, TForwardIterator > {
	return equal_range(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
