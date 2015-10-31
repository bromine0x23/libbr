/**
 * @file
 * @brief copy_if
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
inline auto copy_if(TInputIterator first, TInputIterator last, TOutputIterator result, TUnaryPredicate && predicate) -> TOutputIterator {
	for (; first != last; ++first) {
		if (predicate(*first)) {
			*result = *first;
			++result;
		}
	}
	return result;
}

} // namespace BR
