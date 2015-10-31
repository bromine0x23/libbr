/**
 * @file
 * @brief sort_partially_copy
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/heap_build.hpp>
#include <libbr/algorithm/heap_pop.hpp>
#include <libbr/algorithm/heap_sort.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TInputIterator, typename TRandomAccessIterator, typename TComparator >
auto sort_partially_copy(TInputIterator first, TInputIterator last, TRandomAccessIterator result_first, TRandomAccessIterator result_last, TComparator && comparator) -> TRandomAccessIterator {
	auto result = result_first;
	if (result_first != result_last) {
		for (; first != last && result != result_last; ++first, (void)++result) {
			*result = *first;
		}
		heap_build(result_first, result, comparator);
		for (auto length = result - result_first; first != last; ++first) {
			if (comparator(*first, *result_first)) {
				*result_first = *first;
				Detail::Algorithm::heap_shift_down(result_first, result, length, result_first, comparator);
			}
		}
		heap_sort(result_first, result, comparator);
	}
	return result;
}

template< typename TInputIterator, typename TRandomAccessIterator >
inline auto sort_partially_copy(TInputIterator first, TInputIterator last, TRandomAccessIterator result_first, TRandomAccessIterator result_last) -> TRandomAccessIterator {
	return sort_partially_copy(first, last, result_first, result_last, Less<>());
}

} // namespace BR