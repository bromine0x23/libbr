/**
 * @file
 * @brief clamp
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * Clamps a value between a pair of boundary values.
 * @tparam TValue Type of \p value, \p low & \p high.
 * @tparam TComparator Type of \p comparator
 * @param value The value to clamp.
 * @param low,high The boundaries to clamp \p value to.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return Reference to \p low if \p value is less than \p low,
 *         reference to \p high if \p high is less than \p value,
 *         otherwise reference to \p value.
 */
template< typename TValue, typename TComparator >
constexpr auto clamp(
	TValue const & value,
	TValue const & low, TValue const & high,
	TComparator && comparator
) -> TValue const &;

/**
 * Clamps a value between a pair of boundary values (use Less<>).
 * @tparam TValue Type of \p value, \p low & \p high.
 * @param value The value to clamp.
 * @param low,high The boundaries to clamp \p value to.
 * @return Reference to \p low if \p value is less than \p low,
 *         reference to \p high if \p high is less than \p value,
 *         otherwise reference to \p value.
 */
template< typename TValue >
constexpr auto clamp(
	TValue const & value,
	TValue const & low, TValue const & high
) -> TValue const &;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TValue, typename TComparator >
constexpr auto clamp(TValue const & value, TValue const & low, TValue const & high, TComparator && comparator) -> TValue const & {
	return forward<TComparator>(comparator)(value, low) ? low : forward<TComparator>(comparator)(high, value) ? high : value;
}

template< typename TValue >
constexpr auto clamp(TValue const & value, TValue const & low, TValue const & high) -> TValue const & {
	return clamp(value, low, high, Less<>());
}

} // namespace Algorithm

} // namespace BR
