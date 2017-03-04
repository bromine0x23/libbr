/**
 * @file
 * @brief set_union
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
 * @brief Computes the union of two sets.
 *
 * Constructs a sorted range beginning at \p output consisting of all elements present in one or both sorted ranges \f$ [first_0, last_0) \f$ and \f$ [first_1, last_1) \f$.
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
auto set_union(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TOutputIterator output,
	TComparator && comparator
) -> TOutputIterator;

/**
 * @brief Computes the union of two sets.
 *
 * Constructs a sorted range beginning at \p output consisting of all elements present in one or both sorted ranges \f$ [first_0, last_0) \f$ and \f$ [first_1, last_1) \f$.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @param[in] first0,last0 The range of elements to examine.
 * @param[in] first1,last1 The range of elements to examine.
 * @param[out] output The beginning of the destination range.
 * @return Iterator past the end of the constructed range.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
auto set_union(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto set_union(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator output, TComparator && comparator) -> TOutputIterator {
	for (; first0 != last0; ++output) {
		if (first1 == last1) {
			return copy(first0, last0, output);
		}
		if (forward<TComparator>(comparator)(*first1, *first0)) {
			*output = *first1;
			++first1;
		} else {
			*output = *first0;
			if (!forward<TComparator>(comparator)(*first0, *first1)) {
				++first1;
			}
			++first0;
		}
	}
	return copy(first1, last1, output);
}

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
inline auto set_union(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator output) -> TOutputIterator {
	return set_union(first0, last0, first1, last1, output, Less<>());
}

} // namespace Algorithm

} // namespace BR
