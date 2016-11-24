/**
 * @file
 * @brief sort_partially_copy
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/heap_build.hpp>
#include <libbr/algorithm/heap_pop.hpp>
#include <libbr/algorithm/heap_sort.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::partial_sort_copy
 * @tparam TInputIterator
 * @tparam TRandomAccessIterator
 * @tparam TComparator
 * @param[in] first,last
 * @param[out] result_first,result_last
 * @param[in] comparator
 * @return
 */
template< typename TInputIterator, typename TRandomAccessIterator, typename TComparator >
auto sort_partially_copy(TInputIterator first, TInputIterator last, TRandomAccessIterator result_first, TRandomAccessIterator result_last, TComparator && comparator) -> TRandomAccessIterator;

/**
 * @brief like std::partial_sort_copy
 * @tparam TInputIterator
 * @tparam TRandomAccessIterator
 * @param[in] first,last
 * @param[out] result_first,result_last
 * @return
 */
template< typename TInputIterator, typename TRandomAccessIterator >
auto sort_partially_copy(TInputIterator first, TInputIterator last, TRandomAccessIterator result_first, TRandomAccessIterator result_last) -> TRandomAccessIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TRandomAccessIterator, typename TComparator >
auto sort_partially_copy(TInputIterator first, TInputIterator last, TRandomAccessIterator result_first, TRandomAccessIterator result_last, TComparator && comparator) -> TRandomAccessIterator {
	auto result = result_first;
	if (result_first != result_last) {
		for (; first != last && result != result_last; ++first, (void)++result) {
			*result = *first;
		}
		heap_build(result_first, result, forward<TComparator>(comparator));
		for (auto length = result - result_first; first != last; ++first) {
			if (comparator(*first, *result_first)) {
				*result_first = *first;
				Detail::Algorithm::heap_shift_down(result_first, result, length, result_first, forward<TComparator>(comparator));
			}
		}
		heap_sort(result_first, result, forward<TComparator>(comparator));
	}
	return result;
}

template< typename TInputIterator, typename TRandomAccessIterator >
inline auto sort_partially_copy(TInputIterator first, TInputIterator last, TRandomAccessIterator result_first, TRandomAccessIterator result_last) -> TRandomAccessIterator {
	return sort_partially_copy(first, last, result_first, result_last, Less<>());
}

} // namespace Algorithm

} // namespace BR