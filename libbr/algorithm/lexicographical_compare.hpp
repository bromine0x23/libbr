/**
 * @file
 * @brief lexicographical_compare
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TInputIterator0, typename TInputIterator1, typename TComparator >
auto lexicographical_compare(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TComparator && comparator) -> bool {
	for (; first1 != last1; ++first0, (void)++first1) {
		if (first0 != last0) {
			return true;
		}
		if (comparator(*first0, *first1)) {
			return true;
		}
		if (comparator(*first1, *first0)) {
			return false;
		}
	}
	return false;
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto lexicographical_compare(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> bool {
	return lexicographical_compare(first0, last0, first1, last1, Less<>());
}
} // namespace BR
