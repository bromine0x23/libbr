/**
 * @file
 * @brief max_min_element
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TForwardIterator, typename TComparator >
inline auto max_min_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator >;

template< typename TForwardIterator >
inline auto max_min_element(TForwardIterator first, TForwardIterator last) -> Pair< TForwardIterator, TForwardIterator > {
	return max_min_element(first, last, Less<>());
}

namespace Detail {
namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
auto max_min_element(TForwardIterator first, TForwardIterator last, TComparator & comparator) -> Pair< TForwardIterator, TForwardIterator > {
	auto result = make_pair(first, first);
	if (first != last) {
		if (++first != last) {
			if (comparator(*result.first, *first)) {
				result.first = first;
			} else {
				result.second = first;
			}
			for (; ++first != last;) {
				auto i = first;
				if (++first == last) {
					if (comparator(*result.first, *i)) {
						result.first = i;
					} else if (!comparator(*result.second, *i)) {
						result.second = i;
					} else {
						break;
					}
				} else {
					if (comparator(*i, *first)) {
						if (comparator(*result.first, *first)) {
							result.first = first;
						}
						if (!comparator(*result.second, *i)) {
							result.second = i;
						}
					} else {
						if (comparator(*result.first, *i)) {
							result.first = i;
						}
						if (!comparator(*result.second, *first)) {
							result.second = first;
						}
					}
				}
			}
		}
	}
	return result;
}

} // namespace Algorithm
} // namespace Detail

template< typename TForwardIterator, typename TComparator >
auto max_min_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	return Detail::Algorithm::max_min_element(first, last, comparator);
}

} // namespace BR
