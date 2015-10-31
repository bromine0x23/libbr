/**
 * @file
 * @brief move_backward
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
inline auto move_backward(TBidirectionalIterator0 first, TBidirectionalIterator0 last, TBidirectionalIterator1 result) -> TBidirectionalIterator1 {
	for (; first != last;) {
		*--result = move(*--last);
	}
	return result;
}

} // namespace BR
