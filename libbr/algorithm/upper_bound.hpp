/**
 * @file
 * @brief upper_bound
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::upper_bound
 * @tparam TForwardIterator
 * @tparam TValue
 * @tparam TComparator
 * @param[in] first,last
 * @param[in] value
 * @param[in] comparator
 * @return
 */
template< typename TForwardIterator, typename TValue, typename TComparator >
auto upper_bound(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> TForwardIterator;

/**
 * @brief like std::upper_bound
 * @tparam TForwardIterator
 * @tparam TValue
 * @param[in] first,last
 * @param[in] value
 * @return
 */
template< typename TForwardIterator, typename TValue >
auto upper_bound(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TValue, typename TComparator >
auto upper_bound(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> TForwardIterator {
	for (auto length = distance(first, last); length != 0; ) {
		auto half_length = length / 2;
		auto middle = next(first, length);
		if (forward<TComparator>(comparator)(value, *middle)) {
			length = half_length;
		} else {
			first = ++middle;
			length -= half_length + 1;
		}
	}
	return first;
}

template< typename TForwardIterator, typename TValue >
inline auto upper_bound(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator {
	return upper_bound(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
