/**
 * @file
 * @brief minmax
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/minmax_element.hpp>
#include <libbr/containers/initializer_list.hpp>
#include <libbr/containers/pair.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Returns the smaller and larger of two elements.
 * @tparam T Type of \p x & \p y.
 * @tparam TComparator Type of \p comparator.
 * @param x,y the values to compare.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @see BR::Algorithm::max_min
 * @return Returns the result of <code>Pair&lt;T const &amp;, T const &amp;&gt;(x, y)</code> if \f$ x < y \f$ or if \p x is equivalent to \p y.
 *         Returns the result of <code>Pair&lt;T const &amp;, T const &amp;&gt;(y, x)</code> if \f$ y < x \f$.
 */
template< typename T, typename TComparator >
constexpr auto minmax(
	T const & x, T const & y,
	TComparator && comparator
) -> Pair< T const &, T const & >;

/**
 * @brief Returns the smaller and larger of two elements.
 * @tparam T Type of \p x & \p y.
 * @param x,y the values to compare.
 * @see BR::Algorithm::max_min
 * @return Returns the result of <code>Pair&lt;T const &amp;, T const &amp;&gt;(x, y)</code> if \f$ x < y \f$ or if \p x is equivalent to \p y.
 *         Returns the result of <code>Pair&lt;T const &amp;, T const &amp;&gt;(y, x)</code> if \f$ y < x \f$.
 */
template< typename T >
constexpr auto minmax(
	T const & x, T const & y
) -> Pair< T const &, T const & >;

/**
 * @brief Returns the smallest and the largest of the values in initializer list \p list.
 * @tparam T Type of elements that \p list take.
 * @tparam TComparator Type of \p comparator.
 * @param list Initializer list with the values to compare.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return A pair with the smallest value in \p list as the first element and the largest as the second.
 *         If several elements are equivalent to the smallest, the leftmost such element is returned.
 *         If several elements are equivalent to the largest, the rightmost such element is returned.
 */
template< typename T, typename TComparator >
constexpr auto minmax(
	InitializerList<T> list,
	TComparator && comparator
) -> Pair< T, T >;

/**
 * @brief Returns the smallest and the largest of the values in initializer list \p list.
 * @tparam T Type of elements that \p list take.
 * @param list Initializer list with the values to compare.
 * @return A pair with the smallest value in \p list as the first element and the largest as the second.
 *         If several elements are equivalent to the smallest, the leftmost such element is returned.
 *         If several elements are equivalent to the largest, the rightmost such element is returned.
 */
template< typename T >
constexpr auto minmax(
	InitializerList<T> list
) -> Pair< T, T >;

} // namespace Algorithms



inline namespace Algorithms {

template< typename T, typename TComparator >
constexpr auto minmax(T const & x, T const & y, TComparator && comparator) -> Pair< T const &, T const & > {
	return forward<TComparator>(comparator)(y, x) ? Pair< T const &, T const & >(y, x) : Pair< T const &, T const & >(x, y);
}

template< typename T >
constexpr auto minmax(T const & x, T const & y) -> Pair< T const &, T const & > {
	return minmax(x, y, Less<>{});
}

template< typename T, typename TComparator >
constexpr auto minmax(InitializerList<T> list, TComparator && comparator) -> Pair< T, T > {
	auto pair = minmax_element(list.begin(), list.end(), forward<TComparator>(comparator));
	return make_pair(*pair.first, *pair.second);
}

template< typename T >
constexpr auto minmax(InitializerList<T> list) -> Pair< T, T > {
	return Algorithms::minmax(list, Less<>{});
}

} // namespace Algorithms

} // namespace BR
