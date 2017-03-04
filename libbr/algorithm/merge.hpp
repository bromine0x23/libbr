/**
 * @file
 * @brief merge
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
 * @brief Merges two sorted ranges.
 *
 * Merges two sorted ranges \f$ [first_0, last_0) \f$ and \f$ [first_1, last_1) \f$ into one sorted range beginning at \p output.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @tparam TComparator Type of \p comparator.
 * @param[in] first0,last0 The first range of elements to merge.
 * @param[in] first1,last1 The second range of elements to merge.
 * @param[out] output The beginning of the destination range.
 * @param[in] comparator Comparison function object which returns <code>​true</code>
 *                       if the first argument is less than (i.e. is ordered before) the second.
 * @return An output iterator to element past the last element copied.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto merge(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TOutputIterator output,
	TComparator && comparator
) -> TOutputIterator;

/**
 * @brief Merges two sorted ranges.
 *
 * Merges two sorted ranges \f$ [first_0, last_0) \f$ and \f$ [first_1, last_1) \f$ into one sorted range beginning at \p output.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @param[in] first0,last0 The first range of elements to merge.
 * @param[in] first1,last1 The second range of elements to merge.
 * @param[out] output The beginning of the destination range.
 * @return An output iterator to element past the last element copied.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
auto merge(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator output, TComparator && comparator) -> TOutputIterator {
	for (; first0 != last0; ++output) {
		if (first1 == last1) {
			return copy(first0, last0, output);
		}
		if (forward<TComparator>(comparator)(*first1, *first0)) {
			*output = *first1;
			++first1;
		} else {
			*output = *first0;
			++first0;
		}
	}
	return copy(first1, last1, output);
}

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
inline auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator output) -> TOutputIterator {
	return merge(first0, last0, first1, last1, output, Less<void>());
}

} // namespace Algorithm

} // namespace BR
