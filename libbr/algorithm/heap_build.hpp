/**
 * @file
 * @brief heap_build
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/heap_pop.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::make_heap
 * @tparam TRandomAccessIterator
 * @tparam TComparator
 * @param[in,out] first,last
 * @param[in] comparator
 */
template< typename TRandomAccessIterator, typename TComparator >
void heap_build(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator);

/**
 * @brief like std::make_heap
 * @tparam TRandomAccessIterator
 * @param[in,out] first,last
 */
template< typename TRandomAccessIterator >
void heap_build(TRandomAccessIterator first, TRandomAccessIterator last);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline void heap_build(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	auto length = last - first;
	if (length > 1) {
		for (auto start = (length - 2) / 2; start >= 0; --start) {
			Detail::Algorithm::heap_shift_down(first, last, length, first + start, forward<TComparator>(comparator));
		}
	}
}

template< typename TRandomAccessIterator >
inline void heap_build(TRandomAccessIterator first, TRandomAccessIterator last) {
	heap_build(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR