/**
 * @file
 * @brief is_heap
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/is_sorted_until.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::is_heap
 * @tparam TRandomAccessIterator
 * @tparam TComparator
 * @param[in] first,last
 * @param[in] comparator
 * @return
 */
template< typename TRandomAccessIterator, typename TComparator >
auto is_heap(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> bool;

/**
 * @brief like std::is_heap
 * @tparam TComparator
 * @param[in] first,last
 * @return
 */
template< typename TRandomAccessIterator >
auto is_heap(TRandomAccessIterator first, TRandomAccessIterator last) -> bool;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline auto is_heap(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> bool {
	return is_heap_until(first, last, forward<comparator>(comparator)) == last;
}

template< typename TRandomAccessIterator >
inline auto is_heap(TRandomAccessIterator first, TRandomAccessIterator last) -> bool {
	return is_heap(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
