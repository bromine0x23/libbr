/**
 * @file
 * @brief set_include
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Returns <code>true</code> if one set is a subset of another.
 *
 * Returns <code>true</code> if every element from the sorted range \f$ [first_1, last_1) \f$ is found within the sorted range \f$ [first_0, last_0) \f$.
 * Also returns <code>true</code> if \f$ [first_1, last_1) \f$ is empty.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TComparator Type of \p comparator.
 * @param first0,last0 The range of elements to examine.
 * @param first1,last1 The range of elements to search for.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @retval true Every element from \f$ [first_1, last_1) \f$ is a member of \f$ [first_0, last_0) \f$.
 * @retval false Otherwise.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TComparator >
auto set_include(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TComparator && comparator
) -> Boolean;

/**
 * @brief Returns <code>true</code> if one set is a subset of another.
 *
 * Returns <code>true</code> if every element from the sorted range \f$ [first_1, last_1) \f$ is found within the sorted range \f$ [first_0, last_0) \f$.
 * Also returns <code>true</code> if \f$ [first_1, last_1) \f$ is empty.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @param first0,last0 The range of elements to examine.
 * @param first1,last1 The range of elements to search for.
 * @retval true Every element from \f$ [first_1, last_1) \f$ is a member of \f$ [first_0, last_0) \f$.
 * @retval false Otherwise.
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto set_include(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1
) -> Boolean;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TComparator >
auto set_include(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TComparator && comparator) -> Boolean {
	for (; first1 != last1; ++first0) {
		if (first0 == last0) {
			return false;
		}
		if (forward<TComparator>(comparator)(*first1, *first0)) {
			return false;
		}
		if (!forward<TComparator>(comparator)(*first0, *first1)) {
			++first1;
		}
	}
	return true;
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto set_include(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> Boolean {
	return set_include(first0, last0, first1, last1, Less<>());
}

} // namespace Algorithm

} // namespace BR
