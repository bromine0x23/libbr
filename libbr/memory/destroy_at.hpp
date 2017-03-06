/**
 * @file
 * @brief destroy_at
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Destroys an object at a given address.
 * @tparam TValue Type of element that \p pointer holds.
 * @param pointer A pointer to the object to be destroyed.
 */
template< typename TValue >
void destroy_at(
	TValue * pointer
);

} // namespace Memory



inline namespace Memory {

template< typename TValue >
inline void destroy_at(TValue * pointer) {
	pointer->~TValue();
}

} // namespace Memory

} // namespace BR