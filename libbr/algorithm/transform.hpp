/**
 * @file
 * @brief transform
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryOperation >
inline auto transform(TInputIterator first, TInputIterator last, TOutputIterator result, TUnaryOperation && operation) -> TOutputIterator {
	for (; first != last; ++first, (void)++result) {
		*result = operation(*first);
	}
	return result;
}

} // namespace BR
