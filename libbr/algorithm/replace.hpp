/**
 * @file
 * @brief replace
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TForwardIterator, typename TValue >
inline void replace(TForwardIterator first, TForwardIterator last, TValue const & old_value, TValue const & new_value) {
	for (; first != last; ++first) {
		if (*first == old_value) {
			*first = new_value;
		}
	}
}

} // namespace BR
