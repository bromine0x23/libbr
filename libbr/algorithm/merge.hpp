/**
 * @file
 * @brief merge
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

namespace Detail {
namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator & comparator) -> TOutputIterator {
	for (; first0 != last0; ++result) {
		if (first1 == last1) {
			return copy(first0, last0, result);
		}
		if (comparator(*first1, *first0)) {
			*result = *first1;
			++first1;
		} else {
			*result = *first0;
			++first0;
		}
	}
	return copy(first1, last1, result);
};

} // namespace Algorithm
} // namespace Detail

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
inline auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator && comparator) -> TOutputIterator {
	return Detail::Algorithm::merge(first0, last0, first1, last1, result, comparator);
};

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
inline auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result) -> TOutputIterator {
	return merge(first0, last0, first1, last1, result, Less<void>());
};

} // namespace BR
