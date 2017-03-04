/**
 * @file
 * @brief set_symmetric_difference
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Computes the symmetric difference between two sets.
 *
 * Computes symmetric difference of two sorted ranges: the elements that are found in either of the ranges, but not in both of them are copied to the range beginning at \p output.
 * The resulting range is also sorted.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @tparam TComparator Type of \p comparator.
 * @param[in] first0,last0 The range of elements to examine.
 * @param[in] first1,last1 The range of elements to examine.
 * @param[out] output The beginning of the destination range.
 * @param[in] comparator Comparison function object which returns <code>​true</code>
 *                       if the first argument is less than (i.e. is ordered before) the second.
 * @return Iterator past the end of the constructed range.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto set_symmetric_difference(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TOutputIterator output,
	TComparator && comparator
) -> TOutputIterator;

/**
 * @brief Computes the symmetric difference between two sets.
 *
 * Computes symmetric difference of two sorted ranges: the elements that are found in either of the ranges, but not in both of them are copied to the range beginning at \p output.
 * The resulting range is also sorted.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @param[in] first0,last0 The range of elements to examine.
 * @param[in] first1,last1 The range of elements to examine.
 * @param[out] output The beginning of the destination range.
 * @return Iterator past the end of the constructed range.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
auto set_symmetric_difference(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto set_symmetric_difference(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator output, TComparator && comparator) -> TOutputIterator {
	for (; first0 != last0; ){
		if (first1 == last1) {
			return copy(first0, last0, output);
		}
		if (forward<TComparator>(comparator)(*first0, *first1)) {
			*output = *first0;
			++output;
			++first0;
		} else {
			if (forward<TComparator>(comparator)(*first1, *first0)) {
				*output = *first1;
				++output;
			} else {
				++first0;
			}
			++first1;
		}
	}
	return copy(first1, last1, output);
}

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
inline auto set_symmetric_difference(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator output) -> TOutputIterator {
	return set_symmetric_difference(first0, last0, first1, last1, output, Less<>());
}

} // namespace Algorithm

} // namespace BR
