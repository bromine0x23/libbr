/**
 * @file
 * @brief is_sorted
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/is_sorted_until.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::is_sorted
 * @tparam TForwardIterator
 * @tparam TComparator
 * @param[in] first,last
 * @param[in] comparator
 * @return
 */
template< typename TForwardIterator, typename TComparator >
auto is_sorted(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> bool;

/**
 * @brief like std::is_sorted
 * @tparam TForwardIterator
 * @param[in] first,last
 * @return
 */
template< typename TForwardIterator >
auto is_sorted(TForwardIterator first, TForwardIterator last) -> bool;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
inline auto is_sorted(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> bool {
	return is_sorted_until(first, last, forward<TComparator>(comparator)) == last;
}

template< typename TForwardIterator >
inline auto is_sorted(TForwardIterator first, TForwardIterator last) -> bool {
	return is_sorted(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
