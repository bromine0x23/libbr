/**
 * @file
 * @brief generate_n
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TOutputIterator, typename TSize, typename TGenerator >
inline void generate_n(TOutputIterator first, TSize n, TGenerator && generator) {
	for (; n > 0; ++first, (void)--n) {
		*first = generator();
	}
	return first;
}

} // namespace BR
