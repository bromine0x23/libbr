/**
 * @file
 * @brief rotate_copy
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>

namespace BR {

template< typename TForwardIterator, typename TOutputIterator >
inline auto rotate_copy(TForwardIterator first, TForwardIterator middle, TForwardIterator last, TOutputIterator result) -> TOutputIterator {
	return copy(first, middle, copy(middle, last, result));
}

} // namespace BR
