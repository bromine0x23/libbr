/**
 * @file
 * @brief min_max_element
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TForwardIterator, typename TComparator >
inline auto min_max_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator >;

template< typename TForwardIterator >
inline auto min_max_element(TForwardIterator first, TForwardIterator last) -> Pair< TForwardIterator, TForwardIterator > {
	return min_max_element(first, last, Less<>());
}

namespace Detail {
namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
auto min_max_element(TForwardIterator first, TForwardIterator last, TComparator & comparator) -> Pair< TForwardIterator, TForwardIterator > {
	auto result = make_pair(first, first);
	if (first != last) {
		if (++first != last) {
			if (comparator(*first, *result.first)) {
				result.first = first;
			} else {
				result.second = first;
			}
			for (; ++first != last;) {
				auto i = first;
				if (++first == last) {
					if (comparator(*i, *result.first)) {
						result.first = i;
					} else if (!comparator(*i, *result.second)) {
						result.second = i;
					} else {
						break;
					}
				} else {
					if (comparator(*first, *i)) {
						if (comparator(*first, *result.first)) {
							result.first = first;
						}
						if (!comparator(*i, *result.second)) {
							result.second = i;
						}
					} else {
						if (comparator(*i, *result.first)) {
							result.first = i;
						}
						if (!comparator(*first, *result.second)) {
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
auto min_max_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	return Detail::Algorithm::min_max_element(first, last, comparator);
}

} // namespace BR
