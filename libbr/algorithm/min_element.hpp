/**
 * @file
 * @brief min_element
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::min_element
 * @tparam TForwardIterator
 * @tparam TComparator
 * @param[in] first,last
 * @param[in] comparator
 * @return
 */
template< typename TForwardIterator, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 auto min_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator;

/**
 * @brief like std::min_element
 * @tparam TForwardIterator
 * @param[in] first,last
 * @return
 */
template< typename TForwardIterator >
BR_CONSTEXPR_AFTER_CXX11 auto min_element(TForwardIterator first, TForwardIterator last) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 inline auto min_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator {
	if (first != last) {
		for (auto i = first; ++i != last;) {
			if (forward<TComparator>(comparator)(*i, *first)) {
				first = i;
			}
		}
	}
	return first;
}

template< typename TForwardIterator >
BR_CONSTEXPR_AFTER_CXX11 inline auto min_element(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return min_element(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
