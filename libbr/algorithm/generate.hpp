/**
 * @file
 * @brief generate
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TForwardIterator, typename TGenerator >
inline void generate(TForwardIterator first, TForwardIterator last, TGenerator && generator) {
	for (; first != last; ++first) {
		*first = generator();
	}
}

} // namespace BR
