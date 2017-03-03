/**
 * @file
 * @brief lexicographical_compare
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * Returns <code>true</code> if one range is lexicographically less than another.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em InputIterator.
 * @tparam TComparator Type of \p comparator
 * @param first0,last0 The first range of elements to examine.
 * @param first1,last1 The second range of elements to examine
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @retval true The first range is lexicographically less than the second.
 * @retval false Otherwise.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TComparator >
auto lexicographical_compare(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TComparator && comparator
) -> Boolean;

/**
 * Returns <code>true</code> if one range is lexicographically less than another.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em InputIterator.
 * @param first0,last0 The first range of elements to examine.
 * @param first1,last1 The second range of elements to examine
 * @retval true The first range is lexicographically less than the second.
 * @retval false Otherwise.
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto lexicographical_compare(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1
) -> Boolean;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TComparator >
auto lexicographical_compare(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TComparator && comparator) -> Boolean {
	for (; first1 != last1; ++first0, (void)++first1) {
		if (first0 == last0) {
			return true;
		}
		if (forward<TComparator>(comparator)(*first0, *first1)) {
			return true;
		}
		if (forward<TComparator>(comparator)(*first1, *first0)) {
			return false;
		}
	}
	return false;
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto lexicographical_compare(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> Boolean {
	return lexicographical_compare(first0, last0, first1, last1, Less<>());
}

} // namespace Algorithm

} // namespace BR
