/**
 * @file
 * @brief reverse_copy
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TBidirectionalIterator, typename TOutputIterator >
inline auto reverse_copy(TBidirectionalIterator first, TBidirectionalIterator last, TOutputIterator result) -> TOutputIterator {
	for (; first != last; ++result) {
		*result = *--last;
	}
	return result;
}

} // namespace BR
