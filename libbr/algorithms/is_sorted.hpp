/**
 * @file
 * @brief is_sorted
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/sorted_until.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Checks whether a range is sorted into ascending order
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @retval true The elements in the range are sorted in ascending order.
 * @retval false Otherwise.
 */
template< typename TForwardIterator, typename TComparator >
constexpr auto is_sorted(
	TForwardIterator first, TForwardIterator last,
	TComparator && comparator
) -> Boolean;

/**
 * @brief like std::is_sorted
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param first,last The range of elements to examine.
 * @retval true The elements in the range are sorted in ascending order.
 * @retval false Otherwise.
 */
template< typename TForwardIterator >
constexpr auto is_sorted(
	TForwardIterator first, TForwardIterator last
) -> Boolean;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TComparator >
constexpr inline auto is_sorted(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> bool {
	return sorted_until(first, last, forward<TComparator>(comparator)) == last;
}

template< typename TForwardIterator >
constexpr inline auto is_sorted(TForwardIterator first, TForwardIterator last) -> bool {
	return is_sorted(first, last, Less<>{});
}

} // namespace Algorithms

} // namespace BR
