/**
 * @file
 * @brief set_include
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TInputIterator0, typename TInputIterator1, typename TComparator >
auto set_include(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TComparator && comparator) -> bool {
	for (; first1 != last1; ++first0) {
		if (first0 == last0) {
			return false;
		}
		if (comparator(*first1, *first0)) {
			return false;
		}
		if (!comparator(*first0, *first1)) {
			++first1;
		}
	}
	return true;
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto set_include(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> bool {
	return set_include(first0, last0, first1, last1, Less<>());
}

} // namespace BR
