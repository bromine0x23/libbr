/**
 * @file
 * @brief replace_copy_if
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate, typename TValue >
inline auto replace_copy_if(TInputIterator first, TInputIterator last, TOutputIterator result, TValue const & new_value, TUnaryPredicate && predicate) -> TOutputIterator {
	for (; first != last; ++first, (void) ++result) {
		*result = predicate(*first) ? new_value : *first;
	}
	return result;
}

} // namespace BR
