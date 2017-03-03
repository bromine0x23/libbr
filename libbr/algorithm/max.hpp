/**
 * @file
 * @brief max
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/max_element.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/math/function/max.hpp>
#include <libbr/utility/forward.hpp>

#if defined(max)
#undef max
#  pragma message("macro \"max\" undefined")
#endif

namespace BR {

inline namespace Algorithm {

/**
 * @brief Returns the larger of \p x and \p y.
 * @tparam T Type of \p x & \p y.
 * @tparam TComparator Type of \p comparator.
 * @param x,y The values to compare.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return The larger of \p x and \p y.
 *         If they are equivalent, returns \p x.
 */
template< typename T, typename TComparator >
constexpr auto max(
	T const & x, T const & y,
	TComparator && comparator
) -> T const &;

/**
 * @brief Returns the larger of \p x and \p y.
 * @tparam T Type of \p x & \p y.
 * @param x,y The values to compare.
 * @return The larger of \p x and \p y.
 *         If they are equivalent, returns \p x.
 */
template< typename T >
constexpr auto max(
	T const & x, T const & y
) -> T const &;

/**
 * @brief Returns the largest of the values in initializer list \p list.
 * @tparam T Type of elements that \p list take.
 * @tparam TComparator Type of \p comparator.
 * @param list Initializer list with the values to compare.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return The largest value in \p list.
 *         If several values are equivalent to the largest, returns the leftmost one.
 */
template< typename T, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 auto max(
	InitializerList<T> list,
	TComparator && comparator
) -> T;

/**
 * @brief Returns the largest of the values in initializer list \p list.
 * @tparam T Type of elements that \p list take.
 * @param list Initializer list with the values to compare.
 * @return The largest value in \p list.
 *         If several values are equivalent to the largest, returns the leftmost one.
 */
template< typename T >
BR_CONSTEXPR_AFTER_CXX11 auto max(
	InitializerList<T> list
) -> T;

} // namespace Algorithm



inline namespace Algorithm {

template< typename T, typename TComparator >
constexpr auto max(T const & x, T const & y, TComparator && comparator) -> T const & {
	return forward<TComparator>(comparator)(x, y) ? y : x;
}

template< typename T >
constexpr auto max(T const & x, T const & y) -> T const & {
	return max(x, y, Less<>());
}

template< typename T, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 auto max(InitializerList<T> list, TComparator && comparator) -> T {
	return *max_element(list.begin(), list.end(), forward<TComparator>(comparator));
}

template< typename T >
BR_CONSTEXPR_AFTER_CXX11 auto max(InitializerList<T> list) -> T {
	return *max_element(list.begin(), list.end(), Less<>());
}

} // namespace Algorithm

} // namespace BR
