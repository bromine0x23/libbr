/**
 * @file
 * @brief count
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TInputIterator, typename TPredicate >
inline auto count_if(TInputIterator first, TInputIterator last, TPredicate predicate) -> typename IteratorTraits<TInputIterator>::Difference {
	typename IteratorTraits<TInputIterator>::Difference result(0);
	for (; first != last; ++first) {
		if (predicate(*first)) {
			++result;
		}
	}
	return result;
}

} // namespace BR
