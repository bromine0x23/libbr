/**
 * @file
 * @brief max_min
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like min_max, but give result in contrary order
 * @tparam T
 * @tparam TComparator
 * @param[in] x,y
 * @param[in] comparator
 * @see BR::Algorithm::min_max
 * @return <max(x, y), min(x, y)>
 */
template< typename T, typename TComparator >
constexpr auto max_min(T const & x, T const & y, TComparator && comparator) -> Pair< T const &, T const & >;

/**
 * @brief like min_max, but give result in contrary order
 * @tparam T
 * @param[in] x,y
 * @see BR::Algorithm::min_max
 * @return <max(x, y), min(x, y)>
 */
template< typename T >
constexpr auto max_min(T const & x, T const & y) -> Pair< T const &, T const & >;

} // namespace Algorithm



inline namespace Algorithm {

template< typename T, typename TComparator >
constexpr auto max_min(T const & x, T const & y, TComparator && comparator) -> Pair< T const &, T const & > {
	return forward<TComparator>(comparator)(x, y) ? Pair< T const &, T const & >(y, x) : Pair< T const &, T const & >(x, y);
}

template< typename T >
constexpr auto max_min(T const & x, T const & y) -> Pair< T const &, T const & > {
	return max_min(x, y, Less<>());
}

} // namespace Algorithm

} // namespace BR
