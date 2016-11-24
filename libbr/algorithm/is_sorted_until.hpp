/**
 * @file
 * @brief is_sorted_until
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::is_sorted_until
 * @tparam TForwardIterator
 * @tparam TComparator
 * @param[in] first,last
 * @param[in] comparator
 * @return
 */
template< typename TForwardIterator, typename TComparator >
auto is_sorted_until(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator;

/**
 * @brief like std::is_sorted_until
 * @tparam TForwardIterator
 * @param[in] first,last
 * @return
 */
template< typename TForwardIterator >
inline auto is_sorted_until(TForwardIterator first, TForwardIterator last) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
auto is_sorted_until(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator {
	if (first != last) {
		for (auto after_first = first; ++after_first != last; first = after_first) {
			if (forward<TComparator>(comparator)(*after_first, *first)) {
				return after_first;
			}
		}
	}
	return last;
}

template< typename TForwardIterator >
inline auto is_sorted_until(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return is_sorted_until(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
