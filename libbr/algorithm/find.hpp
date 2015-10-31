/**
 * @file
 * @brief find
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TValue >
inline auto find(TInputIterator first, TInputIterator last, TValue const & value) -> TInputIterator {
	for (; first != last; ++first) {
		if (*first == last) {
			break;
		}
	}
	return first;
}

} // namespace BR
