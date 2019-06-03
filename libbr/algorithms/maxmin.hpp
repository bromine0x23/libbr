/**
 * @file
 * @brief max_min
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/maxmin_element.hpp>
#include <libbr/containers/initializer_list.hpp>
#include <libbr/containers/pair.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Returns the larger and smaller of two elements.
 * @tparam T Type of \p x & \p y.
 * @tparam TComparator Type of \p comparator.
 * @param x,y the values to compare.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @see BR::Algorithm::min_max
 * @return Returns the result of <code>Pair&lt;T const &amp;, T const &amp;&gt;(x, y)</code> if \f$ y < x \f$ or if \p x is equivalent to \p y.
 *         Returns the result of <code>Pair&lt;T const &amp;, T const &amp;&gt;(y, x)</code> if \f$ x < y \f$.
 */
template< typename T, typename TComparator >
constexpr auto maxmin(
	T const & x, T const & y,
	TComparator && comparator
) -> Pair< T const &, T const & >;

/**
 * @brief Returns the larger and smaller of two elements.
 * @tparam T Type of \p x & \p y.
 * @param x,y the values to compare.
 * @see BR::Algorithm::min_max
 * @return Returns the result of <code>Pair&lt;T const &amp;, T const &amp;&gt;(x, y)</code> if \f$ y < x \f$ or if \p x is equivalent to \p y.
 *         Returns the result of <code>Pair&lt;T const &amp;, T const &amp;&gt;(y, x)</code> if \f$ x < y \f$.
 */
template< typename T >
constexpr auto maxmin(
	T const & x, T const & y
) -> Pair< T const &, T const & >;

/**
 * @brief Returns the largest and the smallest of the values in initializer list \p list.
 * @tparam T Type of elements that \p list take.
 * @tparam TComparator Type of \p comparator.
 * @param list Initializer list with the values to compare.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return A pair with the largest value in \p list as the first element and the smallest as the second.
 *         If several elements are equivalent to the smallest, the leftmost such element is returned.
 *         If several elements are equivalent to the largest, the rightmost such element is returned.
 */
template< typename T, typename TComparator >
constexpr auto maxmin(
	InitializerList<T> list,
	TComparator && comparator
) -> Pair< T, T >;

/**
 * @brief Returns the largest and the smallest of the values in initializer list \p list.
 * @tparam T Type of elements that \p list take.
 * @param list Initializer list with the values to compare.
 * @return A pair with the largest value in \p list as the first element and the smallest as the second.
 *         If several elements are equivalent to the smallest, the leftmost such element is returned.
 *         If several elements are equivalent to the largest, the rightmost such element is returned.
 */
template< typename T >
constexpr auto maxmin(
	InitializerList<T> list
) -> Pair< T, T >;

} // namespace Algorithms



inline namespace Algorithms {

template< typename T, typename TComparator >
constexpr auto maxmin(T const & x, T const & y, TComparator && comparator) -> Pair< T const &, T const & > {
	return forward<TComparator>(comparator)(x, y) ? Pair< T const &, T const & >(y, x) : Pair< T const &, T const & >(x, y);
}

template< typename T >
constexpr auto maxmin(T const & x, T const & y) -> Pair< T const &, T const & > {
	return maxmin(x, y, Less<>{});
}

template< typename T, typename TComparator >
constexpr auto maxmin(InitializerList<T> list, TComparator && comparator) -> Pair< T, T > {
	auto pair = maxmin_element(list.begin(), list.end(), forward<TComparator>(comparator));
	return make_pair(*pair.first, *pair.second);
}

template< typename T >
constexpr auto maxmin(InitializerList<T> list) -> Pair< T, T > {
	return Algorithms::maxmin(list, Less<>{});
}

} // namespace Algorithms

} // namespace BR
