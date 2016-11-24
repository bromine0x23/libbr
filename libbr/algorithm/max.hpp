/**
 * @file
 * @brief max
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
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
 * @brief like std::max
 * @tparam T
 * @tparam TComparator
 * @param[in] x,y
 * @param[in] comparator
 * @return
 */
template< typename T, typename TComparator >
constexpr auto max(T const & x, T const & y, TComparator && comparator) -> T const &;

/**
 * @brief like std::max
 * @tparam T
 * @param[in] x,y
 * @return
 */
template< typename T >
constexpr auto max(T const & x, T const & y) -> T const &;

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

} // namespace Algorithm

} // namespace BR
