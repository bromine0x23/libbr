/**
 * @file
 * @brief min_max_element
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::minmax_element
 * @tparam TForwardIterator
 * @tparam TComparator
 * @param[in] first,last
 * @param[in] comparator
 * @return
 */
template< typename TForwardIterator, typename TComparator >
auto min_max_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator >;

/**
 * @brief like std::minmax_element
 * @tparam TForwardIterator
 * @param[in] first,last
 * @return
 */
template< typename TForwardIterator >
auto min_max_element(TForwardIterator first, TForwardIterator last) -> Pair< TForwardIterator, TForwardIterator >;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
auto min_max_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	auto result = make_pair(first, first);
	if (first != last) {
		if (++first != last) {
			if (forward<TComparator>(comparator)(*first, *result.first)) {
				result.first = first;
			} else {
				result.second = first;
			}
			for (; ++first != last;) {
				auto i = first;
				if (++first == last) {
					if (forward<TComparator>(comparator)(*i, *result.first)) {
						result.first = i;
					} else if (!forward<TComparator>(comparator)(*i, *result.second)) {
						result.second = i;
					} else {
						break;
					}
				} else {
					if (forward<TComparator>(comparator)(*first, *i)) {
						if (forward<TComparator>(comparator)(*first, *result.first)) {
							result.first = first;
						}
						if (!forward<TComparator>(comparator)(*i, *result.second)) {
							result.second = i;
						}
					} else {
						if (forward<TComparator>(comparator)(*i, *result.first)) {
							result.first = i;
						}
						if (!forward<TComparator>(comparator)(*first, *result.second)) {
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
inline auto min_max_element(TForwardIterator first, TForwardIterator last) -> Pair< TForwardIterator, TForwardIterator > {
	return min_max_element(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
