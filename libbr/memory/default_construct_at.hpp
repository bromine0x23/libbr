/**
 * @file
 * @brief default_construct_at
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Default constructs an object at a given address.
 * @tparam TValue Type of element that \p pointer holds.
 * @param pointer A pointer to the object to be constructed.
 */
template< typename TValue, typename... TArguments >
void default_construct_at(
	TValue * pointer
);

} // namespace Memory



inline namespace Memory {

template< typename TValue, typename... TArguments >
inline void default_construct_at(TValue * pointer) {
	::new(static_cast<void *>(pointer)) TValue;
}

} // namespace Memory

} // namespace BR