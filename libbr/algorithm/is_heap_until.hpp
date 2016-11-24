/**
 * @file
 * @brief is_heap_until
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::is_heap_until
 * @tparam TRandomAccessIterator
 * @tparam TComparator
 * @param[in] first,last
 * @param[in] comparator
 * @return
 */
template< typename TRandomAccessIterator, typename TComparator >
auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> TRandomAccessIterator;

/**
 * @brief like std::is_heap_until
 * @tparam TComparator
 * @param[in] first,last
 * @return
 */
template< typename TRandomAccessIterator >
auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last) -> TRandomAccessIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> TRandomAccessIterator {
	using Difference = typename IteratorTraits<TRandomAccessIterator>::Difference;
	Difference length = last - first;
	Difference p = 0;
	Difference c = 1;
	auto pp = first;
	for (; c < length;) {
		auto cp = first + c;
		if (forward<comparator>(comparator)(*pp, *cp)) {
			return cp;
		}
		++c;
		++cp;
		if (c == length) {
			return last;
		}
		if (forward<comparator>(comparator)(*pp, *cp)) {
			return cp;
		}
		++p;
		++pp;
		c = 2 * p + 1;
	}
	return last;
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> TRandomAccessIterator {
	return Detail::Algorithm::is_heap_until(first, last, forward<comparator>(comparator));
}

template< typename TRandomAccessIterator >
inline auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last) -> TRandomAccessIterator {
	return is_heap_until(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
