/**
 * @file
 * @brief min
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/min_element.hpp>
#include <libbr/containers/initializer_list.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Returns the smaller of \p x and \p y.
 * @tparam T Type of \p x & \p y.
 * @tparam TComparator Type of \p comparator.
 * @param x,y The values to compare.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return The smaller of \p x and \p y.
 *         If they are equivalent, returns \p x.
 */
template< typename T, typename TComparator >
constexpr auto min(
	T const & x, T const & y,
	TComparator && comparator
) -> T const &;

/**
 * @brief Returns the smaller of \p x and \p y.
 * @tparam T Type of \p x & \p y.
 * @param x,y The values to compare.
 * @return The larger of \p x and \p y.
 *         If they are equivalent, returns \p x.
 */
template< typename T >
constexpr auto min(
	T const & x, T const & y
) -> T const &;

/**
 * @brief Returns the smallest of the values in initializer list \p list.
 * @tparam T Type of elements that \p list take.
 * @tparam TComparator Type of \p comparator.
 * @param list Initializer list with the values to compare.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return The smallest value in \p list.
 *         If several values are equivalent to the largest, returns the leftmost one.
 */
template< typename T, typename TComparator >
constexpr auto min(
	InitializerList<T> list,
	TComparator && comparator
) -> T;

/**
 * @brief Returns the smallest of the values in initializer list \p list.
 * @tparam T Type of elements that \p list take.
 * @param list Initializer list with the values to compare.
 * @return The smallest value in \p list.
 *         If several values are equivalent to the largest, returns the leftmost one.
 */
template< typename T >
constexpr auto min(
	InitializerList<T> list
) -> T;

} // namespace Algorithms



inline namespace Algorithms {

template< typename T, typename TComparator >
constexpr auto min(T const & x, T const & y, TComparator && comparator) -> T const & {
	return forward<TComparator>(comparator)(y, x) ? y : x;
}

template< typename T >
constexpr auto min(T const & x, T const & y) -> T const & {
	return min(x, y, Less<>{});
}

template< typename T, typename TComparator >
constexpr auto min(InitializerList<T> list, TComparator && comparator) -> T {
	return *min_element(list.begin(), list.end(), forward<TComparator>(comparator));
}

template< typename T >
constexpr auto min(InitializerList<T> list) -> T {
	return *min_element(list.begin(), list.end(), Less<>{});
}

} // namespace Algorithms

} // namespace BR
