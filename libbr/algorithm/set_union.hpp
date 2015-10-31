/**
 * @file
 * @brief set_union
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto set_union(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator && comparator) -> TOutputIterator {
	for (; first0 != last0; ++result) {
		if (first1 == last1) {
			return copy(first0, last0, result);
		}
		if (comparator(*first1, *first0)) {
			*result = *first1;
			++first1;
		} else {
			*result = *first0;
			if (!comparator(*first0, *first1)) {
				++first1;
			}
			++first0;
		}
	}
	return copy(first1, last1, result);
}

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
inline auto set_union(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result) -> TOutputIterator {
	return set_union(first0, last0, first1, last1, result, Less<>());
}

} // namespace BR
