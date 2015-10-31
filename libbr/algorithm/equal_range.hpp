/**
 * @file
 * @brief equal_range
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/lower_bound.hpp>
#include <libbr/algorithm/upper_bound.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TForwardIterator, typename TValue, typename TComparator >
auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	for (auto length = distance(first, last); length != 0; ) {
		auto half_length = length / 2;
		auto middle = next(first, length);
		if (comparator(*middle, value)) {
			first = ++middle;
			length -= half_length + 1;
		} else if (comparator(value, *middle)) {
			last = middle;
			length = half_length;
		} else {
			return make_pair(lower_bound(first, middle, value, comparator), upper_bound(next(middle), last, value, comparator));
		}
	}
	return make_pair(first, first);
}

template< typename TForwardIterator, typename TValue >
inline auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value) -> Pair< TForwardIterator, TForwardIterator > {
	return equal_range(first, last, Less<void>());
}

} // namespace BR
