/**
 * @file
 * @brief destroy_n
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/destroy_at.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Destroys a number of objects in a range.
 * @tparam TForwardIterator Type of \p first which satisfies \em ForwardIterator.
 * @tparam TSize Type of \p count.
 * @param first The beginning of the range of elements to destroy.
 * @param count The number of elements to destroy.
 */
template< typename TForwardIterator, typename TSize >
void destroy_n(
	TForwardIterator first,
	TSize count
);

} // namespace Memory



inline namespace Memory {

template< typename TForwardIterator, typename TSize >
void destroy_n(TForwardIterator first, TSize count) {
	for (; count > 0; ++first, (void)--count) {
		destroy_at(address_of(*first));
	}
}

} // namespace Memory

} // namespace BR