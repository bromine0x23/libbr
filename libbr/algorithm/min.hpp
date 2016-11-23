/**
 * @file
 * @brief min
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/math/function/min.hpp>
#include <libbr/utility/forward.hpp>

#if defined(min)
#undef min
#  pragma message("macro \"min\" undefined")
#endif

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::min
 * @tparam T
 * @tparam TComparator
 * @param[in] x,y
 * @param[in] comparator
 * @return
 */
template< typename T, typename TComparator >
constexpr auto min(T const & x, T const & y, TComparator && comparator) -> T const &;

/**
 * @brief like std::min
 * @tparam T
 * @param[in] x,y
 * @return
 */
template< typename T >
constexpr auto min(T const & x, T const & y) -> T const &;

} // namespace Algorithm



inline namespace Algorithm {

template< typename T, typename TComparator >
constexpr auto min(T const & x, T const & y, TComparator && comparator) -> T const & {
	return forward<TComparator>(comparator)(y, x) ? y : x;
}

template< typename T >
constexpr auto min(T const & x, T const & y) -> T const & {
	return min(x, y, Less<>());
}

} // namespace Algorithm

} // namespace BR
