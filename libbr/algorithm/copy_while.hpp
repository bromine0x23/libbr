/**
 * @file
 * @brief copy_while
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
inline auto copy_while(TInputIterator first, TInputIterator last, TOutputIterator result, TUnaryPredicate && predicate) -> TOutputIterator {
	for (; first != last && predicate(*first); ++result, (void)++first) {
		*result = *first;
	}
	return result;
}

} // namespace BR
