/**
 * @file
 * @brief partition_point
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/iterator/distance.hpp>

namespace BR {

template< typename TForwardIterator, typename TUnaryPredicate >
auto partition_point(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	for (auto length = distance(first, last); length != 0;) {
		auto half_length = length / 2;
		auto middle = first;
		advance(middle, half_length);
		if (predicate(*middle)) {
			first = ++middle;
			length -= half_length + 1;
		} else {
			length = half_length;
		}
	}
	return first;
}

} // namespace BR