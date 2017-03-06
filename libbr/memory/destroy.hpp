/**
 * @file
 * @brief destroy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/destroy_at.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Destroys a range of objects.
 *
 * Destroys the objects in the range \f$ [first, last) \f$.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param first,last The range of elements to destroy.
 */
template< typename TForwardIterator >
void destroy(
	TForwardIterator first, TForwardIterator last
);

} // namespace Memory



inline namespace Memory {

template< typename TForwardIterator, typename TSize >
void destroy(TForwardIterator first, TForwardIterator last) {
	for (; first != last; ++first) {
		destroy_at(address_of(*first));
	}
}

} // namespace Memory

} // namespace BR