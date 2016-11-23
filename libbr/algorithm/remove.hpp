/**
 * @file
 * @brief remove
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/find.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::remove
 * @tparam TForwardIterator
 * @tparam TValue
 * @param[in,out] first,last
 * @param[in] value
 * @return
 */
template< typename TForwardIterator, typename TValue >
auto remove(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TValue >
auto remove(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator {
	first = find(first, last, value);
	if (first != last) {
		for (auto iterator = first; ++iterator != last; ) {
			if (!(*iterator == value)) {
				*first = move(*iterator);
				++first;
			}
		}
	}
	return first;
}

} // namespace Algorithm

} // namespace BR
