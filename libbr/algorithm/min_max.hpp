/**
 * @file
 * @brief min_max
 * @author Bromine0x23
 * @since 2015/10/23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::minmax
 * @tparam T
 * @tparam TComparator
 * @param[in] x,y
 * @param[in] comparator
 * @return
 */
template< typename T, typename TComparator >
constexpr auto min_max(T const & x, T const & y, TComparator && comparator) -> Pair< T const &, T const & >;

/**
 * @brief like std::minmax
 * @tparam T
 * @param[in] x,y
 * @return
 */
template< typename T >
constexpr auto min_max(T const & x, T const & y) -> Pair< T const &, T const & >;

} // namespace Algorithm



inline namespace Algorithm {

template< typename T, typename TComparator >
constexpr auto min_max(T const & x, T const & y, TComparator && comparator) -> Pair< T const &, T const & > {
	return forward<TComparator>(comparator)(y, x) ? Pair< T const &, T const & >(y, x) : Pair< T const &, T const & >(x, y);
}

template< typename T >
constexpr auto min_max(T const & x, T const & y) -> Pair< T const &, T const & > {
	return max_min(x, y, Less<>());
}

} // namespace Algorithm

} // namespace BR
