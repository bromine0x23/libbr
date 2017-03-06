/**
 * @file
 * @brief sort_partially_copy
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
 * @brief Copies and partially sorts a range of elements.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TRandomAccessIterator Type of \p first_output & \p last_output which satisfies \em RandomAccessIterator.
 * @tparam TComparator Type of \p comparator.
 * @param[in] first,last The range of elements to sort.
 * @param[out] first_output,last_output Random access iterators defining the destination range.
 * @param[in] comparator Comparison function object which returns <code>​true</code>
 *                       if the first argument is less than (i.e. is ordered before) the second.
 * @return An iterator to the element defining the upper boundary of the sorted range,
 *         i.e. \f$ first_{output} + min(last - first, last_{output} - first_{output}) \f$.
 */
template< typename TInputIterator, typename TRandomAccessIterator, typename TComparator >
auto sort_partially_copy(
	TInputIterator first, TInputIterator last,
	TRandomAccessIterator first_output, TRandomAccessIterator last_output,
	TComparator && comparator
) -> TRandomAccessIterator;

/**
 * @brief Copies and partially sorts a range of elements.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TRandomAccessIterator Type of \p first_output & \p last_output which satisfies \em RandomAccessIterator.
 * @param[in] first,last The range of elements to sort.
 * @param[out] first_output,last_output Random access iterators defining the destination range.
 * @return An iterator to the element defining the upper boundary of the sorted range,
 *         i.e. \f$ first_{output} + min(last - first, last_{output} - first_{output}) \f$.
 */
template< typename TInputIterator, typename TRandomAccessIterator >
auto sort_partially_copy(
	TInputIterator first, TInputIterator last,
	TRandomAccessIterator first_output, TRandomAccessIterator last_output
) -> TRandomAccessIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TRandomAccessIterator, typename TComparator >
auto sort_partially_copy(TInputIterator first, TInputIterator last, TRandomAccessIterator first_output, TRandomAccessIterator last_output, TComparator && comparator) -> TRandomAccessIterator {
	auto result = first_output;
	if (first_output != last_output) {
		for (; first != last && result != last_output; ++first, (void)++result) {
			*result = *first;
		}
		heap_build(first_output, result, forward<TComparator>(comparator));
		for (auto length = result - first_output; first != last; ++first) {
			if (forward<TComparator>(comparator)(*first, *first_output)) {
				*first_output = *first;
				Detail::Algorithm::heap_shift_down(first_output, result, length, first_output, forward<TComparator>(comparator));
			}
		}
		heap_sort(first_output, result, forward<TComparator>(comparator));
	}
	return result;
}

template< typename TInputIterator, typename TRandomAccessIterator >
inline auto sort_partially_copy(TInputIterator first, TInputIterator last, TRandomAccessIterator first_output, TRandomAccessIterator last_output) -> TRandomAccessIterator {
	return sort_partially_copy(first, last, first_output, last_output, Less<>());
}

} // namespace Algorithm

} // namespace BR