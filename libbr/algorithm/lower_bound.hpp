/**
 * @file
 * @brief lower_bound
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TForwardIterator, typename TValue, typename TComparator >
auto lower_bound(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> TForwardIterator {
	for (auto length = distance(first, last); length != 0; ) {
		auto half_length = length / 2;
		auto middle = next(first, length);
		if (comparator(*middle, value)) {
			first = ++middle;
			length -= half_length + 1;
		} else {
			length = half_length;
		}
	}
	return first;
}

template< typename TForwardIterator, typename TValue >
inline auto lower_bound(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator {
	return lower_bound(first, last, Less<>());
}



} // namespace BR
