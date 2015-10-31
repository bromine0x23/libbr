/**
 * @file
 * @brief is_partitioned
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TUnaryPredicate >
auto is_partitioned(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool {
	for (; first != last; ++first) {
		if (!predicate(*first)) {
			break;
		}
	}
	for (; first != last; ++first) {
		if (predicate(*first)) {
			return false;
		}
	}
	return true;
}

} // namespace BR
