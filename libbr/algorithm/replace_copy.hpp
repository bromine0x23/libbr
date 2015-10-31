/**
 * @file
 * @brief replace_copy
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TOutputIterator, typename TValue >
inline auto replace_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TValue const & old_value, TValue const & new_value) -> TOutputIterator {
	for (; first != last; ++first, (void) ++result) {
		*result = (*first == old_value) ? new_value : *first;
	}
	return result;
}

} // namespace BR
