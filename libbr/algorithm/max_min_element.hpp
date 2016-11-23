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
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::minmax_element, but give result in contrary order
 * @tparam TForwardIterator
 * @tparam TComparator
 * @param[in] first,last
 * @param[in] comparator
 * @return <max, min>
 */
template< typename TForwardIterator, typename TComparator >
auto max_min_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator >;

/**
 * @brief like std::minmax_element, but give result in contrary order
 * @tparam TForwardIterator
 * @param[in] first,last
 * @return <max, min>
 */
template< typename TForwardIterator >
auto max_min_element(TForwardIterator first, TForwardIterator last) -> Pair< TForwardIterator, TForwardIterator >;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
auto max_min_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	auto result = make_pair(*first, *first);
	if (first != last) {
		if (++first != last) {
			if (forward<TComparator>(comparator)(*result.first, *first)) {
				result.first = first;
			} else {
				result.second = first;
			}
			for (; ++first != last;) {
				auto i = first;
				if (++first == last) {
					if (forward<TComparator>(comparator)(*result.first, *i)) {
						result.first = i;
					} else if (!forward<TComparator>(comparator)(*result.second, *i)) {
						result.second = i;
					} else {
						break;
					}
				} else {
					if (forward<TComparator>(comparator)(*i, *first)) {
						if (forward<TComparator>(comparator)(*result.first, *first)) {
							result.first = first;
						}
						if (!forward<TComparator>(comparator)(*result.second, *i)) {
							result.second = i;
						}
					} else {
						if (forward<TComparator>(comparator)(*result.first, *i)) {
							result.first = i;
						}
						if (!forward<TComparator>(comparator)(*result.second, *first)) {
							result.second = first;
						}
					}
				}
			}
		}
	}
	return result;
}

template< typename TForwardIterator >
inline auto max_min_element(TForwardIterator first, TForwardIterator last) -> Pair< TForwardIterator, TForwardIterator > {
	return max_min_element(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
