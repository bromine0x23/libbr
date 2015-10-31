/**
 * @file
 * @brief replace_if
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TForwardIterator, typename TUnaryPredicate, typename TValue >
inline void replace_if(TForwardIterator first, TForwardIterator last, TValue const & new_value, TUnaryPredicate predicate) {
	for (; first != last; ++first) {
		if (predicate(*first)) {
			*first = new_value;
		}
	}
}

} // namespace BR
