/**
 * @file
 * @brief reverse_copy
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::reverse_copy
 * @tparam TBidirectionalIterator
 * @tparam TOutputIterator
 * @param[in] first,last
 * @param[out] result
 * @return
 */
template< typename TBidirectionalIterator, typename TOutputIterator >
auto reverse_copy(TBidirectionalIterator first, TBidirectionalIterator last, TOutputIterator result) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TBidirectionalIterator, typename TOutputIterator >
inline auto reverse_copy(TBidirectionalIterator first, TBidirectionalIterator last, TOutputIterator result) -> TOutputIterator {
	for (; first != last; ++result) {
		*result = *--last;
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
