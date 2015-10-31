/**
 * @file
 * @brief move
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TInputIterator, typename TOutputIterator >
inline auto move(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	for (; first != last; ++first, (void)++result) {
		*result = move(*first);
	}
	return result;
}

} // namespace BR
