/**
 * @file
 * @brief remove_copy
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TOutputIterator, typename TValue >
auto remove_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TValue const & value) -> TOutputIterator {
	for (; first != last; ++first) {
		if (!(*first == value)) {
			*result = *first;
			++result;
		}
	}
	return result;
}

} // namespace BR
