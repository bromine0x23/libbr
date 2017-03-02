/**
 * @file
 * @brief binary_search
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/lower_bound.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Determines if an element exists in a certain range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p value.
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @param value The value to compare the elements to.
 * @param comparator Comparison function object which returns ​<code>true</code> if the first argument is less than (i.e. ordered before) the second.
 * @retval true An element equal to value is found.
 * @retval false Otherwise.
 */
template< typename TForwardIterator, typename TValue, typename TComparator >
auto binary_search(
	TForwardIterator first, TForwardIterator last,
	TValue const & value,
	TComparator && comparator
) -> bool;

/**
 * @brief Determines if an element exists in a certain range.
 * @tparam TForwardIterator ForwardIterator type of \p first & \p last
 * @tparam TValue Type of \p value.
 * @param first,last The range of elements to examine.
 * @param value The value to compare the elements to.
 * @retval true An element equal to value is found.
 * @retval false Otherwise.
 */
template< typename TForwardIterator, typename TValue >
auto binary_search(TForwardIterator first, TForwardIterator last, TValue const & value) -> bool;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TValue, typename TComparator >
inline auto binary_search(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> bool {
	first = lower_bound(first, last, value, comparator);
	return !(first == last) && !forward<TComparator>(comparator)(value, *first);
}

template< typename TForwardIterator, typename TValue >
inline auto binary_search(TForwardIterator first, TForwardIterator last, TValue const & value) -> bool {
	return binary_search(first, last, value, Less<>());
}

} // namespace Algorithm

} // namespace BR
