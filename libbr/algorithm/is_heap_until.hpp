/**
 * @file
 * @brief is_heap_until
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TRandomAccessIterator, typename TComparator >
inline auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> TRandomAccessIterator;

template< typename TRandomAccessIterator >
inline auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last) -> TRandomAccessIterator {
	return is_heap_until(first, last, Less<>());
}

namespace Detail {
namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last, TComparator & comparator) -> TRandomAccessIterator {
	using Difference = typename IteratorTraits<TRandomAccessIterator>::Difference;
	Difference length = last - first;
	Difference p = 0;
	Difference c = 1;
	auto pp = first;
	for (; c < length;) {
		auto cp = first + c;
		if (comparator(*pp, *cp)) {
			return cp;
		}
		++c;
		++cp;
		if (c == length) {
			return last;
		}
		if (comparator(*pp, *cp)) {
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

template< typename TRandomAccessIterator, typename TComparator >
auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> TRandomAccessIterator {
	return Detail::Algorithm::is_heap_until(first, last, comparator);
}

} // namespace BR
